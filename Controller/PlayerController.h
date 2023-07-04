#ifndef ROGALIK_PLAYERCONTROLLER_H
#define ROGALIK_PLAYERCONTROLLER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../Entity/EntityContainer.h"
#include "../Entity/Entity.h"
#include "../Entity/Player.h"
#include "../Entity/Projectile.h"
#include "../Sound/SoundManager.h"
#include "../GameManager.h"
#include "../RGmap.h"


class PlayerController {

    SoundManager SoundMgr;

    sf::Clock spellClock;
    sf::Clock attackClock;

    sf::Clock castDurationClock;
    sf::Clock attackDurationClock;

    float velocity = 0.1f;

    Player &player;

    EntityContainer & con;
    GameManager & GameMgr;
    Entity *p;


    void move();
    void attack();
    void shoot();


public:
    explicit PlayerController(Player & p, EntityContainer & c, GameManager & g);

    void update(RGmap & map);


    void getInput();


};


#endif //ROGALIK_PLAYERCONTROLLER_H
