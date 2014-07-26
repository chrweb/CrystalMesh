/*
 * ForwardDecs.h
 *
 *  Created on: 26.07.2014
 *      Author: christoph
 */
#pragma once
#include <stdint.h>

/**
 * Forward-declared types, often used in Delaunay3:
 *
 */

namespace CrystalMesh {

	namespace Subdiv3{

		class Manifold;

		struct FacetEdge;

		struct DirectedEdgeRing;

		struct Vertex;
	}

	namespace Math{

		namespace Geometry {

			struct Point3D;
		}  // namespace Geometry
	}

	namespace Delaunay3{

		typedef uint32_t Index;
	}

}  // namespace CrystalMesh



