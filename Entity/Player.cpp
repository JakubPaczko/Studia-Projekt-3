#include "Player.h"
#include <iostream>


Player::Player(sf::Vector2f pos, sf::Vector2i room) : Entity(pos, room){
    loadTexture();
    setDirection(down);
    setMaxHp(100);
    setHp(5);
    setAction(IDLE);
    setEntityType(PLAYER);
    setDamage(10);
    setCurrentRoom(sf::Vector2i(3, 3));
}

Player::~Player(){
}


void Player::update() {

    doorCollision();
    playAnimation();
}

void Player::move(sf::Vector2f moveVector) {
    if(isAlive()){
        setPosition(moveVector);
    }
}

//Private

void Player::playAnimation() {
    int frame = getFrame();
    int idleFramecount = 5;
    int runFrameCount = 8;
    int castFrameCount = 5;
    int attackFrameCount = 5;

    sf::Time frameTime = animationClock.getElapsedTime();
    Action currentAction = getAction();
    playerSprite.setTexture(playerTexture);
    playerSprite.setScale(4, 4);
    playerSprite.setOrigin(8, 16);
    playerSprite.setPosition({getPosition().x * 64, getPosition().y * 64});
    static int textureTop = 0;

    switch (currentAction) {
        case IDLE:
            if(frameTime.asMilliseconds() >= 100){
                animationClock.restart();
               if(getDirection() == right or getDirection() == up){
                   textureTop = 2;
               }
               if(getDirection() == left or getDirection() == down){
                   textureTop = 3;
               }
                ++frame;
                if(frame >= idleFramecount)
                    frame =0;
            }
            break;
        case WALKING:
            if(frameTime.asMilliseconds() >= 100){
                animationClock.restart();
                if(getDirection() == right or getDirection() == up){
                    textureTop = 0;
                }
                if(getDirection() == left or getDirection() == down){
                    textureTop = 1;
                }
                ++frame;
                if(frame >= runFrameCount)
                    frame = 0;
            }
            break;
        case CASTING:
            if(frameTime.asMilliseconds() >= 100){
                animationClock.restart();
                if(getDirection() == right or getDirection() == up){
                    textureTop = 6;
                }
                if(getDirection() == left or getDirection() == down){
                    textureTop = 7;
                }
                ++frame;
                if(frame >= castFrameCount)
                    frame = 0;
            }
            break;
        case ATTACK:
            if(frameTime.asMilliseconds() >= 100){
                animationClock.restart();
                if(getDirection() == right or getDirection() == up){
                    textureTop = 4;
                }
                if(getDirection() == left or getDirection() == down){
                    textureTop = 5;
                }
                ++frame;
                if(frame >= attackFrameCount)
                    frame = 0;
            }
            break;
    }
    playerSprite.setTextureRect({frame * 32, textureTop  * 32, 32, 32});
    setFrame(frame);

    setSprite(playerSprite);
}

void Player::loadTexture() {
    if(!playerTexture.loadFromFile(texturePath)){
        return;
    }
}

bool Player::canBeDestroyed() {
    return false;
}

void Player::doorCollision() {
    sf::Vector2i roomPos = getCurrentRoom();
    sf::Vector2f pos = getPosition();
    if(getPosition().x < 0.5f){
        setCurrentRoom({roomPos.x - 1, roomPos.y});
        setPosition({pos.x + roomSizeX - 3, pos.y});
    }
    if(getPosition().x > roomSizeX - 1.5){
        setCurrentRoom({roomPos.x + 1, roomPos.y});
        setPosition({pos.x - roomSizeX + 3, pos.y});
    }
    if(getPosition().y < 0.5f){
        setCurrentRoom({roomPos.x, roomPos.y - 1});
        setPosition({pos.x , pos.y + roomSizeY - 3});
    }
    if(getPosition().y > roomSizeY - 1.5){
        setCurrentRoom({roomPos.x, roomPos.y + 1});
        setPosition({pos.x, pos.y - roomSizeY + 3});
    }
}

void Player::mapCollision(RGmap &map) {
    sf::Vector2f position = getPosition();
    sf::Vector2i size = getSize();
    sf::Vector2i currentRoom = getCurrentRoom();
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

    if(map.getEnemyCount(currentRoom.x, currentRoom.y) > 0){
        mapBorderCollision();
    }
}
