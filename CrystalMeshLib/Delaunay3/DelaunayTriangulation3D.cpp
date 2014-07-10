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

				auto collector = [&result, &counter](FacetEdge const & aInst){
					MUST_BE(counter < 3);
					result.mArray[counter] = aInst.getDual();
					counter++;
				};

				forEachElementInFnextRing(*aTri.mpDualEdgeRing->mpRingMember, collector);

				return result;
			}



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

			mpManifold->spliceFacets(ea0.mArray[0], ea1.mArray[0])








		}


	}

}




