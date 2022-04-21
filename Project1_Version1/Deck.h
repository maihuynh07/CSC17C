#ifndef DECK_H
#define DECK_H
#include "Helper.h"
#include <deque>
#include <queue>
#include <iostream>
#include <set>
using namespace std;
class Deck {
public:
    short status;
    short size;
    deque<card> cards;
    queue<card> disCardedCards; 
public:
    Deck();
    card drawCard();
    void resetDeck(set<card>&);
};

#endif /* DECK_H */

