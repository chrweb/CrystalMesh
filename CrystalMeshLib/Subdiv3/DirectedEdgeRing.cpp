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

const FacetEdge* DirectedEdgeRing::getRingMember() const {
	return mpRingMember;
}

FacetEdge* DirectedEdgeRing::getRingMember() {
	return mpRingMember;
}

const Counter DirectedEdgeRing::computeEdgeRingSize() const {
	Counter result = 0;
	MUST_BE (notNullptr(mpRingMember));auto
	functor = [&result](const FacetEdge&) {
		result++;
	};
	forEachElementInFnextRing(*mpRingMember, functor);
	return result;
}

const DirectedEdgeRing* DirectedEdgeRing::getSym() const {
	MUST_BE (notNullptr(mpRingMember));
	return mpRingMember->getClock()->getDirectedEdgeRing();
}

DirectedEdgeRing* DirectedEdgeRing::getSym() {
	MUST_BE (notNullptr(mpRingMember));
	return mpRingMember->getClock()->getDirectedEdgeRing();
}

const bool DirectedEdgeRing::isDual() const {
	return mpRingMember->isDual();
}

const bool DirectedEdgeRing::isPrimal() const {
	return !isDual();
}

const Vertex* DirectedEdgeRing::getOrg() const {
	return mpOrg;
}

Vertex* DirectedEdgeRing::getOrg() {
	return mpOrg;
}

const EdgeRing* DirectedEdgeRing::getEdgeRing() const {
	MUST_BE(mIndex == 0 || mIndex == 1);
	if (mIndex == 1) {
		const DirectedEdgeRing* other = this;
		--other;
		return reinterpret_cast<const EdgeRing*>(other);
	}
	return reinterpret_cast<const EdgeRing*>(this);
		}
		EdgeRing * DirectedEdgeRing::getEdgeRing(){
			return const_cast<EdgeRing*>(getEdgeRing());
		}


	}  // namespace  Subdiv3
};




