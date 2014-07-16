/*
 * DirectedEdgeRing.cpp
 *
 *  Created on: 01.07.2014
 *      Author: christoph
 */
#include "DirectedEdgeRing.h"
#include "FacetEdge.h"
#include "../Misc/Checks.h"
namespace CrystalMesh{
	namespace  Subdiv3 {
		Counter const DirectedEdgeRing::computeEdgeRingSize() const{
			Counter result = 0;
			MUST_BE(notNullptr(mpRingMember));

			auto functor =  [&result](FacetEdge const & ){
				result++;
			};

			forEachElementInFnextRing(*mpRingMember,functor);

			return result;
		}

		DirectedEdgeRing const * DirectedEdgeRing::getSym() const{
			MUST_BE(notNullptr(mpRingMember));
			return mpRingMember->getClock()->getDirectedEdgeRing();
		}
		DirectedEdgeRing * DirectedEdgeRing::getSym(){
			return const_cast<DirectedEdgeRing *>(getSym());
		}

		bool const DirectedEdgeRing::isDual() const{
			return mpRingMember->isDual();
		}

		bool const DirectedEdgeRing::isPrimal() const{
			return !isDual();
		}

		Vertex const * DirectedEdgeRing::getOrg() const{
			return mpOrg;
		}

		Vertex * DirectedEdgeRing::getOrg()
		{
			return mpOrg;
		}

		EdgeRing const * DirectedEdgeRing::getEdgeRing() const{
			MUST_BE(mIndex == 0 || mIndex ==1);
			if (mIndex == 1){
				DirectedEdgeRing const* other = this;
				--other;
				return reinterpret_cast<EdgeRing const*>(other);
			}

			return reinterpret_cast<EdgeRing const*>(this);
		}
		EdgeRing * DirectedEdgeRing::getEdgeRing(){
			return const_cast<EdgeRing*>(getEdgeRing());
		}


	}  // namespace  Subdiv3
};




