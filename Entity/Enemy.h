#ifndef ROGALIK_ENEMY_H
#define ROGALIK_ENEMY_H


#include "Entity.h"
#include "EntityContainer.h"


class Enemy : public Entity{
private:

    sf::Clock moveClock;

    sf::Clock animationClock;
    void playAnimation();


    sf::Sprite enemySprite;
    sf::Texture enemyTexture;
    std::string texturePath = "../Textures/Enemy.png";
    void loadTexture();

    void goTo(sf::Vector2f pos);

public:

    Enemy(sf::Vector2f pos, sf::Vector2i room, int level);
    ~Enemy();

    void update() override;
    void move(sf::Vector2f moveVector) override;
    void movePath(RGmap & map, sf::Vector2f targetPos) override;

    sf::Sprite getSprite() const override;




};


#endif //ROGALIK_ENEMY_H
