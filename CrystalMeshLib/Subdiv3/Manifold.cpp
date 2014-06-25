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
#include "QuaterNode.h"

namespace CrystalMesh{

	namespace Subdiv3{

		/**
		 * Why can't I write something like:
		 * 	typedef EntityMaintener<OctoNode> OctoNodeMaintener;
		 * 	for class definition?
		 */


		class VertexMaintener
		:public EntityMaintener<Vertex>
		{};

		class QuaterNodeMaintener
		:public EntityMaintener<QuaterNode>
		{};

		class EdgeRingMaintener
		:public EntityMaintener<EdgeRing>
		{};

	    Manifold::Manifold()
	    : mpPrimalVertexMaintener( new VertexMaintener() )
	    , mpDualVertexMaintener( new VertexMaintener() )
	    , mpQuaterNodeMaintener( new QuaterNodeMaintener() )
	    , mpPrimalEdgeRingMaintener( new EdgeRingMaintener)
	    , mpDualEdgeRingMaintener( new EdgeRingMaintener)
		{

		}


	    namespace{

	    	FieldIndex computeDualJump(FieldIndex aIdx){
	    		if (aIdx%2 == 0){
	    			return 1;
	    		}
	    		else
	    			return -1;
	    	}

	    	FieldIndex computeClockIndex(FieldIndex aIdx){
	    		if (aIdx < 2)
	    			return 2;
	    		else
	    			return -2;
	    	}

	    	void setMemberVars(QuaterNode & aInst){

	    		for (FieldIndex idx = 0; idx < 4; idx++)
	    		{
	    			auto  ref = & aInst.mNodeArray[idx];
	    			ref->mpNext = ref;
	    			// set the field index and jumps
	    			ref->mIndex =idx;
	    			ref->mDualIt = computeDualJump(idx);
	    			ref->mClckIt = computeClockIndex(idx);

	    			ref->mpNext = ref;
	    		}
	    	}

	    }


	    FacetEdge * Manifold::makeFacetEdge(){

	    	QuaterNode * pInst = mpQuaterNodeMaintener->constructEntity();

	    	// Initialize members in OctoNode's FacetEdges
	    	setMemberVars(*pInst);

	    	return &pInst->mNodeArray[0];
	    }

	    void Manifold::spliceFacets(FacetEdge& aFe0, FacetEdge& aFe1){

	    	// reverence version
	    	auto alpha0 = aFe0.getFnext();
	    	auto alpha1 = aFe1.getFnext();
	    	aFe0.mpNext = alpha1;
	    	aFe1.mpNext = alpha0;

	    	// clocked version
	    	auto fe0Clock = aFe0.getClock();
	    	auto fe1Clock = aFe1.getClock();

	    	auto beta0 = fe0Clock->getFnext();
	    	auto beta1 = fe1Clock->getFnext();

	    	fe0Clock->mpNext = beta1;
	    	fe1Clock->mpNext = beta0;

	    	return;
	    }


	    void Manifold::spliceEdges(FacetEdge& aFe0, FacetEdge& aFe1){
	    	spliceFacets(*aFe0.getDual(), *aFe1.getDual());
	    }



	}
}




