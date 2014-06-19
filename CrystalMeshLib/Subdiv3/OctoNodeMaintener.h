/*
 * OctoNodeMaintener.h
 *
 *  Created on: 19.06.2014
 *      Author: christoph
 */
#pragma once
#include <set>
#include "Subdiv3ForwardDecs.h"

namespace CrystalMesh{

	namespace Subdiv3{

		class OctoNodeMaintener{

		public:

			OctoNodeMaintener();

			OctoNode * constructOctoNode();

			void deleteOctoNode(OctoNode * apNode);

		private:

			std::set<OctoNode*> mContainer;

		};

	}
}

