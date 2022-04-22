#include <cstdlib>
#include "poker.h"
using namespace std;

int main(int argc, char** argv) {
    Poker game;
    game.initializeGame();
    do{
        game.getInput();
        game.update();
        game.render();
    }while(game.getStatus() != static_cast<short>(GAME_STATUS::END));
    return 0;
}

