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

	    	FieldIndex computeDualJump(FieldIndex aIdx){
	    		if (aIdx%2 == 0){
	    			return 3;
	    		}
	    		else
	    			return -3;
	    	}

	    	FieldIndex computeReverseJump(FieldIndex aIdx){
	    		if (aIdx%2 == 0){
	    			return 1;
	    		}
	    		else
	    			return -1;
	    	}

	    	FieldIndex computeClockIndex(FieldIndex aIdx){
	    		if (aIdx < 4)
	    			return 4;
	    		else
	    			return -4;
	    	}

	    	void setMemberVars(OctoNode & aInst){

	    		for (FieldIndex idx = 0; idx < 8; idx++)
	    		{
	    			auto  ref = & aInst.mNodeArray[idx];
	    			ref->mpNext = ref;
	    			// set the field index and jumps
	    			ref->mIndex =idx;
	    			ref->mDualIt = computeDualJump(idx);
	    			ref->mClckIt = computeClockIndex(idx);
	    			ref->mRevsIt = computeReverseJump(idx);
	    		}

	    	}

	    }


	    FacetEdge * Manifold::makeFacetEdge(){

	    	OctoNode * pInst = mpToOctoNodeMaintener->mInternalMaintener.constructEntity();

	    	// Initialize members in OctoNode's FacetEdges
	    	setMemberVars(*pInst)

	    	return &pInst->mNodeArray[0];
	    }


	}
}




