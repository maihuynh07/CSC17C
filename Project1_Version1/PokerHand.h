
#ifndef POKERHAND_H
#define POKERHAND_H
#include <utility>
#include <string>
#include "Helper.h"
#include <map>
#include <set>
#include <queue>
#include <list>
using namespace std;
class PokerHand {
private:
    set<card> cards; // set save cards of a poker hand in ASC order by rank (rank = pair.first)
    set<card,comp> rankedCards; // stack save cards ranked by suit (suit = pair.second)
    set<card> discardedCards; // set save cards which is discarded of a poker hand after draw round
    queue<short> discardedPoss; // positions(in cards set) whose card is discarded , values in = {1,2,3,4,5}
    short score;
    short reply;
    
public:
    PokerHand();
    virtual ~PokerHand();
    void setReply(short rep){ reply = rep;};
    short getReply()const { return reply;};
    
    /* *************************************************************************
     * @name: addCards: insert a card at the end of cards. 
     * @parameter: short key, pairs newCard (rank,suit)
       @return: true if inserting is successful
              , false if size of cards > SIZE_HAND
     * **************************************************************************/
    bool addCards(short,card); 
    
    /* @name: changeCards: add cards from deck into discardedCards and remove cards from cards at positions in discardedPoss.
     * @parameter: newCards (rank,suit)
       @return: true if successful
              , otherwise false
    */
    bool changeCards(queue<card>&);
    
    
    bool setDiscardedPoss(short pos);
    short getSize()const;
    set<card> getCards()const;
    set<card,comp> getRankedCards()const;
    
    /* *************************************************************************
     * @name: isStraightFlush(): check if cards are increasing continuously in rank and the same suit
     *          , type: ACE 2 3 4 5,..., 6 7 8 9 10 ,..., 10 JACK QUEEN KING ACE
     * @return: true if has a straight flush
     *          false otherwise
     * **************************************************************************/
    bool isStraightFlush();
    
    /* *************************************************************************
     * @name: isRoyalFlush(): check if cards are increasing continuously in rank and the same suit and highestRank = ACE
     *         , type: 10 JACK QUEEN KING ACE
     * @return: true if has a straight flush
     *          false otherwise
     * **************************************************************************/
    bool isRoyalFlush();
    
    /* *************************************************************************
     * @name: isFourOfKind(): check if cards are 4 cards which same rank, type xxxx y or x yyyy 
     * @return: true if has a four of kind
     *          false otherwise
     * **************************************************************************/
    bool isFourOfKind();
    
    /* *************************************************************************
     * @name: isFullHouse(): check if cards are 3 cards which same rank, and one pair
     *          , type xxx yy or xx yyy 
     * @return: true if has a full house
     *          false otherwise
     * **************************************************************************/
    bool isFullHouse();
    
    /* *************************************************************************
     * @name: isFlush(): check if cards has the same suit
     *          ,type: 5 SPADES, 5 DIAMONDS,....
     * @return: true if has a flush
     *          false otherwise
     * **************************************************************************/
    bool isFlush();
    
    /* *************************************************************************
     * @name: isStraight(): check if cards are increasing continuously in rank
     * @return: true if has a straight 
     *          false otherwise
     * **************************************************************************/
    bool isStraight();
    
    /* *************************************************************************
     * @name: isThreeOfKind(): check if cards has 3 of a rank and 2 unmatched cards
     *          , type: xxx y z, x yyy z, x y zzz
     * @return: true if has a three of kind
     *          false otherwise
     * **************************************************************************/
    bool isThreeOfKind();
    
    /* *************************************************************************
     * @name: isTwoPair(): check if cards has 2 of a rank and 2 of a rank and 1 unmatched
     *          , type: xx yy z, x yy zz, xx y zz
     * @return: true if has a two of pair
     *          false otherwise
     * **************************************************************************/
    bool isTwoPair();
    
    /* *************************************************************************
     * @name: isPair(): check if cards has 1 of a rank and 3 unmatched
     *          , type: xx y z t, x yy z t, x y zz t, z y z tt
     * @return: true if has a one of pair
     *          false otherwise
     * **************************************************************************/
    bool isPair();
    /* *************************************************************************
     * @name:sortBySuit(): sort cards by suit on ASC order. If same suit, sort rank on ASC order
     * **************************************************************************/
    bool sortBySuit();
    
    // set cards for demo
    void setCardsDemo();
};

#endif /* POKERHAND_H */

