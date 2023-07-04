#include "RGmap.h"


RGmap::RGmap() {
}

RGmap::~RGmap() {
}

void RGmap::debugRoomDisplay(int gridRow, int gridCol) const {
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 20; ++col) {
            std::cout<< "["<<Room[gridCol][gridRow].Object[col][row]<<"]";
        }
        std::cout<<std::endl;
    }
}

bool RGmap::isInMap(int row, int col) {
    if(row > 0 and col > 0 and row < 8 and col < 8)
        return true;
    else
        return false;
}

void RGmap::clearMap(){
    roomList.clear();
    for(int posX = 0; posX < 8; ++posX){
        for(int posY = 0; posY < 8; ++ posY){
            Room[posX][posY].type = blank;
            Room[posX][posY].isVisited = false;
        }
    }
}

void RGmap::generateRoom(int posX, int posY) {
    roomType randRoomType;
    int randRoom = rand() % 4;
    randRoomType = static_cast<roomType>(rand() % blank);

    if(randRoom == 0 and Room[posX - 1][posY].type == blank and isInMap(posX - 1, posY)){
        roomObjectGeneration(posX - 1, posY, randRoomType);
        roomList.push_back({posX - 1 , posY});
        Room[posX - 1][posY].type = randRoomType;
        return;
    }
    else if(randRoom == 1 and Room[posX][posY - 1].type == blank and isInMap(posX, posY - 1)){
        roomObjectGeneration(posX, posY - 1, randRoomType);
        roomList.push_back({posX, posY - 1});
        Room[posX][posY - 1].type = randRoomType;
        return;
    }
    else if(randRoom == 2 and Room[posX + 1][posY].type == blank and isInMap(posX + 1, posY)) {
        roomObjectGeneration(posX + 1, posY, randRoomType);
        roomList.push_back({posX + 1, posY});
        Room[posX + 1][posY].type = randRoomType;
        return;
    }
    else if(randRoom == 3 and Room[posX][posY + 1].type == blank and isInMap(posX, posY + 1)) {
        roomObjectGeneration(posX, posY + 1, randRoomType);
        roomList.push_back({posX, posY + 1});
        Room[posX][posY + 1].type = randRoomType;
        return;
    }
}

void RGmap::generateMap(int roomCount) {
    roomsToGenerate = roomCount;
    clearMap();

    Room[3][3].type = typeA;
    Room[3][3].isVisited = true;
    roomObjectGeneration(3, 3 , Room[3][3].type);
    roomList.push_back(sf::Vector2i(3, 3));


    while (roomList.size() < roomsToGenerate){

        int randRoom = rand() % roomList.size();

        sf::Vector2i tempRoomPos = roomList[randRoom];
        generateRoom(tempRoomPos.x, tempRoomPos.y);

    }
    debugDisplay();

    generateHatch();

    for(int row = 0; row < 8; ++row){
        for(int col = 0; col < 8; ++col) {
            if(Room[row][col].type != blank)
                generateDoor(row, col);
        }
    }
}


void RGmap::debugDisplay() const {
    for (int row = 0; row < 8; ++row){
        for (int col = 0; col < 8; ++col) {
            if(Room[col][row].type == blank)
                std::cout<<"[   ]";
            else
                std::cout<<"[ "<<Room[col][row].type<<" ]";
        }
        std::cout<<std::endl;
    }
}

roomObjects RGmap::getRoomObject(sf::Vector2i room, sf::Vector2i object) const{
    roomObjects result;
    result = Room[room.x][room.y].Object[object.x][object.y];
    return result;
}

sf::Vector2i RGmap::getRoomSize() const{
    return sf::Vector2i(roomSizeX, roomSizeY);
};

