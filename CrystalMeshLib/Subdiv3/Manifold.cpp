/*
 * Manifold.cpp
 *
 *  Created on: 19.06.2014
 *      Author: christoph
*/
#include "Manifold.h"
#include "MaintenerTemplate.h"
#include  "../Misc/Checks.h"
#include "Vertex.h"
#include "OctoNode.h"

namespace CrystalMesh{

	namespace Subdiv3{

		/**
		 * Why can't I write something like:
		 * 	typedef EntityMaintener<OctoNode> OctoNodeMaintener;
		 * 	for class definition?
		 */


		class VertexMaintener{
		public:
			EntityMaintener<Vertex> mInternalMaintener;
		};

		class OctoNodeMaintener{
		public:
			EntityMaintener<OctoNode> mInternalMaintener;
		};

		class EdgeRingMaintener{
		public:
			EntityMaintener<EdgeRing> mInternalMaintener;
		};

	    Manifold::Manifold()
	    : mpToVertexMaintener( new VertexMaintener() )
	    , mpToOctoNodeMaintener( new OctoNodeMaintener() )
	    , mpToEdgeRingMaintener( new EdgeRingMaintener)
		{

		}


	    namespace{

	    	void setMemberVars(OctoNode & aInst){

	    	}

	    }

	    FacetEdge * Manifold::makeFacetEdge(){

	    	OctoNode * pInst = mpToOctoNodeMaintener->mInternalMaintener.constructEntity();

	    }


	}
}




