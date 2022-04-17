
#define demo
#define test
//#define demoStraight
#include "PokerHand.h"
#include <iterator>

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
set<card,comp> PokerHand::getRankedCards()const{
    return rankedCards;
}
bool PokerHand::isStraightFlush(){
    return true;
}
bool PokerHand::isRoyalFlush(){
    return true;
}
bool PokerHand::isFourOfKind(){
    return true;
}
bool PokerHand::isFullHouse(){
    return true;
}

bool PokerHand::isFlush(){
    if(cards.size()!=SIZE_HAND) return false; // check hand has enough 5 cards.
    if(rankedCards.size()!=SIZE_HAND) return false; // check rankedCards has enough 5 cards.
    auto position1= rankedCards.begin();
    auto position5= prev(rankedCards.end());
#ifdef test
    showCards(getRankedCards(),"\nRanked Cards inside flush: \n");
    string message1 = sSuit(position1->second);
    displayMessage("suit1:"+message1);
    string message5 = sSuit(position5->second);
    displayMessage("suit5:"+message5);
    //displayMessage(string(((card)(*position0)).second));
#endif
    if(position1->second == position5->second) // check suit of first card is equal to suit of last card
        return true;
    return false;
}
bool PokerHand::isStraight(){
#ifdef demoStraight
    set<card> tmp;
    card c ; c.first = (short)RANK::ACE; c.second = (short)SUIT::SPADES;
    tmp.insert(c);
    c.first = (short)RANK::TWO; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
    c.first = (short)RANK::THREE; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
     c.first = (short)RANK::FOUR; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
     c.first = (short)RANK::FIVE; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
    tmp.swap(cards);     
    tmp.clear();
#endif
    /* 
     * check for special case: has an ACE
     * if has an ACE, check if has (ACE 2 3 4 5) or (10 JACK QUEEN KING ACE)
     * */
    auto iteratorACE = find_if(cards.begin(),cards.end(),[] (const card& element){ return (element.first)==(short)RANK::ACE;});
    auto itEnd = cards.end();
    auto itBegin = cards.begin();
    auto it1 = next(itBegin,1)
        , it2=next(itBegin,2)
        , it3=next(itBegin,3)
        , it4=next(itBegin,4);
    if(iteratorACE != itEnd) { // if found
        if(iteratorACE == itBegin && it1->first == (short)RANK::TWO){ //(ACE 2 3 4 5)
            if(it2->first == (short)RANK::THREE 
                    && it3->first == (short)RANK::FOUR 
                    && it4->first == (short)RANK::FIVE) 
                return true;
        }
        if(iteratorACE == itBegin && it1->first == (short)RANK::TEN){ //(10 JACK QUEEN KING ACE)
            if(it2->first  == (short)RANK::JACK 
                    && it3->first  == (short)RANK::QUEEN 
                    && it4->first  == (short)RANK::KING) 
                return true;
        }
        return false;
    }
    /* 
     * check for normal case: no ACE, increasing continuously in rank
     */
    auto pos = itBegin;
    auto nextPos = next(pos);
    while(pos!= itEnd && nextPos != itEnd){
        if((pos->first) + 1 != nextPos->first) // check if rank of cards is increasing continuously in rank
            return false;
        ++pos;
    }
    return true;
}
bool PokerHand::isThreeOfKind(){
    return true;
}
bool PokerHand::isTwoPair(){
    return true;
}
bool PokerHand::isPair(){
    return true;
}
bool PokerHand::sortBySuit(){
    set<card,comp> tmp(cards.begin(),cards.end());
    rankedCards = tmp;
    tmp.clear();
    return true;
}

