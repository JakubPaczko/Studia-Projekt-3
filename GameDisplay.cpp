#include <iostream>
#include "GameDisplay.h"
#include "string"



GameDisplay::GameDisplay(RGmap &Map, Player &Player) : map(Map), player(Player){
    screenSize.x = 1280;
    screenSize.y = 720;

    boardOffset.x = (float)screenSize.x / 2 - (float)(roomSizeX * textureSize)/2;
    boardOffset.y = (float)screenSize.y / 2 - (float)(roomSizeY * textureSize)/2;


    this->loadTextures();
    sf::Font font{getFont};
    doorSprite.setTexture(doorTexture);
    objectSprite.setTexture(objecttexture);


}

//Ta funkcja została wzieta z https://stackoverflow.com/questions/4892680/sorting-a-vector-of-structs
bool compareByY(const viewObject &a, const viewObject &b)
{
    return a.pos.y < b.pos.y;
}

void GameDisplay::draw(sf::RenderWindow & win){
//std::cout<<map.getRoomObject(sf::Vector2i(3, 3), sf::Vector2i(0,0));
//    boardOffset = (player.getPlayerPos() - sf::Vector2f (10.f, 4.f) )* -10.f + sf::Vector2f (screenSize.x / 2 - 8 * textureSize, screenSize.y / 2 - 4 * textureSize);

    drawFloor(win);
    drawRoom(win);
    drawPlayer(win);
    drawDoors();

    std::sort(vObject.begin(), vObject.end(), compareByY);

    for(int it = 0; it < vObject.size(); ++it){
        setPosition(vObject[it].pos, vObject[it].Sprite);
        win.draw(vObject[it].Sprite);
    }
    vObject.clear();
}

void GameDisplay::drawPlayer(sf::RenderWindow & win){
//    player.draw(win);
}


void GameDisplay::drawRoom(sf::RenderWindow & win){

    sf::Sprite wallSprite{wallTexture};

    objectSprite.setScale(4, 4);
    objectSprite.setOrigin(0, 16);

    wallSprite.setScale((float)textureSize/16, (float)textureSize/16);

    for(int col = 0; col < roomSizeX - 2; col ++) {
        sf::Vector2f pos;
        wallSprite.setTextureRect({16, 0, 16, 16});
        wallSprite.setPosition((float)(col * textureSize) + boardOffset.x + 64, boardOffset.y);
        win.draw(wallSprite);
        wallSprite.setPosition((float)(col * textureSize) + boardOffset.x + 64, boardOffset.y - (float)textureSize );
        win.draw(wallSprite);
        wallSprite.setTextureRect({0, 0, 16, 16});
        wallSprite.setPosition((float)(col * textureSize) + boardOffset.x + 64, boardOffset.y - (float)textureSize * 2);
        win.draw(wallSprite);
    }

    for(int row = 0; row < roomSizeY; row ++){
        for(int col = 0; col < roomSizeX; col ++) {

            if(map.getRoomObject(player.getCurrentRoom(), sf::Vector2i(col ,row)) == rock){
                objectSprite.setTextureRect({0, 0, 16, 32});
                vObject.push_back({{(float) col, (float) row}, objectSprite});
            }
            else if(map.getRoomObject(player.getCurrentRoom(), sf::Vector2i(col ,row)) == barrel){
                objectSprite.setTextureRect({16 * 1, 0, 16, 32});
                vObject.push_back({{(float) col, (float) row}, objectSprite});
            }
            else if(map.getRoomObject(player.getCurrentRoom(), sf::Vector2i(col ,row)) == pillar){
                objectSprite.setTextureRect({16 * 2, 0, 16, 32});
                vObject.push_back({{(float) col, (float) row}, objectSprite});
            }
            else if(map.getRoomObject(player.getCurrentRoom(), sf::Vector2i(col ,row)) == statue){
                objectSprite.setTextureRect({16 * 3, 0, 16, 32});
                vObject.push_back({{(float) col, (float) row}, objectSprite});
            }
            else if(map.getRoomObject(player.getCurrentRoom(), sf::Vector2i(col ,row)) == candle){
                objectSprite.setTextureRect({16 * 4, 0, 16, 32});
                vObject.push_back({{(float) col, (float) row}, objectSprite});
            }
        }
    }
}

