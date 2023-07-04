#include "Entity.h"

Entity::Entity(sf::Vector2f pos, sf::Vector2i room) {
    direction = down;
    position = pos;
    currentRoom = room;
    setSize(sf::Vector2i(1, 1));
}

Entity::Entity(sf::Vector2f pos, sf::Vector2i room, Direction dir, EntityType p){
    currentAction = IDLE;
    type = PROJECTILE;
    frame = 0;
    parent = p;
    maxHP = 1;
    Hp = 1;
    direction = dir;
    position = pos;
    currentRoom = room;
}

Entity::Entity() {

}

Entity::~Entity() {

}

void Entity::update() {
}

void Entity::move(sf::Vector2f moveVector) {

}


bool Entity::canAttack() {
    sf::Time attackTimer = attackClock.getElapsedTime();

    if(attackTimer.asMilliseconds() > (5000 + rand() % 1000) and isAlive()) {
        attackClock.restart();
        return true;
    }
    return false;

}

void Entity::attackResart() {
}



void Entity::movePath(RGmap &map, sf::Vector2f targetPos) {


}

void Entity::kill() {
    if(isAlive()){
        frame = 0;
        setAlive(false);
    }
}

void Entity::takeDamage(int damage) {
    sf::Time damageTimer = damageClock.getElapsedTime();

    if(damageTimer.asMilliseconds() > 200){
        damageClock.restart();

        Hp -= damage;
        if(Hp <= 0 ){
            alive = false;
            Hp = 0;
        }
    }

}

bool Entity::canBeDestroyed() {
    sf::Time killTimer = killClock.getElapsedTime();
    if(killTimer.asMilliseconds() > 1500){
        return true;
    }
    return false;
}


bool Entity::entCollisionCheck(Entity &targetEntity) {
    sf::Vector2f targetPos = targetEntity.getPosition();
    sf::Vector2i targetSize = targetEntity.getSize();

    float deltaX = std::abs(targetPos.x - position.x) - (float) (targetSize.x + size.x) / 2;
    float deltaY = std::abs(targetPos.y - position.y) - (float) (targetSize.y + size.y) / 2;

    if (deltaX < 0 and deltaY < 0) {
        if (getEntType() == PLAYER and targetEntity.getEntType() == PROJECTILE and targetEntity.isAlive()
        and targetEntity.getParent() != PLAYER) {

            targetEntity.kill();
            takeDamage(10);
        }
        if (getEntType() == ENEMY and targetEntity.getEntType() == PROJECTILE and targetEntity.isAlive()
            and targetEntity.getParent() != ENEMY) {

            knockback(targetEntity.getDirection());
            targetEntity.kill();
            takeDamage(10);
        }

        return true;
    }

    return false;
}

void Entity::mapCollision(RGmap &map) {

    roomObjects object;

    for (int posX = 0; posX < map.getRoomSize().x; ++posX) {
        for (int posY = 0; posY < map.getRoomSize().y; ++posY) {
            object = map.getRoomObject(currentRoom, sf::Vector2i(posX, posY));

            if (!map.isObjWalkable(object)) {
                float deltaX = std::abs((float) posX - position.x) - (1.f + (float) size.x) / 2;
                float deltaY = std::abs((float) posY - position.y) - (1.f + (float) size.y) / 2;


                if (deltaX < 0 and deltaY < 0) {
                    collisionPush((float) posX, (float) posY, {1, 1});
//                    kill();
                }
            }
        }
    }

}

void Entity::collisionPush(float posX, float posY, sf::Vector2i getSize) {

    float deltaX = std::abs((float) posX - position.x) - (float) (getSize.x + size.x) / 2;
    float deltaY = std::abs((float) posY - position.y) - (float) (getSize.y + size.y) / 2;

    // X axis collision
    if (deltaX > deltaY) {
        if (posX > position.x) {
            position.x = posX - 1;
        }
        if (posX < position.x) {
            position.x = posX + 1;
        }
    }
        // Y axis collision
    else if (deltaX < deltaY) {
        if (posY > position.y) {
            position.y = posY - 1;
        }
        if (posY < position.y) {
            position.y = posY + 1;
        }
    }
}

