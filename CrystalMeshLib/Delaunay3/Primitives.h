/*
 * Primitives.h
 *
 *  Created on: 29.06.2014
 *      Author: christoph
 */
#pragma once

namespace CrystalMesh{

	namespace Subdiv3{

		struct EdgeRing;

		struct Vertex;


	}

	namespace Delaunay3{

		struct Vertex{
			Subdiv3::Vertex* mpPrimalVertex;
		};

		struct Corner{

		};

		struct Triangle{

			Subdiv3::EdgeRing* mpDualEdgeRing;
		};

		struct Tetraeder{
			Triangle mBounds[4];
		};

	}
}

