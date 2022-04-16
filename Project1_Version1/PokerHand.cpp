/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PokerHand.cpp
 * Author: Mai Huynh
 * 
 * Created on April 14, 2022, 7:36 PM
 */

#include "PokerHand.h"

PokerHand::PokerHand() {
    score = 0;
}
PokerHand::~PokerHand() {
}
bool PokerHand::addCards(short key,card c){
    if(getSize()>=SIZE_HAND) return false;
    cards.insert(c);
    return true;
}
bool PokerHand::removeCards(short){
    return false;
}
short PokerHand::changeCards(short removeCard,short key, card newCard){
    return 0;
}
short PokerHand::getSize()const{
    return cards.size();
}
set<card> PokerHand::getCards()const{
    return cards;
}
