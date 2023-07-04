#ifndef ROGALIK_GAMEMANAGER_H
#define ROGALIK_GAMEMANAGER_H

#include "Entity//EntityContainer.h"
#include "Entity//Entity.h"
#include "Entity//Player.h"
#include "RGmap.h"

enum gameState {MENU, RUNNING, FINISHED};

class GameManager {
    int gameLevel;

    gameState GameState;
    Player & player;
    RGmap & map;
    EntityContainer & con;

    Entity * ent;

public:
    GameManager(RGmap & m, EntityContainer & c, Player & p);
    void SpawnEnemies();
    gameState getGameState();
    void changeGameState(gameState state);

    void setGameLevel(int lvl);
    int getGameLevel();

    void nextLevel();
    void resetGame();

};


#endif //ROGALIK_GAMEMANAGER_H
