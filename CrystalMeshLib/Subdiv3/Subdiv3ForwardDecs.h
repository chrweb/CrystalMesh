/*
 * Subdiv3ForwardDecs.h
 *
 *  Created on: 18.06.2014
 *      Author: christoph
 *
 *      Declare some types for the 3D manifold
 */
#pragma once

#include <stdint.h>

namespace CrystalMesh{

	namespace Subdiv3{

		/**
		 * Declare Prototypes for the manifold
		 */

		struct Vertex;

		struct FacetEdge;

		struct EdgeRing;

		struct Face;

		struct OctoNode;

		class Manifold;

		/**
		 * Define some types
		 */

		typedef uint8_t FieldIndex;


	}
}

