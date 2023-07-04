#ifndef ROGALIK_MENU_H
#define ROGALIK_MENU_H

#include "GameManager.h"
#include <SFML/Graphics.hpp>

class Menu {
    GameManager & mgr;
    int selectedOption;
public:
    explicit Menu (GameManager & m);
    void changeMenuState();
    int getSelectedOption();
};


#endif //ROGALIK_MENU_H
