
#define demo
#define test

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
bool PokerHand::setDiscardedPoss(short pos){
    discardedPoss.push(pos);
    return true;
}
bool PokerHand::changeCards(queue<card>& ds){
    
    set<card>::iterator it = cards.begin();
    
    short count=0; // number of cards is removed in cards set
    // removed some cards from cards set and save to discardedCards
    while(!discardedPoss.empty()){
        
        short pos = discardedPoss.front()-1 - count; 
        it = next(cards.begin(),pos); 
        discardedPoss.pop();
        
        // get card at pos in cards
        card c = (*it);
        
        // save discarded card into discardedCards
        discardedCards.insert(c);
        
        // remove card at pos in cards
        cards.erase(it);
        count ++;
    }
    
    // add ds to set of cards
    while(!ds.empty()){
        cards.insert(ds.front());     
        ds.pop();
    }
    return true;
}
short PokerHand::getSize()const{
    return cards.size();
}
set<card,comp> PokerHand::getRankedCards()const{
    return rankedCards;
}
bool PokerHand::isStraightFlush(){

    if(isStraight() && isFlush()){
        handRank = static_cast<short>(HAND_RANKS::STRAIGHTFLUSH);
        startRank = 0;
        sizeHighCard = 0;
        return true;
    }
    return false;
}
bool PokerHand::isRoyalFlush(){

    auto it = prev(cards.end());
    if(isStraight() && isFlush() && it->first==(short)RANK::KING) {
        handRank = static_cast<short>(HAND_RANKS::ROYALFLUSH);
        startRank = 0;
        sizeHighCard = 0;
        return true;
    }
    return false;
}
bool PokerHand::isFourOfKind(){
    
    auto itBegin = cards.begin();
    auto itLast = prev(cards.end(),1); 
    
    short firstCard = itBegin->first;
    int countStart = count_if(cards.begin(),itLast,[firstCard](const card& c){ return c.first== firstCard;}); 
    
    itBegin = next(itBegin);
    firstCard = itBegin->first;
    int countEnd = count_if(itBegin,cards.end(),[firstCard](const card& c){ return c.first== firstCard;}); 
    
    if(countStart == FOUROFKIND // type: xxxx y
            || countEnd == FOUROFKIND // type: x yyyy
        ) {
        handRank = static_cast<short>(HAND_RANKS::FOUROFKIND);
        countStart == FOUROFKIND? startRank = 0: startRank =1;
        sizeHighCard = 1;
        return true;
    }
    return false;
}
bool PokerHand::isFullHouse(){
   
    auto itBegin = cards.begin();
    auto it1 = next(itBegin,1)
        , it2=next(itBegin,2)
        , it3=next(itBegin,3)
        , it4=next(itBegin,4);
    
    //check for type: xxx yy
    if (itBegin->first == it1->first && it1->first == it2->first && it3->first == it4->first){
        startRank = 0;
    }
    
    //check for type: xx yyy
    else if (itBegin->first == it1->first  && it2->first == it3->first && it3->first == it4->first){
        startRank = 2;
    }
    else 
        return false;
    
    handRank = static_cast<short>(HAND_RANKS::FULLHOUSE);
    sizeHighCard = 0;
    return true;
}
bool PokerHand::isFlush(){
        
    auto position1= rankedCards.begin();
    auto position5= prev(rankedCards.end());
    if(position1->second == position5->second) // check suit of first card is equal to suit of last card
    {
        handRank = static_cast<short>(HAND_RANKS::FLUSH);
        startRank = 0;
        sizeHighCard = 0;
        return true;
    }
    return false;
}
bool PokerHand::isStraight(){
    
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
                handRank = static_cast<short>(HAND_RANKS::STRAIGHT);
                startRank = 0;
                sizeHighCard = 0;
                return true;
        }
        if(iteratorACE == itBegin && it1->first == (short)RANK::TEN){ //(10 JACK QUEEN KING ACE)
            if(it2->first  == (short)RANK::JACK 
                    && it3->first  == (short)RANK::QUEEN 
                    && it4->first  == (short)RANK::KING) 
                handRank = static_cast<short>(HAND_RANKS::STRAIGHT);
                startRank = 0;
                sizeHighCard = 0;
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
        pos = nextPos;
        nextPos = next(pos);
    }
    
    handRank = static_cast<short>(HAND_RANKS::STRAIGHT);
    startRank = 0;
    sizeHighCard = 0;
    
    return true;
}
bool PokerHand::isThreeOfKind(){
    
    if(isFourOfKind() || isFullHouse()) 
        return false; 
    
    auto itBegin = cards.begin();
    auto it1 = next(itBegin,1)
        , it2=next(itBegin,2)
        , it3=next(itBegin,3)
        , it4=next(itBegin,4);
    
    if(itBegin->first == it1->first && it1->first==it2->first ){ // check for xxx y z
        startRank = 0;
    }
    else if(it1->first == it2->first && it2->first==it3->first ){ // check for x yyy z
        startRank = 1;
    }
    else if(it2->first == it3->first && it3->first==it4->first ){ // check for x y zzz
        startRank = 2;
    }
    else 
        return false;
    
    handRank = static_cast<short>(HAND_RANKS::THREEOFKIND);
    sizeHighCard = SIZE_HAND-THREEOFKIND;
    
    return true;
}
bool PokerHand::isTwoPair(){
    
    if(isFourOfKind() || isFullHouse() || isThreeOfKind()) 
        return false;
    
    auto itBegin = cards.begin();
    auto it1 = next(itBegin,1)
        , it2=next(itBegin,2)
        , it3=next(itBegin,3)
        , it4=next(itBegin,4);
    
    if(itBegin->first == it1->first && it2->first==it3->first ){ // check for xx yy z
        startRank = 0;
    }
    else if(it1->first == it2->first && it3->first==it4->first ){ // check for x yy zz
        startRank = 1;
    }
    else if(itBegin->first == it1->first && it3->first==it4->first ){ // check for xx y zz
        startRank = 3;
    }
    else 
        return false;
    
    handRank = static_cast<short>(HAND_RANKS::TWOPAIR);
    sizeHighCard = SIZE_HAND-TWOPAIR;
    
    return true;
}
bool PokerHand::isPair(){
        
    if(isFourOfKind() || isFullHouse() || isThreeOfKind() || isTwoPair()) // if fourofkind or fullhouse or threeofkind or twopair
        return false;
    
    auto itBegin = cards.begin();
    auto it1 = next(itBegin,1)
        , it2=next(itBegin,2)
        , it3=next(itBegin,3)
        , it4=next(itBegin,4);
    if(itBegin->first == it1->first  // xx y z t
            || it1->first == it2->first  // x yy z t
            || it2->first == it3->first  // x y zz t
            || it3->first == it4->first  // x y z tt
            ){ 
        
        if(itBegin->first == it1->first)  
           startRank = 0;
        else if(it1->first == it2->first)  
           startRank = 1;
        else if(it2->first == it3->first)  
           startRank = 2;
        else if(it3->first == it4->first)  
           startRank = 3;
        
        handRank = static_cast<short>(HAND_RANKS::ONEPAIR);
        sizeHighCard = SIZE_HAND-ONEPAIR;
        
        return true;
    }
    return false;
}
bool PokerHand::sortBySuit(){
    rankedCards.clear();
    set<card,comp> tmp(cards.begin(),cards.end());
    rankedCards = tmp;
    tmp.clear();
    return true;
}
bool PokerHand::rank(){
    
    sortBySuit();
    
    if(cards.size()!=SIZE_HAND) return false; // check hand has enough 5 cards.
    if(rankedCards.size()!=SIZE_HAND) return false; // check rankedCards has enough 5 cards.
    
    if(isRoyalFlush()) { 
        return true; 
    }
    
    if(isStraightFlush()) { 
        return true; 
    }
    
    if(isFourOfKind()) { 
        return true; 
    }
    
    if(isFullHouse()) { 
        return true; 
    }
    
    if(isFlush()){ 
        return true; 
    }
    
    if(isStraight()) { 
        return true; 
    }
    
    if(isThreeOfKind()) { 
        return true; 
    }
    
    if(isTwoPair()) { 
        return true; 
    }
    
    if(isPair()) { 
        return true; 
    }
    
    // lowest hand rank
    startRank = 0;
    sizeHighCard = SIZE_HAND;
    handRank = static_cast<short>(HAND_RANKS::HIGHCARD);
    return true;
}
void PokerHand::reset(){
    cards.clear();
    rankedCards.clear();
    discardedCards.clear();
    while(!discardedPoss.empty()) discardedPoss.pop();
    score = 0;
    reply = -1;
    handRank = 0;
    startRank = -1;
    sizeHighCard = 0;
}

