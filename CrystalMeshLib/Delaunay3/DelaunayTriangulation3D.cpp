/*
 * DelaunayTriangulation3.cpp
 *
 *  Created on: 29.06.2014
 *      Author: christoph
 */
#include "DelaunayTriangulation3D.h"
#include "../Subdiv3/Subdiv3Prototypes.h"
#include "../Subdiv3/MaintenerTemplate.h"
#include "../Subdiv3/FacetEdge.h"

namespace CrystalMesh{

	class VertexDataContainer
	:public Subdiv3::EntityMaintener<VertexData>
	 {};

	namespace Delaunay3{

		DelaunayTriangulation3D::DelaunayTriangulation3D()
		: mpManifold(new Subdiv3::Manifold)
		, mpToVetexData(new VertexDataContainer)
		{

		}

		namespace{
			Triangle const triangleOf(Subdiv3::DirectedEdgeRing * apRing){
				Triangle result;
				result.mpDualEdgeRing = apRing;
				return result;
			}

		}

		Triangle const DelaunayTriangulation3D::makeTriangle(){
			auto e0 = mpManifold->makeFacetEdge();
			auto e1 = mpManifold->makeFacetEdge();
			auto e2 = mpManifold->makeFacetEdge();

			mpManifold->spliceEdges(*e0, *e1);
			mpManifold->spliceEdges(*e1, *e2);

			auto ring = mpManifold->makeDualEdgeRing();

			mpManifold->linkEdgeRingAndFacetEdges(*ring, *e0->getDual());

			Triangle result;
			result.mpDualEdgeRing = e0->getDual()->getDirectedEdgeRing();

			return result;
		}

		namespace {

			struct EdgeArray{
				Subdiv3::FacetEdge * mArray[3];
			};

			EdgeArray const edgeArrayOf(Triangle const & aTri){
				using namespace Subdiv3;
				EdgeArray result;
				int counter = 0;

				auto collector = [&result, &counter](FacetEdge  & aInst){
					MUST_BE(counter < 3);
					result.mArray[counter] = aInst.getDual();
					counter++;
				};

				forEachElementInFnextRing(*aTri.mpDualEdgeRing->mpRingMember, collector);

				return result;
			}

			Triangle const clockedTriangle(Triangle const & aTri){
				Triangle result;
				result.mpDualEdgeRing = aTri.mpDualEdgeRing->mpRingMember->getClock()->getDirectedEdgeRing();
				return result;
			}

			typedef uint32_t Counter;



		}

		Tetraeder const DelaunayTriangulation3D::makeTetraeder(){

			Tetraeder result;

			auto tri0 = makeTriangle();
			auto tri1 = makeTriangle();
			auto tri2 = makeTriangle();
			auto tri3 = makeTriangle();

			auto vert0 = mpManifold->makePrimalVertex();
			auto vert1 = mpManifold->makePrimalVertex();
			auto vert2 = mpManifold->makePrimalVertex();
			auto vert3 = mpManifold->makePrimalVertex();

			auto extr = mpManifold->makeDualVertex();
			auto intr = mpManifold->makeDualVertex();

			EdgeArray ea0 = edgeArrayOf(tri0);
			EdgeArray ea1 = edgeArrayOf(tri1);
			EdgeArray ea2 = edgeArrayOf(tri2);
			EdgeArray ea3 = edgeArrayOf(tri3);

			mpManifold->spliceFacets(*ea0.mArray[0], *ea1.mArray[0]->getClock());
			mpManifold->spliceFacets(*ea0.mArray[1], *ea1.mArray[0]->getClock());
			mpManifold->spliceFacets(*ea0.mArray[2], *ea1.mArray[0]->getClock());

			mpManifold->spliceFacets(*ea1.mArray[2], *ea2.mArray[1]->getClock());
			mpManifold->spliceFacets(*ea2.mArray[2], *ea3.mArray[1]->getClock());
			mpManifold->spliceFacets(*ea3.mArray[2], *ea1.mArray[1]->getClock());

			// constructing edge rings for tet's corner:
			Subdiv3::EdgeRing* ring[6];
			for (Counter c = 0; c < 6; c++){
				ring[c] = mpManifold->makePrimalEdgeRing();
			}

			// links them..
			mpManifold->linkEdgeRingAndFacetEdges(*ring[0], *ea0[0]);
			mpManifold->linkEdgeRingAndFacetEdges(*ring[1], *ea0[1]);
			mpManifold->linkEdgeRingAndFacetEdges(*ring[2], *ea0[2]);

			mpManifold->linkEdgeRingAndFacetEdges(*ring[3], *ea1[2]);
			mpManifold->linkEdgeRingAndFacetEdges(*ring[4], *ea2[2]);
			mpManifold->linkEdgeRingAndFacetEdges(*ring[5], *ea3[2]);

			// linking the primal vertices:
			//mpManifold->linkVertexEdgeRings()






			return result;
		}


	}

}