void GameDisplay::loadTextures(){

    if(!doorTexture.loadFromFile("../Textures/Door.png")){
        std::cout<<"error: Failed to load texture"<<std::endl;
    }
    if(!floorTexture.loadFromFile("../Textures/Floor.png")){
        std::cout<<"error: Failed to load texture"<<std::endl;
    }
    if(!wallTexture.loadFromFile("../Textures/Wall.png")){
        std::cout<<"error: Failed to load texture"<<std::endl;
    }
    if(!hatchTexture.loadFromFile("../Textures/Hatch.png")){
        std::cout<<"error: Failed to load texture"<<std::endl;
    }
    if(!getFont.loadFromFile("../Font/Gamer.ttf")){
        std::cout<<"error: Failed to load font"<<std::endl;
    }
    if(!objecttexture.loadFromFile("../Textures/RoomObjects.png")){
        std::cout<<"error: Failed to load texture"<<std::endl;
    }
    sf::Sprite floor{floorTexture};
    sf::Sprite rock{rockTexture};
}


void GameDisplay::drawEntity(EntityContainer & con, sf::RenderWindow & win){

    sf::Text drawHp;
    sf::Text pos;

    sf::Sprite tempSprite;
    drawHp.setFont(getFont);
    pos.setFont(getFont);

    for(int it = 0; it < con.getSize(); ++it){
        if(con.getEntity(it).getCurrentRoom() == player.getCurrentRoom()){
            tempSprite = con.getEntSprite(it);
            tempSprite.move(boardOffset);
            vObject.push_back({con.getEntity(it).getPosition(), tempSprite});


            drawHp.setString(std::to_string(con.getEntity(it).getHp()));
            drawHp.setPosition(con.getEntSprite(it).getPosition() + boardOffset);
            win.draw(drawHp);

            pos.setOrigin(0, -16);
            pos.setString(std::to_string(con.getEntity(it).isAlive()));
            pos.setPosition(con.getEntSprite(it).getPosition() + boardOffset);
            win.draw(pos);


        }
    }
}

void GameDisplay::drawFloor(sf::RenderWindow & win){
    sf::RectangleShape floor({roomSizeX * (float)textureSize, roomSizeY * (float)textureSize});
    sf::Sprite floorSprite{floorTexture};
    sf::Sprite hatchSprite{hatchTexture};

    hatchSprite.setScale(4, 4);
    floorSprite.setScale(4,4);
    floor.setPosition(boardOffset);
    floor.setFillColor(sf::Color{120, 100, 80});

//    win.draw(floor);
    for(int row = 0; row < roomSizeY - 2; row ++){
        for(int col = 0; col < roomSizeX - 2; col ++) {
            setPosition({(float) col + 1, (float) row + 1}, floorSprite);
            win.draw(floorSprite);
        }
    }
    if(map.getRoomObject(player.getCurrentRoom(), {8, 4}) == hatch){
        hatchSprite.setTextureRect({32, 0, 32, 32});
        if(map.getEnemyCount(player.getCurrentRoom().x, player.getCurrentRoom().y) > 0)
            hatchSprite.setTextureRect({0, 0, 32, 32});

        setPosition({8,4}, hatchSprite);
        win.draw(hatchSprite);
    }

}



