/*
 * AdjacentDirectedEdgeRings.h
 *
 *  Created on: 21.07.2014
 *      Author: christoph
 */
#pragma once
#include <vector>
#include "Subdiv3ForwardDecs.h"

namespace CrystalMesh {

	namespace Subdiv3 {

		typedef std::vector<DirectedEdgeRing*> AdjacentRings;

		AdjacentRings const getAdjacentRingsOf( Vertex const & aVert);


	}  // namespace Subdiv3

}  // namespace CrystalMesh

