#ifndef DECK_H
#define DECK_H
#include "Helper.h"
#include <deque>
#include <stack>
#include <iostream>
#include <set>
using namespace std;
class Deck {
public:
    short status;
    short size;
    deque<card> cards;
    stack<card> disCardedCards; 
public:
    Deck();
    void drawCard();
    void resetDeck(set<card>&);
};

#endif /* DECK_H */

