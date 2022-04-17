
#ifndef POKERHAND_H
#define POKERHAND_H
#include <utility>
#include <string>
#include "Helper.h"
#include <map>
#include <set>
using namespace std;
class PokerHand {
private:
    set<card> cards; // set save cards of a poker hand in ASC order by rank (rank = pair.first)
    set<card,comp> rankedCards; // stack save cards ranked by suit (suit = pair.second)
    set<card> discard_cards; // set save cards which is discarded of a poker hand after draw round
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
              , false if size of cards > SIZE_HAND\
    */
    short changeCards(short removeCard,short key, card newCard);
    short getSize()const;
    set<card> getCards()const;
    set<card,comp> getRankedCards()const;
    bool isStraightFlush();
    bool isRoyalFlush();
    bool isFourOfKind();
    bool isFullHouse();
    /* @name: isFlush(): check if cards has the same suit
     * @return: true if has a flush
     *          false otherwise
     */
    bool isFlush();
    
    /* @name: isStraight(): check if cards are increasing continuously in rank
     * @return: true if has a straight 
     *          false otherwise
     */
    bool isStraight();
    bool isThreeOfKind();
    bool isTwoPair();
    bool isPair();
    /*
     * @name:sortBySuit(): sort cards by suit on ASC order. If same suit, sort rank on ASC order
     */
    bool sortBySuit();
};

#endif /* POKERHAND_H */