void Entity::mapBorderCollision() {
    if (position.x < 1)
        position.x = 1;
    if (position.x > roomSizeX - 2)
        position.x = roomSizeX - 2;

    if (position.y < 1)
        position.y = 1;
    if (position.y > roomSizeY - 2)
        position.y = roomSizeY - 2;

}


//Setters

void Entity::setHp(int getHp) {
    Hp = getHp;
}

void Entity::setMaxHp(int getMaxHp) {
    maxHP = getMaxHp;
}

void Entity::setSprite(sf::Sprite &sprite) {
    entSprite = sprite;
}

void Entity::setSize(sf::Vector2i s) {
    size = s;
}

void Entity::setPosition(sf::Vector2f pos) {
    position = pos;
}

void Entity::setDirection(Direction dir) {
    direction = dir;
}

void Entity::setDirection(float angle) {
    double pi = 3.14159265359;
    float an = angle * (180/pi);

    if( an < 45.f and an > -45.f){
        direction = left;
    }
    if( an < 135.f and an > 45.f){
        direction = up;
    }
    if( an > -135.f and an > 135.f){
        direction = right;
    }
    if( an > -135.f and an < -45.f){
        direction = down;
    }
}

void Entity::setAction(Action action) {
    currentAction = action;
}

void Entity::setCurrentRoom(sf::Vector2i roomPos) {
    currentRoom = roomPos;
}

void Entity::setAlive(bool setAlive) {
    alive = setAlive;
}

void Entity::setEntityType(EntityType getType) {
    type = getType;
}

void Entity::setFrame(int f) {
    frame = f;
}

void Entity::setDamage(int dmg) {
    damage = dmg;
}

void Entity::setAcceleration(float acc) {
    acceleration = acc;
}

void Entity::setMaxSpeed(float speed) {
    maxSpeed = speed;
}

void Entity::setSpeed(sf::Vector2f getSpeed) {
    speed = getSpeed;
}

//Getters

int Entity::getHp() const {
    return Hp;
}


bool Entity::isAlive() const{
    return alive;
}

sf::Vector2f Entity::getPosition() const {
    return position;
}

Action Entity::getAction() const {
    return currentAction;
}

Direction Entity::getDirection() const {
    return direction;
}

sf::Vector2i Entity::getCurrentRoom() const {
    return currentRoom;
}

sf::Vector2i Entity::getSize() const {
    return size;
}

sf::Sprite Entity::getSprite() const {
    return entSprite;
}

EntityType Entity::getEntType() const{
    return type;
}

int Entity::getFrame() const{
    return frame;
}

EntityType Entity::getParent() {
    return parent;
}

int Entity::getDamage() {
    return damage;
}

void Entity::killClockRestart() {
    killClock.restart();
}

float Entity::getDrag() {
    return drag;
}

float Entity::getAcceleration() {
    return acceleration;
}

float Entity::getMaxSpeed() {
    return maxSpeed;
}

sf::Vector2f Entity::getSpeed() {
    return speed;
}

void Entity::knockback(Direction getDir) {
    switch (getDir) {
        case up:
            speed.y = -maxSpeed;
            break;
        case down:
            speed.y = maxSpeed;
            break;
        case left:
            speed.x = -maxSpeed;
            break;
        case right:
            speed.x = maxSpeed;
            break;
    }

}

void Entity::entCollisionPush(Entity &targetEntity) {
    sf::Vector2f pos = targetEntity.getPosition();
    sf::Vector2i size = targetEntity.getSize();

    collisionPush(pos.x, pos.y, size);

}

bool Entity::colisionCheck(sf::Vector2f pos, sf::Vector2i getSize) {

    float deltaX = std::abs(pos.x - position.x) - (float) (getSize.x + size.x) / 2;
    float deltaY = std::abs(pos.y - position.y) - (float) (getSize.y + size.y) / 2;

    if (deltaX < 0 and deltaY < 0) {
        return true;
    }

    return false;
}









