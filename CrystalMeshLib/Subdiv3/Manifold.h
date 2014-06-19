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

		private:

			VertexMaintener * mpToVertexMaintener;
			OctoNodeMaintener *  mpToOctoNodeMaintener;
			CornerMaintener * mpToCornerMaintener;
			FaceMaintener * mpToFaceMaintener;
		};


	}
}
