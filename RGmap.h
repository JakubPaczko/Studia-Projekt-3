#ifndef ROGALIK_RGMAP_H
#define ROGALIK_RGMAP_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/graphics.hpp>


enum roomType {typeA, typeB, typeC, typeD, typeE, blank};
enum roomObjects {none, wall, rock, torch, pillar, statue, barrel, candle, urn, door, hatch};

const int roomSizeX = 18;
const int roomSizeY = 10;



struct grid{

    roomType type;
    roomObjects Object[roomSizeX][roomSizeY];
    bool isVisited;
    int enemyCount;
};

class RGmap{

    grid Room[8][8];

    int roomsToGenerate = 6;

    std::vector<sf::Vector2i>  roomList;

    void clearMap();

    void generateRoom(int row, int col);

    //check if room is inside the grid
    static bool isInMap(int row, int col) ;

    void generateDoor(int posX, int posY);

    void generateHatch();

    void roomObjectGeneration(int posX, int posY, roomType type);

public:
    RGmap();
    ~RGmap();

    roomObjects getRoomObject(sf::Vector2i room, sf::Vector2i object) const;
    roomType getRoomType(sf::Vector2i pos);
    sf::Vector2i getRoomSize() const;

    void debugRoomDisplay(int gridRow, int gridCol) const;

    void generateMap(int roomCount);

    void debugDisplay() const;

    void setVisited(int posX, int posY);

    bool isObjWalkable(roomObjects obj);
    bool isVisited(int posX, int posY);
    int getEnemyCount(int posX, int posY);
    void setEnemyCount(int posX, int posY, int n);


    //difficulity getDifficulity();
};

#endif //ROGALIK_RGMAP_H
