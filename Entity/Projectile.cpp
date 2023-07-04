#include "Projectile.h"

Projectile::Projectile(sf::Vector2f Pos, sf::Vector2i room, Direction Dir, EntityType p, float dmg)
    : Entity(Pos, room, Dir, p){
    setEntityType(PROJECTILE);
    setDamage(dmg);
    loadTexture();
}

Projectile::~Projectile(){
//std::cout << "Destroyed" << "\n";
};

void Projectile::update() {
    mapBorderCollision();
    playAnimation();
    move({0,0});
    if(isAlive()){
        killClockRestart();
    }
}

//void Projectile::kill() {
//    if(isAlive()){
//        frame = 0;
//        std::cout << frame << "\n";
//        setAlive(false);
//    }
//}
//
//bool Projectile::canBeDestroyed() {
//    sf::Time killTimer = killClock.getElapsedTime();
//    if(killTimer.asMilliseconds() > 1500){
//        return true;
//    }
//    return false;
//}


void Projectile::move(sf::Vector2f moveVector) {
    if(isAlive()){
        Direction direction = getDirection();
        sf::Vector2f position = getPosition();
        switch (direction) {
            case up:
                setPosition(sf::Vector2f(position.x, position.y - velocity));
                break;
            case down:
                setPosition(sf::Vector2f(position.x, position.y + velocity));
                break;
            case left:
                setPosition(sf::Vector2f(position.x - velocity, position.y));
                break;
            case right:
                setPosition(sf::Vector2f(position.x + velocity, position.y));
                break;
        }
    }
}
//Private:
void Projectile::playAnimation() {
    frame = getFrame();
    sf::Time animationTime = animationClock.getElapsedTime();
    int frameTime = 100;
    int frameCount = 8;
    int textureRow;

    projectileSprite.setTexture(projectileTexture);
    projectileSprite.setScale(4, 4);


    switch (getDirection()) {
        case up:
            textureRow = 0;
            break;
        case down:
            textureRow = 1;
            break;
        case left:
            textureRow = 2;
            break;
        case right:
            textureRow = 3;
            break;
    }
    if (animationTime.asMilliseconds() > frameTime) {
        ++frame;
        animationClock.restart();
    }

    if(isAlive()){

        projectileSprite.setTextureRect({frame * 16, textureRow * 16, 16, 16});
        projectileSprite.setPosition(getPosition().x * 64, getPosition().y * 64);


        if (frame >= frameCount) {
            frame = 0;
        }
    }
    else if(!isAlive()){
        projectileSprite.setTextureRect({frame * 16, 4 * 16, 16, 16});
        projectileSprite.setPosition(getPosition().x * 64, getPosition().y * 64);

    }
    setFrame(frame);
}

void Projectile::loadTexture() {
    if (!projectileTexture.loadFromFile(texturePath)){
        return;
    }
}

sf::Sprite Projectile::getSprite() const{
    return projectileSprite;
}

void Projectile::mapBorderCollision() {
    sf::Vector2f position = getPosition();

    if(position.x < 0 or position.x > roomSizeX - 2 or position.y < 0 or position.y > roomSizeY - 2)
        this->kill();
}

void Projectile::mapCollision(RGmap &map) {
    roomObjects object;
    sf::Vector2f position = getPosition();
    sf::Vector2i currentRoom = getCurrentRoom();
    sf::Vector2i size = getSize();


    for(int posX = 0; posX < map.getRoomSize().x; ++posX){
        for(int posY = 0; posY < map.getRoomSize().y; ++posY) {
            object = map.getRoomObject(currentRoom, sf::Vector2i(posX, posY));

            if(!map.isObjWalkable(object)){
                float deltaX = std::abs((float) posX - position.x) - (1.f + (float) size.x)/2;
                float deltaY = std::abs((float) posY - position.y) - (1.f + (float) size.y)/2;


                if(deltaX < 0 and deltaY < 0){
                    kill();
                }
            }
        }
    }
}
