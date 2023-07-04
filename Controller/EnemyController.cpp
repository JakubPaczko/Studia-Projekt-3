#include "EnemyController.h"

EnemyController::EnemyController(EntityContainer &c, Player &p) : con(c), player(p){
}

void EnemyController::update() {
    for(int it = 0; it < con.getSize(); ++it){
        Projectile p (player.getPosition(), player.getCurrentRoom(), player.getDirection(), ENEMY, 10.f);

        Entity *ent = & con.getEntity(it);
        if(con.getEntity(it).getEntType() == ENEMY){
            shoot(con.getEntity(it));
            ent->move(player.getPosition());

        }
        for(int it2 = 0; it2 < con.getSize(); ++it2){
            if(con.getEntity(it2).getEntType() == PROJECTILE and con.getEntity(it2).getParent() == PLAYER and
                    con.getEntity(it2).isAlive()){
                if(con.getEntity(it).entCollisionCheck(con.getEntity(it2))){
                    SoundMgr.playEnemyHitSound();
                    con.getEntity(it).takeDamage(con.getEntity(it2).getDamage());
                    con.getEntity(it2).kill();
                }

            }
        }

    }
}

void EnemyController::shoot(Entity & ent) {
    if(ent.canAttack()){
        SoundMgr.playProjectileSound();
        p = new Projectile(ent.getPosition(), player.getCurrentRoom(), ent.getDirection(), ENEMY, ent.getDamage());
        con.addEntity(p);
        ent.attackResart();
    }
}
