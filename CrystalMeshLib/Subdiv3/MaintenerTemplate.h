/*
 * MaintenerTemplate.h
 *
 *  Created on: 19.06.2014
 *      Author: christoph
 */
#pragma once

#include <set>
#include "../Misc/Checks.h"

namespace CrystalMesh{

	namespace Subdiv3{

		template<typename Entity>
		class EntityMaintener{

		public:

			EntityMaintener();

			Entity * constructEntity();

			void deleteEntity (Entity *apInstance);

		private:

			std::set<Entity*> mContainer;
		};



		template<typename Entity>
		EntityMaintener<Entity>::EntityMaintener()
		:mContainer(){}

		template<typename Entity>
		Entity * EntityMaintener<Entity>::constructEntity(){
			auto pInst = new Entity;
	        mContainer.insert(pInst);
	        return pInst;
		}

		template<typename Entity>
		void EntityMaintener<Entity>::deleteEntity(Entity * apInst){
			auto found = mContainer.find(apInst);
			MUST_BE(found != mContainer.end());
			delete *found;
			mContainer.erase(found);
			return;
		}
	}

}

