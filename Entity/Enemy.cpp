#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos, sf::Vector2i room, int level) : Entity(pos, room){
    loadTexture();
    setSize(sf::Vector2i(1, 2));
    setDamage(10 * level * 0.5 );
    setMaxHp(100 * level * 0.5);
    setHp(100 * level * 0.5);
    setEntityType(ENEMY);
    setAcceleration(0.001f);
    setMaxSpeed(0.01f);
    setSpeed({0.f, 0.f});
}

Enemy::~Enemy() = default;


void Enemy::update() {
    if(isAlive()){
        killClockRestart();
    }
    if(getHp() <= 0)
        setAlive(false);
    mapBorderCollision();
    playAnimation();
}

void Enemy::goTo(sf::Vector2f pos) {

}

void Enemy::move(sf::Vector2f moveVector) {
    sf::Vector2f currSpeed = getSpeed();

    if (isAlive()) {
        sf::Vector2f pos = getPosition();
        float acc = getAcceleration();
        sf::Vector2f targetPos = moveVector;
        float angle = atan2f(pos.y - targetPos.y, pos.x - targetPos.x);
        currSpeed = { currSpeed.x -=  cosf(angle) * acc, currSpeed.y -= sinf(angle) * acc};


        setDirection(angle);
    }

    setSpeed(currSpeed);

    setSpeed({getSpeed().x * getDrag(), getSpeed().y * getDrag()});

    if(getSpeed().x > getMaxSpeed()) {
        setSpeed({getMaxSpeed(), getSpeed().y});
    }

    else if(std::abs(getSpeed().x) > getMaxSpeed()) {
        setSpeed({-getMaxSpeed(), getSpeed().y});
    }

    if(getSpeed().y > getMaxSpeed()) {
        setSpeed({getSpeed().y, getMaxSpeed()});
    }

    else if(std::abs(getSpeed().y) > getMaxSpeed()) {
        setSpeed({getSpeed().y, -getMaxSpeed()});
    }


    setPosition(getPosition() + currSpeed);

}

sf::Sprite Enemy::getSprite() const{
    return enemySprite;
}

void Enemy::playAnimation(){
    enemySprite.setPosition(getPosition().x * 64, getPosition().y * 64);
    enemySprite.setOrigin(8, 16);
    enemySprite.setScale(4, 4);
}

void Enemy::loadTexture() {
    if(!enemyTexture.loadFromFile(texturePath)){
        return;
    }
    enemySprite.setTexture(enemyTexture);
}

void Enemy::movePath(RGmap &map, sf::Vector2f targetPos) {
    sf::Vector2i currentRoom = getCurrentRoom();


}


