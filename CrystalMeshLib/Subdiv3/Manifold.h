/*
 * Manifold.h
 *
 *  Created on: 17.06.2014
 *      Author: christoph
 */
#pragma once

#include "Subdiv3ForwardDecs.h"

namespace CrystalMesh{

	namespace Subdiv3{



		class Manifold{

		public:

			Manifold();

			Manifold(const Manifold & aSrc);

			FacetEdge * makeFacetEdge();

		private:

			VertexMaintener * mpToVertexMaintener;
			OctoNodeMaintener *  mpToOctoNodeMaintener;
			EdgeRingMaintener * mpToEdgeRingMaintener;
		};


	}
}
