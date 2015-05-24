/*
 * MaintenerTemplate.h
 *
 *  Created on: 19.06.2014
 *      Author: christoph
 */
#pragma once

#include <set>
#include "../Toolbox/Checks.h"

namespace CrystalMesh{

    namespace Subdiv3{

        template<typename Entity>
        class EntityMaintener{

        public:

            EntityMaintener();

            ~EntityMaintener();

            Entity * constructEntity();

            bool const isMyEntity( Entity const & aRef) const;

            void deleteEntity (Entity *apInstance);

            std::set<Entity*> const& getContainer() const;

            size_t size() const;

        private:

            std::set<Entity*> mContainer;
        };



        template<typename Entity>
        EntityMaintener<Entity>::EntityMaintener()
        :mContainer()
        {}

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

        template<typename Entity>
        bool const EntityMaintener<Entity>::isMyEntity( Entity const & aRef) const{
            Entity * pInst = const_cast<Entity*>(&aRef);
            auto found = mContainer.find(pInst);
            return found != mContainer.end();
        }

        template<typename Entity>
        EntityMaintener<Entity>::~EntityMaintener(){
            for (auto current: mContainer){
                    delete current;
            }

            mContainer.clear();
        }

        template<typename Entity>
        typename std::set<Entity*> const& EntityMaintener<Entity>::getContainer() const{
            return mContainer;
        }
        
        template<typename Entity>
        size_t EntityMaintener<Entity>::size()const{
            return mContainer.size();
        }
    }

}

