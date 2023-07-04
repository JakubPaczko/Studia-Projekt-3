#include <iostream>
#include <ctime>
#include "Game.h"

//wsad - ruch          k,j - strzał, atak
int main() {
    srand(time(nullptr));
    Game gameplay;
    gameplay.play();

    return 0;
}
