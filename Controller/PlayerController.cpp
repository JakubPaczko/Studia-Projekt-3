#include "PlayerController.h"

PlayerController::PlayerController(Player &p, EntityContainer & c, GameManager & g) : player(p), con(c), GameMgr(g){
}

void PlayerController::getInput() {
    attack();
    shoot();
    if(player.getAction() != ATTACK and player.getAction() != CASTING){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.setPosition({player.getPosition().x, player.getPosition().y + velocity});
            player.setAction(WALKING);
            player.setDirection(down);
            return;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.setPosition({player.getPosition().x, player.getPosition().y - velocity});
            player.setAction(WALKING);
            player.setDirection(up);
            return;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.setPosition({player.getPosition().x - velocity, player.getPosition().y});
            player.setAction(WALKING);
            player.setDirection(left);
            return;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.setPosition({player.getPosition().x + velocity, player.getPosition().y});
            player.setAction(WALKING);
            player.setDirection(right);
            return;
        }
        player.setAction(IDLE);
    }

}

void PlayerController::shoot() {
    sf::Time spellTime = spellClock.getElapsedTime();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::J) and spellTime.asSeconds() > 1){
        SoundMgr.playCastSound();
        player.setFrame(0);
        player.setAction(CASTING);
        spellClock.restart();
        castDurationClock.restart();
    }

    sf::Time spellDurationTimer = castDurationClock.getElapsedTime();

    if(player.getAction() == CASTING and spellDurationTimer.asMilliseconds() > 500) {
        SoundMgr.playProjectileSound();
        sf::Vector2f pos = player.getPosition();
        p = new Projectile({pos.x, pos.y - 0.5f}, player.getCurrentRoom(), player.getDirection(), PLAYER, 10.f);
        con.addEntity(p);
        player.setFrame(0);

        player.setAction(IDLE);
    }


}

void PlayerController::attack() {

    sf::Time attackTimer = attackClock.getElapsedTime();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::K) and attackTimer.asSeconds() > 0.5){

        SoundMgr.playAttackSound();
        player.setFrame(0);
        player.setAction(ATTACK);
        attackClock.restart();
        attackDurationClock.restart();
    }
    sf::Time attackCastTimer = attackDurationClock.getElapsedTime();


    if(player.getAction() == ATTACK and attackCastTimer.asMilliseconds() > 500){
        player.setAction(IDLE);
        player.setFrame(0);

        for(int it = 0; it < con.getSize(); ++it){
            if(con.getEntity(it).getEntType() == ENEMY){
                if(con.getEntity(it).entCollisionCheck(player)){
                    SoundMgr.playEnemyHitSound();
                    con.getEntity(it).takeDamage(player.getDamage());
                    con.getEntity(it).knockback(player.getDirection());
                }
            }
        }

    }


}

void PlayerController::move() {

}

void PlayerController::update(RGmap & map) {
    for(int row = 0; row < roomSizeY; ++row){
        for(int col = 0; col < roomSizeX; ++col) {
            if(map.getRoomObject(player.getCurrentRoom(), {col, row}) == hatch){
                if(player.colisionCheck({(float)col, (float)row}, {1, 1})){
                    if(map.getEnemyCount(player.getCurrentRoom().x, player.getCurrentRoom().y) == 0){
                    GameMgr.nextLevel();
                    }
                }
            }
        }
    }

    for(int it = 0; it < con.getSize(); ++it){
        if(con.getEntity(it).getEntType() == PROJECTILE and con.getEntity(it).getParent() == ENEMY and
            con.getEntity(it).isAlive()){

            if(player.entCollisionCheck(con.getEntity(it))){
                player.takeDamage(con.getEntity(it).getDamage());
                SoundMgr.playHitSound();
                con.getEntity(it).kill();
            }

        }
    }
    if(player.getHp() <= 0){
        player.setAlive(false);
    }
    if(!player.isAlive()){
        GameMgr.changeGameState(FINISHED);
    }
}

