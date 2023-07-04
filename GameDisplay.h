#ifndef ROGALIK_GAMEDISPLAY_H
#define ROGALIK_GAMEDISPLAY_H
#include <SFML/graphics.hpp>
#include <vector>
#include <algorithm>

#include "Entity/Player.h"
#include "Entity/EntityContainer.h"
#include "Entity/Entity.h"
#include "Entity/Projectile.h"
#include "RGmap.h"
#include "Menu.h"

struct viewObject{
    sf::Vector2f pos;
    sf::Sprite Sprite;
};


class GameDisplay{
private:

    std::vector<viewObject> vObject;

    sf::Vector2i screenSize;

    sf::Vector2f boardOffset;

    const int textureSize = 64;

    RGmap &map;
    Player &player;

    sf::Font getFont;


    sf::Texture objecttexture;
    sf::Sprite objectSprite;

    sf::Texture doorTexture;
    sf::Sprite doorSprite;

    sf::Texture floorTexture;
    sf::Texture wallTexture;
    sf::Texture rockTexture;
    sf::Texture pillarTexture;
    sf::Texture barrelTexture;
    sf::Texture candleTexture;
    sf::Texture statueTexture;
    sf::Texture hatchTexture;

    sf::Sprite shape;

    void loadTextures();

    void drawPlayer(sf::RenderWindow & win);

    void drawRoom(sf::RenderWindow & win);

    void drawFloor(sf::RenderWindow & win);

    void drawDoors() ;

    void setPosition(sf::Vector2f pos, sf::Sprite & s);

public:

    void drawEntity(EntityContainer & con, sf::RenderWindow & win);

    GameDisplay(RGmap &Map, Player &Player);

    void draw(sf::RenderWindow & win);

    void debugDisplay(sf::RenderWindow & win);

    void drawMenu(sf::RenderWindow & win, Menu & menu);

    void drawEndScreen(sf::RenderWindow & win, Menu & menu);
};

#endif //ROGALIK_GAMEDISPLAY_H
