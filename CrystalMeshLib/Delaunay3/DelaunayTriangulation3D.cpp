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
	:public Subdiv3::EntityMaintener
	 {};

	namespace Delaunay3{

		DelaunayTriangulation3D::DelaunayTriangulation3D()
		: mpManifold(new Subdiv3::Manifold)
		, mpToVetexData(new VertexDataContainer)
		{

		}

		namespace{
			Triangle const triangleOf(Subdiv3::EdgeRing * apEdgeRing){
				Triangle result;
				result.mpDualEdgeRing = apEdgeRing;
				return result;
			}

		}

		Triangle const DelaunayTriangulation3D::makeTriangle(){


		}


	}

}



