#ifndef ROGALIK_ENTITY_H
#define ROGALIK_ENTITY_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

#include "../RGmap.h"



enum Action {IDLE, WALKING, ATTACK, CASTING};
enum Direction {up, down, left, right};
enum EntityType {ENTITY, PLAYER, PROJECTILE, ENEMY};

class Entity {
private:


    EntityType type;
    EntityType parent;
    int frame;

    int maxHP;
    int Hp;
    bool alive = true;

    int damage;

    float acceleration;
    float drag = 0.95f;
    float maxSpeed;
    sf::Vector2f speed;

    sf::Clock killClock;
    sf::Clock damageClock;
    sf::Clock attackClock;

    sf::Vector2i size;

    sf::Vector2i currentRoom;
    sf::Vector2f position;

    Direction direction;
    Action currentAction;

    std::string texturePath;
    sf::Sprite entSprite;
    sf::Texture entTexture;


public:
    Entity();
    Entity(sf::Vector2f pos, sf::Vector2i room);
    Entity(sf::Vector2f pos, sf::Vector2i room,  Direction dir, EntityType p);

    virtual ~Entity();

    virtual void update();

    void takeDamage(int damage);

    bool canAttack();
    void attackResart();

    void knockback(Direction getDir);

    virtual void move(sf::Vector2f moveVector);
    virtual void movePath(RGmap & map, sf::Vector2f targetPos);

    void killClockRestart();

    virtual void kill();
    virtual bool canBeDestroyed();

    bool colisionCheck(sf::Vector2f pos, sf::Vector2i getSize);
    bool entCollisionCheck(Entity& targetEntity);
    void collisionPush(float posX, float posY, sf::Vector2i getSize);
    void entCollisionPush(Entity& targetEntity);
    virtual void mapCollision(RGmap & map);
    virtual void mapBorderCollision();

    void setHp(int getHp);
    void setMaxHp(int getMaxHp);
    void setSprite(sf::Sprite & sprite);
    void setSize(sf::Vector2i size);
    void setPosition(sf::Vector2f pos);
    void setDirection(Direction dir);
    void setDirection(float angle);
    void setAction(Action action);
    void setAlive(bool setAlive);
    void setEntityType(EntityType getType);
    void setCurrentRoom(sf::Vector2i roomPos);
    void setDamage(int dmg);
    void setFrame(int f);
    void setAcceleration(float acc);
    void setMaxSpeed(float getSpeed);
    void setSpeed(sf::Vector2f getSpeed);

    bool isAlive() const;
    int getHp() const;
    virtual sf::Sprite getSprite() const;
    virtual Action getAction() const;
    sf::Vector2i getSize() const;
    sf::Vector2f getPosition() const;
    Direction getDirection() const;
    sf::Vector2i getCurrentRoom() const;
    EntityType getEntType() const;
    EntityType getParent();
    int getDamage();
    int getFrame() const;
    float getDrag();
    float getAcceleration();
    float getMaxSpeed();
    sf::Vector2f getSpeed();

};


#endif //ROGALIK_ENTITY_H
