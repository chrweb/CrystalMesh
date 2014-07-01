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

			DirectedEdgeRing mRings[2];
			void * mpData;
		};



	}
}

