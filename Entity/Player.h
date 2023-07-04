#ifndef ROGALIK_PLAYER_H
#define ROGALIK_PLAYER_H
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cmath>

#include "../RGmap.h"
#include "Entity.h"
#include "Projectile.h"
#include "EntityContainer.h"
#include "Enemy.h"





class Player : public Entity{
private:


    sf::Clock animationClock;

    sf::Sprite playerSprite;
    sf::Texture playerTexture;

    void playAnimation();

    std::string texturePath = "../Textures/PlayerSheet1.png";
    void loadTexture();

    void doorCollision();
    void move(sf::Vector2f moveVector) override;


public:
    explicit Player(sf::Vector2f pos, sf::Vector2i room);

    ~Player() override;

    void update() override;

    void mapCollision(RGmap & map) override;

    bool canBeDestroyed() override;
};

#endif //ROGALIK_PLAYER_H
