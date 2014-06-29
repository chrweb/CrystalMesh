/*
 * DirectedEdgeRing.h
 *
 *  Created on: 29.06.2014
 *      Author: christoph
 */
#pragma once

#include "Subdiv3ForwardDecs.h"

namespace CrystalMesh{

	namespace Subdiv3{

	    /**
		* An equivalence class for a ring of FacetEdges, forming a ring,
		*/
		struct DirectedEdgeRing{

			FacetEdge * mpRingMember;

			template<typename Functor>
			void forEachRingMember(Functor const & aFunc) const;
		};
	}
}
