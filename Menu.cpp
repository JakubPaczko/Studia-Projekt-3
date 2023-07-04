//
// Created by kubap on 19.06.2022.
//

#include "Menu.h"

Menu::Menu(GameManager &m) : mgr(m){

}

void Menu::changeMenuState() {
    if(mgr.getGameState() != RUNNING){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            ++selectedOption;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            --selectedOption;

        if (selectedOption > 1)
            selectedOption = 1;
        if (selectedOption <0)
            selectedOption = 0;


    }
    if(mgr.getGameState() == MENU){
        if(selectedOption == 1 and sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            mgr.changeGameState(RUNNING);
            mgr.resetGame();
        }
        if(selectedOption == 0 and sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            exit(0);
    }
    if(mgr.getGameState() == FINISHED){
        if(selectedOption == 1 and sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            mgr.changeGameState(MENU);
//            mgr.resetGame();
        }
        if(selectedOption == 0 and sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            exit(0);
    }
}

int Menu::getSelectedOption() {
    return selectedOption;
}
