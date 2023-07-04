#include "EntityContainer.h"

EntityContainer::EntityContainer(RGmap & m) : map(m) {
}

Entity & EntityContainer::getEntity(int id) {
    return *Container[id];
}

void EntityContainer::addEntity(Entity *add) {
    Container.push_back(add);
}

void EntityContainer::destroyEntity(int id) {
    Container.erase (Container.begin() + id);
}

int EntityContainer::getSize() {
    return Container.size();
}

void EntityContainer::update() {
        for(int it = 0; it < Container.size(); ++it){

            Container[it]->update();
            Container[it]->mapCollision(map);

            if(Container[it]->canBeDestroyed()){
                destroyEntity(it);
            }
//            for(int i = 0; i < Container.size(); ++i and i != it){
//                if(Container[it]->entCollisionCheck(*Container[i]) and  Container[it]->getEntType() != PROJECTILE
//                and Container[i]->getEntType() != PROJECTILE){
//                    Container[it]->entCollisionPush(*Container[i]);
//                }
//            }
        }
}

sf::Sprite EntityContainer::getEntSprite(int id) {
    return Container[id]->getSprite();
}

Entity EntityContainer::getPlayer() {
    return *Container[0];
}

void EntityContainer::clear() {
    
    Container.erase(Container.begin() + 1, Container.end());
}
