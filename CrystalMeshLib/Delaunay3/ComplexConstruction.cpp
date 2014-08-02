/*
 * ComplexConstruction.cpp
 *
 *  Created on: 25.07.2014
 *      Author: christoph
 */

#include "../Subdiv3/Manifold.h"
#include "../Math/Geometry.h"
#include "../Subdiv3/FacetEdge.h"
#include "../Subdiv3/DirectedEdgeRing.h"
#include "../Subdiv3/EdgeRing.h"
#include "../Subdiv3/AdjacentDirectedEdgeRings.h"
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

		TetInteriour const constructTetInteriourInComplex(Subdiv3::Manifold & aComplex){

			// see https://github.com/chrweb/CrystalMesh/wiki/Cell-complexes-in-Delaunay3#tetrahedron-interior
			// for a sketch..

			Fan fan = constructFanInComplex(aComplex);
			Blossom blos = constructBlossomInComplex(aComplex);

			auto fanTuple = fan.getBlossomAdapter();
			auto blosTuple = blos.getFanAdapter();

			aComplex.spliceFacets(*fanTuple.f0, *blosTuple.f0);
			aComplex.spliceFacets(*fanTuple.f1, *blosTuple.f1);
			aComplex.spliceFacets(*fanTuple.f2, *blosTuple.f2);

			Subdiv3::EdgeRing * ring[3];

			// construct corners
			for (Index i = 0; i<3; i++){
				ring[i] = aComplex.makePrimalEdgeRing();
			}

			//construct vertex:
			auto pVertex = aComplex.makePrimalVertex();

			//link corners
			aComplex.linkEdgeRingAndFacetEdges(*ring[0], *fanTuple.f0);
			aComplex.linkEdgeRingAndFacetEdges(*ring[1], *fanTuple.f1);
			aComplex.linkEdgeRingAndFacetEdges(*ring[2], *fanTuple.f2);

			// link vertex:
			aComplex.linkVertexDirectedEdgeRings(*pVertex, *fanTuple.f0->getDirectedEdgeRing());


			TetInteriour result;

			result.mpVertex = pVertex;

			// collect all adjacent edge rings:
			auto const adjRings = getAdjacentRingsOf(*pVertex);

			// return their syms, whose origins are not linked yet
			for (Index i = 0; i<4; i++){
				result.mpDring[i]= adjRings[i]->getSym();
			}

			return result;
		}






	}  // namespace Delaunay3



}  // namespace CrystalMesh



