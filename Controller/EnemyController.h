#ifndef ROGALIK_ENEMYCONTROLLER_H
#define ROGALIK_ENEMYCONTROLLER_H

#include "../Entity/Enemy.h"
#include "../Entity/Player.h"
#include "../Entity/EntityContainer.h"
#include "../Sound//SoundManager.h"

class EnemyController {
private:
    SoundManager SoundMgr;

    EntityContainer & con;
    Entity *p;
    Player &player;
    void shoot(Entity & ent);
public:
    EnemyController(EntityContainer & c, Player & p);
    void update();

};


#endif //ROGALIK_ENEMYCONTROLLER_H
