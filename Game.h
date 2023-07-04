#ifndef ROGALIK_GAME_H
#define ROGALIK_GAME_H
#include <SFML/graphics.hpp>

#include "Entity/Player.h"
#include "RGmap.h"
#include "GameDisplay.h"
#include "Entity/Entity.h"
#include "GameManager.h"
#include "Controller/EnemyController.h"

class Game{

    GameManager *GameMgr;
    RGmap *map;
    sf::RenderWindow *win;
    sf::Event event;
    Player* player;
    GameDisplay* Display;
    EntityContainer* con;


public:

    Game();

    void play();

};


#endif //ROGALIK_GAME_H
