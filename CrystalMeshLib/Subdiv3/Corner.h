/*
 * Corner.h
 *
 *  Created on: 17.06.2014
 *      Author: christoph
 */
#pragma once

namespace CrystalMesh{

	namespace Subdiv3{

		struct FacetEdge;

		struct Corner{

			FacetEdge * mpRingMember;
			void mpData;
		};



	}
}

