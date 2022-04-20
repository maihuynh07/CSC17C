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
    short status ; // status of game
    short state; // state of a game
    short question; // question to players
    map<short,string> messages; // messages to display to players through a game
    map<short,string> questions; // questions to players through a game
    map<string, short> replies; // answer of players
public:
    void initializeGame(); // initialize a game
    void getInput(); // ask user for some commands (ex: "Do you want to continue(y/n)?"
    void update(); 
    void render();
    short getStatus() const{return status;}; // get status of game
    void setStatus(short ss){status = ss;}; // set status of game
    short getState() const{return state;}; // get state of game
    void setState(short st){state = st;}; // set state of game
    void dealCard(); // deal five cards per 1 player
    void drawCard(); // exchange some cards on players and deck
    void rankHand(); // rank players to score
    /*  ************************************************************************
     *  @name: score: manipulate score of players in a game.
     *  Hands are ranked as follows (from high to low):
        •	Straight Flush
        •	Four of a Kind
        •	Full House
        •	Flush
        •	Straight
        •	Three of a Kind
        •	Two Pair
        •	Pair
        •	High Card
     * *************************************************************************/
     
    void score(); 
   
private:

};

#endif /* POKER_H */

