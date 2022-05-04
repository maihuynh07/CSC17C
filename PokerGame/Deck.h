#ifndef DECK_H
#define DECK_H
#include "Helper.h"
#include <deque>
#include <stack>
#include <iostream>
#include <set>
using namespace std;

class Deck : public Helper{
public:
    short status;
    short size;
    deque<card> cards;
    stack<card> disCardedCards; 
public:
    Deck();
    void drawCard(); // draw card from deck, save to discardedCards
    void resetDeck(set<card>&); // reset deck (deck is full size)
    void showDeck(); // display deck card
};

#endif /* DECK_H */

