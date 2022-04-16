#ifndef DECK_H
#define DECK_H
#include "Helper.h"
#include <deque>
#include <iostream>
using namespace std;
class Deck {
private:
    
    short status;
    short size;
public:
    deque<card> cards;
    Deck();
    // display cards on deck
};

#endif /* DECK_H */

