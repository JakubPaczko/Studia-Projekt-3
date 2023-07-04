//
// Created by kubap on 10.06.2022.
//

#include "GameManager.h"

GameManager::GameManager(RGmap &m, EntityContainer &c, Player &p)
    : map(m), con(c), player(p){
    gameLevel = 1;
    GameState = MENU;
}

void GameManager::SpawnEnemies() {
    sf::Vector2i roomPos = player.getCurrentRoom();
    map.isVisited(roomPos.x, roomPos.y);
    int enemyCount = 0;
    if(!map.isVisited(roomPos.x, roomPos.y)){
        int enemyAmount = rand() % (3 + gameLevel * rand() % 2) + 1;

        while(enemyCount < enemyAmount){
            int randPosX = rand() % roomSizeX;
            int randPosY = rand() % roomSizeY;

            if(map.isObjWalkable(map.getRoomObject(player.getCurrentRoom(), {randPosX, randPosY}))
            and map.isObjWalkable(map.getRoomObject(player.getCurrentRoom(), {randPosX + 1, randPosY}))
            and map.isObjWalkable(map.getRoomObject(player.getCurrentRoom(), {randPosX, randPosY + 1}))
            and map.isObjWalkable(map.getRoomObject(player.getCurrentRoom(), {randPosX + 1, randPosY + 1}))){
                ent = new Enemy({(float )randPosX + 0.5f, (float )randPosY + 0.5f}, player.getCurrentRoom(), gameLevel);
                con.addEntity(ent);
                enemyCount ++;
            }

        }

        map.setVisited(roomPos.x, roomPos.y);
    }
    for(int it = 0; it < con.getSize(); ++it){
        if(con.getEntity(it).getCurrentRoom() == roomPos and con.getEntity(it).getEntType() == ENEMY){
            ++enemyCount;
        }
    }
    map.setEnemyCount(roomPos.x, roomPos.y, enemyCount);
}

gameState GameManager::getGameState() {
    return GameState;
}

void GameManager::changeGameState(gameState state) {
    GameState = state;
}

void GameManager::setGameLevel(int lvl) {
    gameLevel = lvl;
}

int GameManager::getGameLevel() {
    return gameLevel;
}

void GameManager::resetGame() {
    gameLevel = 1;
    map.generateMap(6 + gameLevel);
    player.setPosition({3, 3});
    player.setHp(100);
    player.setCurrentRoom({3, 3});
    player.setAlive(true);
    con.clear();
}

void GameManager::nextLevel() {
    ++gameLevel;
    map.generateMap(6 + gameLevel);
    player.setHp(100);
    player.setAlive(true);
    player.setCurrentRoom({3, 3});
}
