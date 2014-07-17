/*
 * Corner.h
 *
 *  Created on: 17.06.2014
 *      Author: christoph
 */
#pragma once

#include "Subdiv3ForwardDecs.h"
#include "DirectedEdgeRing.h"

namespace CrystalMesh{

	namespace Subdiv3{


		struct EdgeRing{

			bool const isDual() const;

			bool const isPrimal() const;

			Counter const computeEdgeRingSize() const;

			DirectedEdgeRing & operator[](FieldIndex aIndex);

			DirectedEdgeRing const & operator[](FieldIndex aIndex) const;

			DirectedEdgeRing mRings[2];
		};



	}
}

