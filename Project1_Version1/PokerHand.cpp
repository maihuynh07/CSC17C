
#define demo
#define test
#define demoRoyalFlush
//#define demoStraightFlush
//#define demoFourOfKind
//#define demoFullHouse
//#define demoFlush
//#define demoStraight
//#define demoThreeOfKind
//#define demoTwoPair
//#define demoOnePair


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
        
#ifdef test
        showCards(cards,"Cards before erase: ("+ sRank(it->first)+")");
#endif
        // remove card at pos in cards
        cards.erase(it);
        count ++;
#ifdef test
        showCards(cards,"Cards after erase: ("+ sRank(it->first)+")");
#endif
    }
    
    // add ds to set of cards
    while(!ds.empty()){
        cards.insert(ds.front());
#ifdef test
        displayMessage("ds: "+sRank(ds.front().first)+","+sSuit(ds.front().second));
#endif        
        ds.pop();
    }
#ifdef test
        showCards(cards,"Cards after erase: ");
#endif    
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
        
    if(cards.size()!=SIZE_HAND) return false; // check hand has enough 5 cards.
    if(rankedCards.size()!=SIZE_HAND) return false; // check rankedCards has enough 5 cards.
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
    
    if(isFourOfKind() || isFullHouse()) // if fourofkind or fullhouse
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
    
    if(isFourOfKind() || isFullHouse() || isThreeOfKind()) // if fourofkind or fullhouse or threeofkind
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
        else if(itBegin->first == it1->first)  
           startRank = 1;
        else if(itBegin->first == it1->first)  
           startRank = 2;
        else if(itBegin->first == it1->first)  
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
void PokerHand::rank(){
    
    sortBySuit();
    if(isRoyalFlush()) { 
#ifdef test
        displayMessage("Players has a isRoyalFlush");
#endif
        return; 
    }
    
    if(isStraightFlush()) { 
#ifdef test
        displayMessage("Players has a isRoyalFlush");
#endif
        return; 
    }
    
    if(isFourOfKind()) { 
#ifdef test
        displayMessage("Players has a isRoyalFlush");
#endif
        return; 
    }
    
    if(isFullHouse()) { 
#ifdef test
        displayMessage("Players has a isRoyalFlush");
#endif
        return; 
    }
    
    if(isFlush()){ 
#ifdef test
        displayMessage("Players has a isRoyalFlush");
#endif
        return; 
    }
    
    if(isStraight()) { 
#ifdef test
        displayMessage("Players has a isRoyalFlush");
#endif
        return; 
    }
    
    if(isThreeOfKind()) { 
#ifdef test
        displayMessage("Players has a isRoyalFlush");
#endif
        return; 
    }
    
    if(isTwoPair()) { 
#ifdef test
        displayMessage("Players has a isRoyalFlush");
#endif
        return; 
    }
    
    if(isPair()) { 
#ifdef test
        displayMessage("Players has a isRoyalFlush");
#endif
        return; 
    }
    
    startRank = 0;
    sizeHighCard = SIZE_HAND;
    handRank = static_cast<short>(HAND_RANKS::HIGHCARD);
}
void PokerHand::setCardsDemo(){
#ifdef demoStraightFlush
    set<card> tmp;
    card c ; c.first = (short)RANK::ACE; c.second = (short)SUIT::DIAMONS;
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
    #ifdef demoRoyalFlush
    set<card> tmp;
    card c ; 
    c.first = (short)RANK::ACE; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
    c.first = (short)RANK::QUEEN; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
    c.first = (short)RANK::TEN; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
    c.first = (short)RANK::KING; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
    c.first = (short)RANK::JACK; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
    tmp.swap(cards);     
    tmp.clear();
#endif    
#ifdef demoFourOfKind
    set<card> tmp;
    card c ; 
    c.first = (short)RANK::NINE; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
    c.first = (short)RANK::KING; c.second = (short)SUIT::CLUBS;
    tmp.insert(c);
    c.first = (short)RANK::NINE; c.second = (short)SUIT::SPADES;
    tmp.insert(c);
    c.first = (short)RANK::NINE; c.second = (short)SUIT::CLUBS;
    tmp.insert(c);
    c.first = (short)RANK::NINE; c.second = (short)SUIT::HEARTS;
    tmp.insert(c);
    tmp.swap(cards);     
    tmp.clear();
#endif    
#ifdef demoFullHouse
    set<card> tmp;
    card c ; 
    c.first = (short)RANK::TWO; c.second = (short)SUIT::HEARTS;
    tmp.insert(c);
    c.first = (short)RANK::TWO; c.second = (short)SUIT::CLUBS;
    tmp.insert(c);
    c.first = (short)RANK::TWO; c.second = (short)SUIT::SPADES;
    tmp.insert(c);
    c.first = (short)RANK::NINE; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
    c.first = (short)RANK::NINE; c.second = (short)SUIT::CLUBS;
    tmp.insert(c);
    showCards<set<card>>(cards,"Cards before swap: "); 
    showCards<set<card>>(tmp,"tmp before swap: "); 
    tmp.swap(cards);   
    showCards<set<card>>(cards,"Cards after swap: "); 
    showCards<set<card>>(tmp,"tmp after swap: "); 
    tmp.clear();
#endif       
#ifdef demoFlush
    set<card> tmp;
    card c ;
    c.first = (short)RANK::JACK; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
    c.first = (short)RANK::QUEEN; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
    c.first = (short)RANK::THREE; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
    c.first = (short)RANK::TEN; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
    c.first = (short)RANK::FIVE; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
    tmp.swap(cards);     
    tmp.clear();
#endif 
#ifdef demoStraight
    set<card> tmp1;
    card c1 ;
    c1.first = (short)RANK::TWO; c1.second = (short)SUIT::SPADES;
    tmp1.insert(c1);
    c1.first = (short)RANK::FOUR; c1.second = (short)SUIT::DIAMONS;
    tmp1.insert(c1);
    c1.first = (short)RANK::FIVE; c1.second = (short)SUIT::SPADES;
    tmp1.insert(c1);
    c1.first = (short)RANK::THREE; c1.second = (short)SUIT::CLUBS;
    tmp1.insert(c1);
    c1.first = (short)RANK::SIX; c1.second = (short)SUIT::DIAMONS;
    tmp1.insert(c1);
    tmp1.swap(cards);     
    tmp1.clear();
    
#endif    
#ifdef demoThreeOfKind
    set<card> tmp;
    card c ; 
    c.first = (short)RANK::NINE; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
    c.first = (short)RANK::KING; c.second = (short)SUIT::CLUBS;
    tmp.insert(c);
    c.first = (short)RANK::TWO; c.second = (short)SUIT::HEARTS;
    tmp.insert(c);
    c.first = (short)RANK::NINE; c.second = (short)SUIT::SPADES;
    tmp.insert(c);
    c.first = (short)RANK::NINE; c.second = (short)SUIT::CLUBS;
    tmp.insert(c);
    tmp.swap(cards);     
    tmp.clear();
#endif    
#ifdef demoTwoPair
    set<card> tmp;
    card c ; 
    c.first = (short)RANK::KING; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
    c.first = (short)RANK::KING; c.second = (short)SUIT::CLUBS;
    tmp.insert(c);
    c.first = (short)RANK::TWO; c.second = (short)SUIT::HEARTS;
    tmp.insert(c);
    c.first = (short)RANK::NINE; c.second = (short)SUIT::SPADES;
    tmp.insert(c);
    c.first = (short)RANK::NINE; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
    tmp.swap(cards);     
    tmp.clear();
#endif     
#ifdef demoOnePair
    set<card> tmp;
    card c ; 
    c.first = (short)RANK::KING; c.second = (short)SUIT::HEARTS;
    tmp.insert(c);
    c.first = (short)RANK::QUEEN; c.second = (short)SUIT::CLUBS;
    tmp.insert(c);
    c.first = (short)RANK::TWO; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
    c.first = (short)RANK::NINE; c.second = (short)SUIT::SPADES;
    tmp.insert(c);
    c.first = (short)RANK::NINE; c.second = (short)SUIT::DIAMONS;
    tmp.insert(c);
    tmp.swap(cards);     
    tmp.clear();
#endif   
}


