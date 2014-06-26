/*
 * Corner.h
 *
 *  Created on: 17.06.2014
 *      Author: christoph
 */
#pragma once

#include "Subdiv3ForwardDecs.h"

namespace CrystalMesh{

	namespace Subdiv3{

		/**
		 * An equivalence class for a ring of FacetEdges, forming a ring,
		 */
		struct EdgeRing{

//			template<typename Functor>
//			void forEachRingMember(Functor const & aFunc);

			template<typename Functor>
			void forEachRingMember(Functor const & aFunc) const;

			FacetEdge * mpRingMember;
			void * mpData;
		};



	}
}

