
#ifndef POKERHAND_H
#define POKERHAND_H
#include <utility>
#include <string>
#include "Helper.h"
#include <set>
using namespace std;
class PokerHand {
private:
    set<card> cards; // map save cards of a poker hand
    set<card> discard_cards; // map save cards which is discarded of a poker hand after draw round
    short score;
    string reply;
    
public:
    PokerHand();
    virtual ~PokerHand();
    void setReply(string rep){ reply = rep;};
    string getReply()const { return reply;};
    /* @name: addCards: insert a card at the end of cards. 
     * @parameter: short key, pairs newCard (rank,suit)
       @return: true if inserting is successful
              , false if size of cards > SIZE_HAND
    */
    bool addCards(short,card); 
    bool removeCards(short);
    /* @name: changeCards: change a card at the position iterator 
     * @parameter: short key, pairs newCard (rank,suit)
       @return: true if inserting is successful
              , false if size of cards > SIZE_HAND
    */
    short changeCards(short removeCard,short key, card newCard);
    short getSize()const;
    set<card> getCards()const;
    
private:

};

#endif /* POKERHAND_H */

