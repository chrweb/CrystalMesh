/*
 * ComplexConstruction.cpp
 *
 *  Created on: 25.07.2014
 *      Author: christoph
 */

#include "Manifold.h"
#include "../Mathbox/Mathbox.h"
#include "FacetEdge.h"
#include "DirectedEdgeRing.h"
#include "EdgeRing.h"
#include "AdjacentDirectedEdgeRings.h"
#include "ComplexConstruction.h"

namespace CrystalMesh {

	typedef Subdiv3::FacetEdge FacetEdge;

	namespace Delaunay3 {

		Triangle const constructTriangleInComplex(Subdiv3::Manifold & aComplex){

			auto e0 = aComplex.makeFacetEdge();
			auto e1 = aComplex.makeFacetEdge();
			auto e2 = aComplex.makeFacetEdge();

			aComplex.spliceEdges(*e0, *e1);
			aComplex.spliceEdges(*e1, *e2);

			auto ring = aComplex.makeDualEdgeRing();

			aComplex.linkEdgeRingAndFacetEdges(*ring, *e0->getDual());

			Triangle result;
			result.mpDualEdgeRing = e0->getDual()->getDirectedEdgeRing();

			return result;
		}


		namespace {

			struct FePair{
				FacetEdge *f0;
				FacetEdge *f1;
			};

			FacetEdge * anyBoundInTriangle(Triangle const & aTri){
				return const_cast<FacetEdge*>(aTri.mpDualEdgeRing->mpRingMember->getDual());

			}

			FePair fromTriangle(Triangle const& aTri){
				FacetEdge * fe = anyBoundInTriangle(aTri);
				FePair result = {fe, fe->getClock()->getEnext()};
				return result;
			}




		}

		Blossom const constructBlossomInComplex(Subdiv3::Manifold & aComplex){

			Triangle tri[3];
			FePair fep[4];

			for (Index i = 0; i<3; i++){
				tri[i] = constructTriangleInComplex(aComplex);
				fep[i] = fromTriangle(tri[i]);
			}

			fep[3] = fep[0];

			Blossom result;

			for (Index i = 0; i<3; i++){
				auto & a = fep[i];
				auto & b = fep[i+1];

				aComplex.spliceFacets(*a.f1, *b.f0);
			}

			result.mTuple.f0 = fep[0].f0;
			result.mTuple.f1 = fep[1].f0;
			result.mTuple.f2 = fep[2].f0;

			return result;
		}

		Fan const constructFanInComplex(Subdiv3::Manifold & aComplex){
			Triangle tri[3];
			FacetEdge* fe[3];

			for (Index i = 0; i<3; i++){
				tri[i] = constructTriangleInComplex(aComplex);
				fe[i] = anyBoundInTriangle(tri[i]);
			}


			for (Index i = 0; i<2; i++){
				aComplex.spliceFacets(*fe[i], *fe[i+1]);
			}

			auto corner = aComplex.makePrimalEdgeRing();
			aComplex.linkEdgeRingAndFacetEdges(*corner, *fe[0]);

			Fan result;
			result.mpCorner = &corner->getItem(0);

			return result;
		}

		namespace{

			struct FeArray3{
				FacetEdge * array[3];
			};

			FeArray3 const fromThreeTuble(FacetEdgeThreeTuple const aTuble){
				FeArray3 result;
				result.array[0] = aTuble.f0;
				result.array[1] = aTuble.f1;
				result.array[2] = aTuble.f2;

				return result;
			}
		}

