/*
 * Manifold.cpp
 *
 *  Created on: 19.06.2014
 *      Author: christoph
*/
#include <vector>
#include <stddef.h>
#include "MaintenerTemplate.h"
#include  "../Toolbox/Checks.h"
#include "Vertex.h"
#include "QuaterNode.h"
#include "EdgeRing.h"
#include <assert.h>

#include "Manifold.h"
#include "AdjacentDirectedEdgeRings.h"

namespace CrystalMesh{

	namespace Subdiv3{
            
                
            using namespace Toolbox;
            
            //Inherit from Mainteer template..
		
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

	    	/**
	    	 * see
	    	 * https://github.com/chrweb/CrystalMesh/wiki/Topological-operations-on-a-3D-cell-complex#splicefacets
	    	 * for detailed explanation.
	    	 */

	    	// reverence version fnext
	    	auto fe0Fnext = aFe0.getFnext();
	    	auto fe1Fnext = aFe1.getFnext();

	    	// clocked versions
	    	auto fe0FnextClock = aFe1.getFnext()->getClock();
	    	auto fe1FnextClock = aFe0.getFnext()->getClock();

	    	// clocked fnext fields
	    	auto fe0FnextClockFnext = fe0FnextClock->getFnext();
	    	auto fe1FnextClockFnext = fe1FnextClock->getFnext();

	    	// reverence version's fnext fields
	    	aFe0.mpNext =fe1Fnext;
	    	aFe1.mpNext = fe0Fnext;

	    	// clocked version's fnext fields
	    	fe0FnextClock->mpNext = fe1FnextClockFnext;
	    	fe1FnextClock->mpNext = fe0FnextClockFnext;

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

	    EdgeRing * Manifold::makePrimalEdgeRing(){
                auto pInst = mpPrimalEdgeRingMaintener->constructEntity();
	   	setEdgeRingMemberVars(*pInst);
	   	return pInst;
	    }
            
            
            void Manifold::deletePrimalEdgeRing(EdgeRing & aRef){
                auto pToInstance = &aRef;
                mpPrimalEdgeRingMaintener->deleteEntity(pToInstance);
            }

	    EdgeRing * Manifold::makeDualEdgeRing()
	    {
	    	auto pInst = mpDualEdgeRingMaintener->constructEntity();
	    	setEdgeRingMemberVars(*pInst);
	    	return pInst;
	    }
            
            void Manifold::deleteDualEdgeRing(EdgeRing & aRef){
                auto pToInstance = &aRef;
                mpDualEdgeRingMaintener->deleteEntity(pToInstance);
                return;
            }

	    namespace{
	    	void setVertexLinks(Vertex & aVert){
	    		aVert.mpData =  nullptr;
	    		aVert.mpOut = nullptr;
	    		return;
	    	}

	    }



	    Vertex * Manifold::makePrimalVertex(){
	    	auto pInst = mpPrimalVertexMaintener->constructEntity();
	    	setVertexLinks(*pInst);
	    	return pInst;
	    }
            
            void Manifold::deletePrimalVertex(Vertex & aRef){
                auto pToInstance = &aRef;
                mpPrimalVertexMaintener->deleteEntity(pToInstance);
            }
            
            void Manifold::deleteQuaterNodeOf(FacetEdge & aRef){
               auto toQuaterNode = aRef.getQuaterNode();
               mpQuaterNodeMaintener->deleteEntity(toQuaterNode);
               return;
            }


	    Vertex * Manifold::makeDualVertex(){
	    	auto pInst = mpDualVertexMaintener->constructEntity();
	    	setVertexLinks(*pInst);
	    	return pInst;
	    }
            
            void Manifold::deleteDualVertex(Vertex & aRef){
                auto pToInstance = &aRef;
                mpDualVertexMaintener->deleteEntity(pToInstance);
                return;
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
	    	if (isDualEdgeRing){
                MUST_BE(isDualFacetEdge);    
                }
	    	else{
                    MUST_BE(!isDualFacetEdge);
                }

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
	    	
                    SHOULD_BE(apVert!=nullptr);
                    aDring.mpOrg = apVert;

	    	}

	    	void linkDirectedEdgeRingToVertex(DirectedEdgeRing * apDring, Vertex& aVert){
                    SHOULD_BE(apDring!=nullptr);
                    aVert.mpOut = apDring->getRingMember();
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
                
          





                void Manifold::exportPrimalVerts(VertexBuffer& aBuffer) const{
                
                    auto const& container = mpPrimalVertexMaintener->getContainer();
                    
                    aBuffer.reserve(container.size());
                    for (auto item: container){
                        aBuffer.push_back(item);
                    }
                    
                }
                        
                void Manifold::exportDualVerts(VertexBuffer& aBuffer) const{
                    auto const& container = mpDualVertexMaintener->getContainer();
                    
                    aBuffer.reserve(container.size());
                    for (auto item: container){
                        aBuffer.push_back(item);
                    }
                }
                        
                void Manifold::exportPrimalEdgeRings(EdgeRingBuffer& aBuffer) const{
                    auto const& container = mpPrimalEdgeRingMaintener->getContainer();
                    
                    aBuffer.reserve(container.size());
                    for (auto item: container){
                        aBuffer.push_back(item);
                    }
                }
                        
                void Manifold::exportDualEdgeRings(EdgeRingBuffer& aBuffer) const{
                    auto const& container = mpDualEdgeRingMaintener->getContainer();
                    
                    aBuffer.reserve(container.size());
                    for (auto item: container){
                        aBuffer.push_back(item);
                    }
                }
                
                size_t Manifold::primalVertexSize() const{
                    return mpPrimalVertexMaintener->size();
                }
                        
                size_t Manifold::dualVertexSize() const{
                    return mpDualVertexMaintener->size();
                }
                        
                size_t Manifold::primalEdgeRingSize() const{
                    return mpPrimalEdgeRingMaintener->size();
                }
                        
                size_t Manifold::dualEdgeRingSize() const{
                    return mpDualEdgeRingMaintener->size();
                }
                       
	}
}




