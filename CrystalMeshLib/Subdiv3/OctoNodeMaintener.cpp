/*
 * OctoNodeMaintener.cpp
 *
 *  Created on: 19.06.2014
 *      Author: christoph
 */
#include "OctoNodeMaintener.h"
#include "OctoNode.h"
#include  "../Misc/Checks.h"

namespace CrystalMesh{

	namespace Subdiv3{

		OctoNodeMaintener::OctoNodeMaintener()
			:mContainer()
		{

		}


		OctoNode * OctoNodeMaintener::constructOctoNode(){
			OctoNode * pInst = new OctoNode;
			mContainer.insert(pInst);
			return pInst;
		}

		void OctoNodeMaintener::deleteOctoNode(OctoNode * apNode){
			auto result = mContainer.find(apNode);
			MUST_BE(result != mContainer.end());
			delete *result;
			mContainer.erase(result);
			return;
		}



	}
}



