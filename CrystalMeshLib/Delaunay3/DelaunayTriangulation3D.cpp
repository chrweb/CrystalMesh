/*
 * DelaunayTriangulation3.cpp
 *
 *  Created on: 29.06.2014
 *      Author: christoph
 */
#include "DelaunayTriangulation3D.h"
#include "../Subdiv3/Subdiv3Prototypes.h"
#include "../Subdiv3/MaintenerTemplate.h"
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
			mpManifold->spliceEdges(*e2, *e0);

			auto ring = mpManifold->makeDualEdgeRing();

			mpManifold->linkEdgeRingAndFacetEdges(*ring, *e0->getDual());

			Triangle result;
			result.mpDualEdgeRing = e0->getDual()->getDirectedEdgeRing();

			return result;
		}


	}

}