		TetInteriour const constructTetInteriourInComplex(Subdiv3::Manifold & aComplex){

			// see https://github.com/chrweb/CrystalMesh/wiki/Cell-complexes-in-Delaunay3#tetrahedron-interior
			// for a sketch..

			Fan fan = constructFanInComplex(aComplex);
			Blossom blos = constructBlossomInComplex(aComplex);

			auto fanArray = fromThreeTuble(fan.getBlossomAdapter());
			auto blosArray = fromThreeTuble(blos.getFanAdapter());

			for (Index i = 0; i<3; i++){
				aComplex.spliceFacets(*fanArray.array[i], *blosArray.array[i]);
			}

			/**
			 * to make flipping easier, construct well-linked entities..
			 */
			//construct and link interior corners (edge ring size 3)
			Subdiv3::EdgeRing * innerRing[3];

			for(Index i = 0; i<3; i++){
				innerRing[i] = aComplex.makePrimalEdgeRing();
				aComplex.linkEdgeRingAndFacetEdges(*innerRing[i], *fanArray.array[i]);
			}


			TetInteriour result;

			//construct and link corners with edge ring size 1 (outer ones)
			// these can be reached by fan tuple
			Subdiv3::FacetEdge * outerEdges[6];
			auto & outerRing = result.mpOuterEdgeRing;

			// get linking pairs
			for (Index i = 0; i<3; i++){
				outerEdges[i] =   fanArray.array[i]->getEnext();
				outerEdges[i+3] =   fanArray.array[i]->getFnext()->getEnext();
			}

			// construct and link
			for (Index i = 0; i<6; i++){
				outerRing[i] = aComplex.makePrimalEdgeRing();
				aComplex.linkEdgeRingAndFacetEdges(*outerRing[i], *outerEdges[i]);
			}

			//construct vertices
			auto &  vert = result.mpVertex;
			for(Index i = 0; i<5; i++){
				vert[i] = aComplex.makePrimalVertex();
			}

			// link interiour vertex:
			aComplex.linkVertexDirectedEdgeRings(*vert[0], *fanArray.array[0]->getDirectedEdgeRing());

			// collect all adjacent edge rings:
			auto const adjRings = getAdjacentRingsOf(*vert[0]);

			// link their syms with vertex 1 to 4
			for (Index i = 1; i<5; i++){
				aComplex.linkVertexDirectedEdgeRings(*vert[i], *adjRings[i-1]->getSym());
			}

			// prepare result:
			return result;
		}

		Tet const constructTetInComplex(Subdiv3::Manifold & aComplex){

			Tet result;

			Subdiv3::Vertex* verts[4];

			// four primal vertices,
			// four tris
			for (Index i = 0; i<4; i++){
				result.mTri[i] = constructTriangleInComplex(aComplex);
				verts[i] = aComplex.makePrimalVertex();
			}

			auto & tri = result.mTri;

			// two dual verts
			auto extr = aComplex.makeDualVertex();
			auto intr = aComplex.makeDualVertex();

			//interiour is needed for result:
			result.mpDualVertex = intr;

			// ea => edgeArray
			auto ea0 = tri[0].getBoundary();
			auto ea1 = tri[1].getBoundary();
			auto ea2 = tri[2].getBoundary();
			auto ea3 = tri[3].getBoundary();

			// do splice operations
			aComplex.spliceFacets(*ea0.f0, *ea1.f0->getClock());
			aComplex.spliceFacets(*ea0.f1, *ea2.f0->getClock());
			aComplex.spliceFacets(*ea0.f2, *ea3.f0->getClock());

			aComplex.spliceFacets(*ea1.f2, *ea2.f1->getClock());
			aComplex.spliceFacets(*ea2.f2, *ea3.f1->getClock());
			aComplex.spliceFacets(*ea3.f2, *ea1.f1->getClock());

			// constructing edge rings for tet's corner:
			Subdiv3::EdgeRing* ring[6];
			for (Index c = 0; c < 6; c++){
				ring[c] = aComplex.makePrimalEdgeRing();
			}

			// link them..
			aComplex.linkEdgeRingAndFacetEdges(*ring[0], *ea0.f0);
			aComplex.linkEdgeRingAndFacetEdges(*ring[1], *ea0.f1);
			aComplex.linkEdgeRingAndFacetEdges(*ring[2], *ea0.f2);

			aComplex.linkEdgeRingAndFacetEdges(*ring[3], *ea1.f2);
			aComplex.linkEdgeRingAndFacetEdges(*ring[4], *ea2.f2);
			aComplex.linkEdgeRingAndFacetEdges(*ring[5], *ea3.f2);

			// linking the primal vertices:
			aComplex.linkVertexDirectedEdgeRings(*verts[0], ring[3]->operator [](0));
			aComplex.linkVertexDirectedEdgeRings(*verts[1], ring[2]->operator [](0));
			aComplex.linkVertexDirectedEdgeRings(*verts[2], ring[0]->operator [](0));
			aComplex.linkVertexDirectedEdgeRings(*verts[3], ring[1]->operator [](0));

			// link dual  verts:
			Subdiv3::DirectedEdgeRing * pToOuter = result.mTri[0].mpDualEdgeRing;
			Subdiv3::DirectedEdgeRing * pToInner = pToOuter->getSym();

			aComplex.linkVertexDirectedEdgeRings(*extr, *pToInner);
			aComplex.linkVertexDirectedEdgeRings(*intr, *pToOuter);

			return result;
		}


	}  // namespace Delaunay3



}  // namespace CrystalMesh



