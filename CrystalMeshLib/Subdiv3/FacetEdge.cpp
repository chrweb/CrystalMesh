/*
 * FacetEdge.cpp
 *
 *  Created on: 18.06.2014
 *      Author: christoph
 */
#include "FacetEdge.h"
#include "Vertex.h"
#include "DirectedEdgeRing.h"
#include "../Misc/Checks.h"

namespace CrystalMesh{

	namespace Subdiv3{

		namespace{

			template<typename T>
			void checkValidPtr(T const * ptr){
				MUST_BE(notNullptr(ptr));
			}

			bool checkClockIteration(FacetEdge const & aFe){
				return aFe.mClckIt == 2  || aFe.mClckIt== -2;
			}

//			bool checkReverseIteration(FacetEdge const & aFe){
//				return aFe.mRevsIt == 1  || aFe.mRevsIt == -1;
//			}

			bool checkDualIteration(FacetEdge const & aFe){
				return aFe.mDualIt == 1  || aFe.mDualIt == -1;
			}

			FieldIndex const computeJump(FieldIndex const aFi, FieldIndex const aJmp){
				   if (aFi + aJmp > 3) return aJmp-4;
				   if (aFi + aJmp < 0) return 4+aJmp;
				   else return aJmp;
			}

			FacetEdge const * jumpTo(FacetEdge const & aInstance, FieldIndex const aJump){
				auto const jump = computeJump(aInstance.mIndex, aJump);
				auto const * pDest = & aInstance;
				return  (pDest + jump);
			}

			FacetEdge * jumpTo(FacetEdge & aInstance, FieldIndex const aJump){
				//return const_cast<FacetEdge&>(jumpTo(aInstance, aJump));
				 auto const jump = computeJump(aInstance.mIndex, aJump);
				 auto  * pDest = & aInstance;
				 return  (pDest + jump);
			}
		}

		Vertex const * FacetEdge::getOrg() const{
			checkValidPtr(mpDirectedEdgeRing);
			return getDirectedEdgeRing()->getOrg();
		}

		Vertex * FacetEdge::getOrg(){
			return const_cast<Vertex*>(getOrg());
		};

		Vertex const * FacetEdge::getDest() const{
			return getClock()->getOrg();
		};

		Vertex * FacetEdge::getDest(){
			return getClock()->getOrg();
		}

		DirectedEdgeRing const *  FacetEdge::getDirectedEdgeRing() const{
			checkValidPtr(mpDirectedEdgeRing);
			return mpDirectedEdgeRing;
		}

		DirectedEdgeRing * FacetEdge::getDirectedEdgeRing() {
			checkValidPtr(mpDirectedEdgeRing);
			return mpDirectedEdgeRing;
		}


		  FacetEdge const  *	FacetEdge::getDual() const{
			  MUST_BE(checkClockIteration(*this));
			  return jumpTo(*this, mDualIt);
		  }
		  FacetEdge *	FacetEdge::getDual(){
			  MUST_BE(checkClockIteration(*this));
			  return jumpTo(*this, mDualIt);
		  }

//	      FacetEdge const &	FacetEdge::getRev() const{
//	    	  MUST_BE(checkReverseIteration(*this));
//	    	  return jumpTo(*this, mRevsIt);
//	      }
//
//		  FacetEdge &	FacetEdge::getRev(){
//	    	  MUST_BE(checkReverseIteration(*this));
//	    	  return jumpTo(*this, mRevsIt);
//		  }

		  FacetEdge const * FacetEdge::getClock() const{
	    	  MUST_BE(checkClockIteration(*this));
	    	  return jumpTo(*this, mClckIt);
		  }

		  FacetEdge * 	FacetEdge::getClock(){
			  MUST_BE(checkClockIteration(*this));
			 return jumpTo(*this, mClckIt);
		  }

		  FacetEdge const * FacetEdge::getFnext() const{
			  return mpNext;
		  }
		  FacetEdge * FacetEdge::getFnext(){
			  return mpNext;
		  }

		  FacetEdge const * FacetEdge::getInvFnext() const{
			  return getClock()->getFnext()->getClock();
		  }
		  FacetEdge * FacetEdge::getInvFnext(){
			  return getClock()->getFnext()->getClock();
		  }

		  FacetEdge const * FacetEdge::getEnext() const{
			  return getDual()->getFnext()->getDual();
		  }

		  FacetEdge * FacetEdge::getEnext() {
			  return getDual()->getFnext()->getDual();
		  }


		  FacetEdge const * FacetEdge::getInvEnext() const{
			  return getClock()->getEnext()->getClock();
		  }

		  FacetEdge * FacetEdge::getInvEnext(){
			  return getClock()->getEnext()->getClock();
		  }

		  QuaterNode const * FacetEdge::getQuaterNode() const{
			  return reinterpret_cast<QuaterNode const *>( this-mIndex);
		  }

		  QuaterNode * FacetEdge::getQuaterNode(){
			  return reinterpret_cast<QuaterNode *>( this-mIndex);
		  }

		  bool FacetEdge::isPrimal() const{
			  return (mIndex == 0 || mIndex ==2);
		  }

		  bool FacetEdge::isDual() const{
			  return !isPrimal();
		  }







	}
}




