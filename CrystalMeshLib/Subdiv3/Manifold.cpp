/*
 * Manifold.cpp
 *
 *  Created on: 19.06.2014
 *      Author: christoph
*/
#include "MaintenerTemplate.h"
#include  "../Misc/Checks.h"
#include "Vertex.h"
#include "QuaterNode.h"
#include "EdgeRing.h"
#include <assert.h>
#include <set>
#include <vector>
#include <queue>
#include "Manifold.h"
#include "AdjacentDirectedEdgeRings.h"

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

	    Manifold::~Manifold(){
	    	delete mpPrimalVertexMaintener;
	    	delete mpDualVertexMaintener;
	    	delete mpQuaterNodeMaintener;
	    	delete mpPrimalEdgeRingMaintener;
	    	delete mpDualEdgeRingMaintener;
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

	    			ref->mpDirectedEdgeRing = nullptr;
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

	    namespace{
	    	void setEdgeRingMemberVars(EdgeRing & aRing){

	    		for (FieldIndex i = 0; i<2; i++){
	    			aRing.mRings[i].mpRingMember = nullptr;
	    			aRing.mRings[i].mpOrg = nullptr;
	    			aRing.mRings[i].mIndex = i;
	    		}

	    	}

	    }

	    EdgeRing * Manifold::makePrimalEdgeRing()
	   	    {
	   	    	auto pInst = mpPrimalEdgeRingMaintener->constructEntity();
	   	    	setEdgeRingMemberVars(*pInst);
	   	    	return pInst;
	   	    }

	    EdgeRing * Manifold::makeDualEdgeRing()
	    {
	    	auto pInst = mpDualEdgeRingMaintener->constructEntity();
	    	setEdgeRingMemberVars(*pInst);
	    	return pInst;
	    }

	    namespace{
	    	void setVertexLinks(Vertex & aVert){
	    		aVert.mpData =  nullptr;
	    		aVert.mpOut = nullptr;
	    		return;
	    	}

	    }

	    /**
	     * Implementation of functions to collect adjacent directed edge rings
	     */
	    namespace{

	    	typedef std::vector<DirectedEdgeRing*> IncidentEdgeRings;

	    	IncidentEdgeRings const incidentEdgeRingsFrom(DirectedEdgeRing * apRing){
	    		IncidentEdgeRings result;

	    		auto collector = [&result](FacetEdge & aFe){
	    			FacetEdge * transition = aFe.getInvEnext()->getClock();
	    			result.push_back(transition->getDirectedEdgeRing());
	    		};

	    		forEachElementInFnextRing(*apRing->mpRingMember, collector);
	    		return result;
	    	}


	    	// All incident rings to a vertex may be extracted by a BFS:
	    	// http://en.wikipedia.org/wiki/Breadth-first_search
	    	AdjacentRings const getAdjacentRingsOf( DirectedEdgeRing const & aDring){

	    		typedef std::queue<DirectedEdgeRing*> NodeQueue;
	    		std::set<DirectedEdgeRing*> visitedNodes;


	    		NodeQueue nodeQueue;

	    		// initial node:
	    		DirectedEdgeRing * initialNode = const_cast<DirectedEdgeRing*>(&aDring);
	    		nodeQueue.push(initialNode);
	    		visitedNodes.insert(initialNode);

	    		while(!nodeQueue.empty()){
					auto current = nodeQueue.front();
					nodeQueue.pop();

					auto const nextNodes = incidentEdgeRingsFrom(current);

					for(auto current: nextNodes){
						// the node was not visited yet:
						if (visitedNodes.insert(current).second){
							// add this node into queue to get neighbored nodes:
							nodeQueue.push(current);
						}
					}
	    		}

	    		AdjacentRings result(visitedNodes.begin(), visitedNodes.end());
	    		return result;
	    	}
	    }


	    Vertex * Manifold::makePrimalVertex(){
	    	auto pInst = mpPrimalVertexMaintener->constructEntity();
	    	setVertexLinks(*pInst);
	    	return pInst;
	    }

	    Vertex * Manifold::makeDualVertex(){
	    	auto pInst = mpDualVertexMaintener->constructEntity();
	    	setVertexLinks(*pInst);
	    	return pInst;
	    }

	    void Manifold::linkEdgeRingAndFacetEdges(EdgeRing& aEring, FacetEdge & aRingRep) const {

	    	// preconditions:
	    	// preconditions are verified in only in debug
	    	// fail should cause termination
	    	#ifndef NDEBUG

	    	// EdgeRing's flavor
	    	bool isDualEdgeRing = isMyDualEdgeRing(aEring);

	    	bool isPrimalEdgeRing = isMyPrimalEdgeRing(aEring);

	    	// EdgeRing must be element of this
	    	MUST_BE(isDualEdgeRing ^ isPrimalEdgeRing);

	    	// FacetEdge's flavor
	    	bool isDualFacetEdge = aRingRep.isDual();

	    	// FacetEdge is part of this
	    	bool isMyFe= isMyFacetEdge(aRingRep);

	    	MUST_BE(isMyFe);

	    	// FacetEdge must be same flavor as EdgeRing
	    	if (isDualEdgeRing)
	    		MUST_BE(isDualFacetEdge);
	    	else
	    		MUST_BE(!isDualFacetEdge);

	    	// Edge ring is unassociated
	    	MUST_BE(isNullptr(aEring.mRings[0].mpRingMember));
	    	MUST_BE(isNullptr(aEring.mRings[1].mpRingMember));

	    	// All FacetEdges are unassociated
	    	bool unAssociated = true;

	    	auto checkUnAssociated = [&unAssociated](FacetEdge const & aArg ){
	    		if (notNullptr(aArg.mpDirectedEdgeRing))
	    			unAssociated = false;

	    		auto const pClock = aArg.getClock();

	    		if (notNullptr(pClock->mpDirectedEdgeRing))
	    			unAssociated = false;
	    	};

	    	forEachElementInFnextRing(aRingRep, checkUnAssociated);

	    	MUST_BE(unAssociated);

			#endif

	    	// link EdgeRing to FacetEdge
	    	aEring.mRings[0].mpRingMember = &aRingRep;
	    	aEring.mRings[1].mpRingMember = aRingRep.getClock();

	    	auto  & ringRef = aEring;

	    	// link FacetEdges to Ring:
	    	auto ringLinker = [&ringRef](FacetEdge & aRef){
	    		aRef.mpDirectedEdgeRing = &ringRef.mRings[0];
	    		aRef.getClock()->mpDirectedEdgeRing = &ringRef.mRings[1];
	    	};

	    	forEachElementInFnextRing(aRingRep, ringLinker);

	    	return;

	    }

	    void Manifold::dislinkEdgeRing(EdgeRing & aEring) const{

	    	MUST_BE(notNullptr(aEring[0].mpRingMember));
	    	MUST_BE(notNullptr(aEring[1].mpRingMember));

	    	auto disLinker = [](FacetEdge& aRef){
	    		aRef.mpDirectedEdgeRing = nullptr;
	    		aRef.getClock()->mpDirectedEdgeRing = nullptr;
	    	};

	    	forEachElementInFnextRing(*aEring[0].mpRingMember , disLinker);

	    	aEring[0].mpRingMember = nullptr;
	    	aEring[1].mpRingMember = nullptr;

	    	return;
	    }

	    namespace{
	    	void linkVertexToDirectedEdgeRing(Vertex * apVert, DirectedEdgeRing & aDring){
	    		// TODO: check nullptr'ness here..?
	    		aDring.mpOrg = apVert;

	    	}

	    	void linkDirectedEdgeRingToVertex(DirectedEdgeRing * apDring, Vertex& aVert){
	    		// TODO: check nullptr'ness here..?
	    		aVert.mpOut = apDring;
	    	}
	    }

	    void Manifold::linkVertexDirectedEdgeRings(Vertex & aVert, DirectedEdgeRing & aDring){

	    	// Edge rings is instance of this
	    	// Directed edge ring is dual?
	    	if (aDring.isDual())
	    	{
	    		// must be a part of my dual edge ring...
	    		MUST_BE(isMyDualEdgeRing(*aDring.getEdgeRing()));
	    		// vertex must be my part of my duals either..
	    		MUST_BE(isMyDualVertex(aVert));
	    	}
	    	// primals analogous
	    	else{
	    		MUST_BE(isMyPrimalEdgeRing(*aDring.getEdgeRing()));
	    		MUST_BE(isMyPrimalVertex(aVert));
	    	}

	    	// get every incident edge ring
	    	auto incEdgeRings = getAdjacentRingsOf(aDring);

	    	// vertex not associated
	    	MUST_BE(isNullptr(aVert.mpOut));

	    	for (auto const item: incEdgeRings){
	    		MUST_BE(isNullptr(item->getOrg()));
	    	}

	    	linkDirectedEdgeRingToVertex(&aDring, aVert);

	    	for(auto const currentDring: incEdgeRings){
	    		linkVertexToDirectedEdgeRing(&aVert, *currentDring);
	    	}

	    	// done
	    	return;
	    }

		bool const Manifold::isMyFacetEdge(FacetEdge const & aFe) const{
			auto const qn = aFe.getQuaterNode();
			return mpQuaterNodeMaintener->isMyEntity(*qn);
		}

		bool const Manifold::isMyPrimalEdgeRing(EdgeRing const & aRing) const{
			return mpPrimalEdgeRingMaintener->isMyEntity(aRing);
		}

		bool const Manifold::isMyDualEdgeRing(EdgeRing const & aRing) const{
			return mpDualEdgeRingMaintener->isMyEntity(aRing);
		}

		bool const Manifold::isMyPrimalVertex(Vertex const & aVert) const{
			return mpPrimalVertexMaintener->isMyEntity(aVert);
		}

		bool const Manifold::isMyDualVertex(Vertex const & aVert) const{
			return mpDualVertexMaintener->isMyEntity(aVert);
		}

		void Manifold::dislinkVertexDirectedEdgeRings(Vertex & aVertex){

			auto const adjEdgeRings = getAdjacentRingsOf(aVertex);
			aVertex.mpOut = nullptr;
			for (auto pCurrent: adjEdgeRings){
				pCurrent->mpOrg = nullptr;
			}

			return;
		}

		// public function to collect adjacent directed edge rings.
	    AdjacentRings const getAdjacentRingsOf( Vertex const & aVert){
	    	return getAdjacentRingsOf(*aVert.getDirectedEdgeRing());
	    }






	}
}




