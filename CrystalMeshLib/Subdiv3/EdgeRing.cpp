/*
 * EdgeRing.cpp
 *
 *  Created on: 01.07.2014
 *      Author: christoph
 */
#include "EdgeRing.h"
#include  "../Misc/Checks.h"

namespace CrystalMesh {

	using namespace Subdiv3;

	Counter const EdgeRing::computeEdgeRingSize() const{

		auto const c0 = mRings[0].computeEdgeRingSize();
		auto const c1 = mRings[1].computeEdgeRingSize();

		MUST_BE(c0 == c1);

		return c0;
	}



}  // namespace CrystalMesh;




