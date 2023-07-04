#ifndef ROGALIK_PROJECTILE_H
#define ROGALIK_PROJECTILE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Entity.h"


class Projectile : public Entity{
private:
    sf::Clock animationClock;

    int frame{};

    float Damage{};

    float velocity = 0.2f;

    sf::Sprite projectileSprite;
    sf::Texture projectileTexture;

    void playAnimation();

    std::string texturePath = "../Textures/Fireball.png";
    void loadTexture();

public:

    sf::Sprite getSprite() const override;

    Projectile(sf::Vector2f Pos, sf::Vector2i room, Direction Dir, EntityType p, float dmg);

    ~Projectile() override;

    void update() override;

    void mapCollision(RGmap & map) override;

    void mapBorderCollision() override;

//    void kill() override;
//    bool canBeDestroyed() override;

    void move(sf::Vector2f moveVector) override;
};


#endif //ROGALIK_PROJECTILE_H