void RGmap::roomObjectGeneration(int posX, int posY, roomType type) {
//    std::cout<< posX << " : " << posY << "\n";

    std::fstream mapFile;

//    Room[posX][posY].type = type;

    mapFile.open("../Text/roomLayout.txt", std::ios::in);
    int lineStart = 0;
    switch (type) {
        case typeA:
            lineStart = 1;
            break;
        case typeB:
            lineStart = roomSizeY + 1;
            break;
        case typeC:
            lineStart = roomSizeY * 2 + 1;
            break;
        case typeD:
            lineStart = roomSizeY * 3 + 1;
            break;
        case typeE:
            lineStart = roomSizeY * 4 + 1;
            break;
        case blank:
            return;
    }

    if(!mapFile.good()){
        std::cout << "Blad pliku roomLayout.txt" << std::endl;
        return;
    }

    std::string line;

    int lineNo = 1;
    while (mapFile >> line){
        if(lineNo > lineStart and lineNo <= lineStart + roomSizeY){
            for(int col = 0; col < roomSizeX; ++col){
                switch (line[col]) {
                    case 'w':
                        Room[posX][posY].Object[col][(lineNo - 1) % roomSizeY] = wall;
                        break;
                    case 'c':
                        Room[posX][posY].Object[col][(lineNo - 1) % roomSizeY] = candle;
                        break;
                    case 'r':
                        Room[posX][posY].Object[col][(lineNo - 1) % roomSizeY] = rock;
                        break;
                    case 's':
                        Room[posX][posY].Object[col][(lineNo - 1) % roomSizeY] = statue;
                        break;
                    case 't':
                        Room[posX][posY].Object[col][(lineNo - 1) % roomSizeY] = torch;
                        break;
                    case 'b':
                        Room[posX][posY].Object[col][(lineNo - 1) % roomSizeY] = barrel;
                        break;
                    case 'p':
                        Room[posX][posY].Object[col][(lineNo - 1) % roomSizeY] = pillar;
                        break;
                }
            }
        }

        lineNo ++;
    }

    mapFile.close();
}

void RGmap::generateDoor(int posX, int posY) {
    if(Room[posX][posY - 1].type != blank and isInMap(posX, posY - 1)){
        Room[posX][posY].Object[8][0] = door;
        Room[posX][posY].Object[9][0] = door;
    }
    if(Room[posX][posY + 1].type != blank and isInMap(posX, posY + 1)){
        Room[posX][posY].Object[8][9] = door;
        Room[posX][posY].Object[9][9] = door;
    }
    if(Room[posX - 1][posY].type != blank and isInMap(posX - 1, posY)){
        Room[posX][posY].Object[0][4] = door;
        Room[posX][posY].Object[0][5] = door;
    }
    if(Room[posX + 1][posY].type != blank and isInMap(posX + 1, posY)){
        Room[posX][posY].Object[17][4] = door;
        Room[posX][posY].Object[17][5] = door;
    }
}

roomType RGmap::getRoomType(sf::Vector2i pos) {
    return Room[pos.x][pos.y].type;
}

bool RGmap::isObjWalkable(roomObjects obj) {
    if(obj == none or  obj == door or obj == hatch)
        return true;
    return false;
}

bool RGmap::isVisited(int posX, int posY) {
    return Room[posX][posY].isVisited;
}


void RGmap::setVisited(int posX, int posY) {
    Room[posX][posY].isVisited = true;
}

int RGmap::getEnemyCount(int posX, int posY) {
    return Room[posX][posY].enemyCount;
}

void RGmap::setEnemyCount(int posX, int posY, int n) {
    Room[posX][posY].enemyCount = n;
}

void RGmap::generateHatch() {

    for(int it = 0; it < roomList.size(); ++it){
        sf::Vector2i pos = roomList[it];
        if(!Room[pos.x + 1][pos.y].isVisited and (pos.x != 3 and pos.y != 3)){
            int roomCount = 0;
            if (Room[pos.x + 1][pos.y].type != blank)
                roomCount += 1;

            if (Room[pos.x - 1][pos.y].type != blank)
                roomCount += 1;

            if (Room[pos.x][pos.y + 1].type != blank)
                roomCount += 1;

            if (Room[pos.x][pos.y - 1].type != blank)
                roomCount += 1;

            if (roomCount <= 2) {
                Room[pos.x][pos.y].Object[8][4] = hatch;
                Room[pos.x][pos.y].Object[8][5] = hatch;
                Room[pos.x][pos.y].Object[9][4] = hatch;
                Room[pos.x][pos.y].Object[9][5] = hatch;

                std::cout << "hatch generated at - x:" << pos.x << " y: " << pos.y << "\n";

                return;
            }
        }
    }
    generateHatch();

}


