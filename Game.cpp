#include "Game.h"
#include "Controller/PlayerController.h"
#include "Menu.h"
const sf::Vector2i winSize = sf::Vector2i{1280 , 720};

Game::Game(){
    win = new sf::RenderWindow(sf::VideoMode(winSize.x, winSize.y), "Rogalik");
    player = new Player({3, 3}, {3, 3});
    map = new RGmap();
    con = new EntityContainer(*map);
    Display = new GameDisplay(*map, *player);
    GameMgr = new GameManager(*map, *con, *player);
//    map->generateMap(6 + GameMgr->getGameLevel());
}

void Game::play() {
    win->setFramerateLimit(60);
    con->addEntity(player);
    PlayerController contr(*player, *con, *GameMgr);
    EnemyController eController(*con, *player);
    Menu menu(*GameMgr);

//        map->debugDisplay();
//        map->debugRoomDisplay(3, 3);

    while (win->isOpen()){

        while (win->pollEvent(event)){

            if (event.type == sf::Event::Closed){
                win->close();
            }

        }

        win->clear();

        if(GameMgr->getGameState() == RUNNING){
            GameMgr->SpawnEnemies();

            eController.update();
            contr.getInput();
            contr.update(*map);
            con->update();
            Display->drawEntity(*con, *win);
            Display->draw(*win);
        }
        if(GameMgr->getGameState() == MENU){
            menu.changeMenuState();
            Display->drawMenu(*win, menu);
        }
        if(GameMgr->getGameState() == FINISHED){
            menu.changeMenuState();
            Display->drawEntity(*con, *win);
            Display->draw(*win);
            Display->drawEndScreen(*win, menu);
        }


//        Display->debugDisplay(*win);
        win->display();
    }
}
