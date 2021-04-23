#include "Game.h"
#include <ctime>

int main() {

    srand(time(nullptr));

    Game game;

    game.run();

    return 0;
}