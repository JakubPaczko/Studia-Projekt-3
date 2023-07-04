#ifndef ROGALIK_ENTITYCONTAINER_H
#define ROGALIK_ENTITYCONTAINER_H
#include <vector>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "../RGmap.h"

class EntityContainer {
std::vector<Entity*> Container;
RGmap & map;
    Entity getPlayer();
public:
    explicit EntityContainer(RGmap & m);

    Entity &getEntity(int id);


    int getSize();

    void addEntity(Entity *add);
    void destroyEntity(int id);
    void clear();

    void update();

    sf::Sprite getEntSprite(int id);
};


#endif //ROGALIK_ENTITYCONTAINER_H
