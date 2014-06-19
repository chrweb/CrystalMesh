/*
 * FacetEdge.cpp
 *
 *  Created on: 18.06.2014
 *      Author: christoph
 */
#include "FacetEdge.h"
#include "Vertex.h"
#include "EdgeRing.h"
#include "../Misc/Checks.h"

namespace CrystalMesh{

	namespace Subdiv3{

		namespace{

			template<typename T>
			void checkValidPtr(T const * ptr){
				MUST_BE(notNullptr(ptr));
			}

			bool checkClockIteration(FacetEdge const & aFe){
				return aFe.mDualIt == 4  || aFe.mDualIt == -4;
			}

			bool checkReverseIteration(FacetEdge const & aFe){
				return aFe.mRevsIt == 1  || aFe.mRevsIt == -1;
			}

			bool checkDualIteration(FacetEdge const & aFe){
				return aFe.mDualIt == 1  || aFe.mDualIt == -1;
			}

			FieldIndex const computeJump(FieldIndex const aFi, FieldIndex const aJmp){
				   if (aFi + aJmp > 7) return aJmp-8;
				   if (aFi + aJmp < 0) return 8+aJmp;
				   else return aJmp;
			}

			FacetEdge const & jumpTo(FacetEdge const & aInstance, FieldIndex const aJump){
				auto const jump = computeJump(aInstance.mIndex, aJump);
				auto const * pDest = & aInstance;
				return * (pDest + jump);
			}

			FacetEdge & jumpTo(FacetEdge & aInstance, FieldIndex const aJump){
				//return const_cast<FacetEdge&>(jumpTo(aInstance, aJump));
				 auto const jump = computeJump(aInstance.mIndex, aJump);
				 auto  * pDest = & aInstance;
				 return * (pDest + jump);
			}
		}

		Vertex const & FacetEdge::getOrg() const{
			checkValidPtr(mpVertex);
			return *mpVertex;
		}

		Vertex & FacetEdge::getOrg(){
			checkValidPtr(mpVertex);
			return *mpVertex;
		};

		Vertex const & FacetEdge::getDest() const{
			return getClock().getOrg();
		};

		Vertex & FacetEdge::getDest(){
			return getClock().getOrg();
		}

		EdgeRing const & FacetEdge::getEdgeRing() const{
			checkValidPtr(mpEdgeRing);
			return *mpEdgeRing;
		}

		EdgeRing & FacetEdge::getEdgeRing() {
			checkValidPtr(mpEdgeRing);
			return *mpEdgeRing;
		}


		  FacetEdge const &	FacetEdge::getDual() const{
			  MUST_BE(checkClockIteration(*this));
			  return jumpTo(*this, mDualIt);
		  }
		  FacetEdge &	FacetEdge::getDual(){
			  MUST_BE(checkClockIteration(*this));
			  return jumpTo(*this, mDualIt);
		  }

	      FacetEdge const &	FacetEdge::getRev() const{
	    	  MUST_BE(checkReverseIteration(*this));
	    	  return jumpTo(*this, mRevsIt);
	      }

		  FacetEdge &	FacetEdge::getRev(){
	    	  MUST_BE(checkReverseIteration(*this));
	    	  return jumpTo(*this, mRevsIt);
		  }

		  FacetEdge const & FacetEdge::getClock() const{
	    	  MUST_BE(checkClockIteration(*this));
	    	  return jumpTo(*this, mClckIt);
		  }

		  FacetEdge& 	FacetEdge::getClock(){
			  MUST_BE(checkClockIteration(*this));
			 return jumpTo(*this, mClckIt);
		  }

		  FacetEdge const & FacetEdge::getFnext() const{
			  return *mpNext;
		  }
		  FacetEdge & FacetEdge::getFnext(){
			  return *mpNext;
		  }

		  FacetEdge const & FacetEdge::getInvFnext() const{
			  return getClock().getFnext().getClock();
		  }
		  FacetEdge & FacetEdge::getInvFnext(){
			  return getClock().getFnext().getClock();
		  }

		  FacetEdge const & FacetEdge::getEnext() const{
			  return getDual().	getFnext().getDual();
		  }

		  FacetEdge & FacetEdge::getEnext() {
			  return getDual().	getFnext().getDual();
		  }


		  FacetEdge const & FacetEdge::getInvEnext() const{
			  return getClock().getEnext().getClock();
		  }

		  FacetEdge & FacetEdge::getInvEnext(){
			  return getClock().getEnext().getClock();
		  }






	}
}




