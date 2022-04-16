/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Poker.h
 * Author: Mai Huynh
 *
 * Created on April 14, 2022, 7:37 PM
 */
#define oneplayer
#ifndef POKER_H
#define POKER_H
#include "PokerHand.h"
#include "Deck.h"


class Poker {
#ifdef oneplayer
    PokerHand player;
    PokerHand dealer;
#else
    list<PokerHand> player;
#endif
    Deck deck;
    short status ;
    
public:
    void initializeGame(); // initialize a game
    void getInput(); // ask user for some commands (ex: "Do you want to continue(y/n)?"
    void update(); 
    void render();
    short getStatus() const{return status;}; // get status of game
    void setStatus(short ss){status = ss;}; // set status of game
    void dealCard();// deal five cards per 1 player
private:

};

#endif /* POKER_H */

