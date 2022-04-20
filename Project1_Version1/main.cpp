//#define test1
//#define test2
#include <map>
#include <cstdlib>
#include "poker.h"
using namespace std;

int main(int argc, char** argv) {
    Poker game;
    game.initializeGame();
    do{
        game.getInput();
        game.update();
#ifdef test1
        if(game.getState()==2) game.setStatus(2);
#endif        
#if test2
        game.setStatus(2);
#endif
        game.render();

    }while(game.getStatus() != static_cast<short>(GAME_STATUS::END));
    return 0;
}