void GameDisplay::drawDoors(){
    sf::Vector2i roomPos = player.getCurrentRoom();
    doorSprite.setTextureRect({0, 0, 32, 32});
    doorSprite.setScale(4, 4);
    int topRect = 0;

    if(map.getEnemyCount(player.getCurrentRoom().x, player.getCurrentRoom().y) > 0){
        topRect = 32;
    }
    for(int posX = 0; posX < roomSizeX - 1; ++posX){
        if( map.getRoomObject(roomPos, {posX, 0}) == door and
                map.getRoomObject(roomPos, {posX + 1, 0}) == door)
        {
            doorSprite.setOrigin(0, 16);
            doorSprite.setPosition(posX * textureSize, 0);
            doorSprite.setTextureRect({0, topRect, 32, 32});
            vObject.push_back({{(float) posX, 0.f}, doorSprite});
        }

        if( map.getRoomObject(roomPos, {posX, roomSizeY - 1}) == door and
            map.getRoomObject(roomPos, {posX + 1, roomSizeY - 1}) == door)
        {
            doorSprite.setOrigin(0, 32);
            doorSprite.setPosition(posX * textureSize, (roomSizeY - 1) * textureSize);
            doorSprite.setTextureRect({1 * 32, topRect, 32, 32});
            vObject.push_back({{(float) posX, (float) roomSizeY - 1}, doorSprite});
        }
    }
    for(int posY = 0; posY < roomSizeY - 1; ++posY){
        if( map.getRoomObject(roomPos, {0, posY}) == door and
            map.getRoomObject(roomPos, {0, posY + 1}) == door)
        {
            doorSprite.setOrigin(0, 16);
            doorSprite.setPosition(0, (float) (posY + 1) * textureSize);
            doorSprite.setTextureRect({2 * 32, topRect, 32, 32});
            vObject.push_back({{0, (float) posY + 1}, doorSprite});
        }

        if( map.getRoomObject(roomPos, {roomSizeX-1, posY}) == door and
            map.getRoomObject(roomPos, {roomSizeX-1, posY + 1}) == door)
        {
            doorSprite.setOrigin(0, 16);
            doorSprite.setPosition((roomSizeX-2) * roomSizeX, (float) (posY + 1) * textureSize);
            doorSprite.setTextureRect({3 * 32, topRect, 32, 32});
            vObject.push_back({{roomSizeX - 2, (float) posY + 1}, doorSprite});
        }
    }
}


void GameDisplay::setPosition(sf::Vector2f pos, sf::Sprite & s) {
    s.setPosition(pos.x * textureSize + boardOffset.x, pos.y * textureSize + boardOffset.y);
}




void GameDisplay::debugDisplay(sf::RenderWindow & win) {
    sf::Text text;

    text.setFont(getFont);
    text.setCharacterSize(32);

    win.draw(text);
    text.setPosition(100, 0);
    text.setString(std::to_string(player.getPosition().x));
    win.draw(text);
    text.setPosition(100, 30);
    text.setString(std::to_string(player.getPosition().y));
    win.draw(text);

    text.setPosition(100, 80);
    text.setString(std::to_string(player.getCurrentRoom().x));
    win.draw(text);
    text.setPosition(120, 80);
    text.setString(std::to_string(player.getCurrentRoom().y));
    win.draw(text);

    text.setPosition(100, 100);
    text.setString(std::to_string(map.getEnemyCount(player.getCurrentRoom().x, player.getCurrentRoom().y)));
    win.draw(text);

}

void GameDisplay::drawMenu(sf::RenderWindow &win, Menu & menu) {
    sf::Text start;
    sf::Text exit;
    start.setFont(getFont);
    exit.setFont(getFont);
    start.setPosition(win.getSize().x / 2 - 100, 100);
    exit.setPosition(win.getSize().x / 2 - 100, 200);

    start.setCharacterSize(100);
    exit.setCharacterSize(100);

    start.setString("Start");
    exit.setString("Exit");


    if(menu.getSelectedOption() == 1){
        start.setFillColor(sf::Color::Red);
    }
    else if(menu.getSelectedOption() == 0){
        exit.setFillColor(sf::Color::Red);
    }
    win.draw(start);
    win.draw(exit);
}

void GameDisplay::drawEndScreen(sf::RenderWindow & win, Menu & menu) {
    sf::Text start;
    sf::Text exit;
    start.setFont(getFont);
    exit.setFont(getFont);
    start.setPosition(win.getSize().x / 2, 100);
    exit.setPosition(win.getSize().x / 2, 200);

    start.setCharacterSize(100);
    exit.setCharacterSize(100);

    start.setString("RETRY");
    exit.setString("Exit");


    if(menu.getSelectedOption() == 1){
        start.setFillColor(sf::Color::Red);
    }
    else if(menu.getSelectedOption() == 0){
        exit.setFillColor(sf::Color::Red);
    }
    win.draw(start);
    win.draw(exit);
}

