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





	}  // namespace  Subdiv3
};




