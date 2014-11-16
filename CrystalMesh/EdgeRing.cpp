/*
 * EdgeRing.cpp
 *
 *  Created on: 01.07.2014
 *      Author: christoph
 */
#include "EdgeRing.h"
#include  "../Toolbox/Checks.h"

namespace CrystalMesh {

	using namespace Subdiv3;

const Counter EdgeRing::computeEdgeRingSize() const {
	const auto c0 = mRings[0].computeEdgeRingSize();
	const auto c1 = mRings[1].computeEdgeRingSize();
	MUST_BE(c0 == c1);
	return c0;
}

const bool Subdiv3::EdgeRing::isDual() const {
	return mRings[0].isDual();
}

const bool Subdiv3::EdgeRing::isPrimal() const {
	return !isDual();
}


const DirectedEdgeRing& EdgeRing::operator [](FieldIndex aIndex) const{
	MUST_BE(aIndex < 2);
	return mRings[aIndex];
}

DirectedEdgeRing & EdgeRing::operator [](FieldIndex aIndex){
	MUST_BE(aIndex < 2);
	return mRings[aIndex];
}

DirectedEdgeRing const & EdgeRing::getItem(FieldIndex aIndex) const{
	return this->operator[](aIndex);
}

DirectedEdgeRing & EdgeRing::getItem(FieldIndex aIndex){
	return this->operator[](aIndex);
}



}  // namespace CrystalMesh;




