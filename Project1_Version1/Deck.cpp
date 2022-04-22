#include <list>

#include "Deck.h"
Deck::Deck(){
    
    // set size of deck is 52 cards
    size = SIZE_DECK; 
    
    // set status of deck is full at the beginning of a game
    status = static_cast<short>(DECK_STATUS::FULL);
    
    short key = 0;
    // create 52 cards of poker game
    for(short rank = (short)RANK::ACE;rank!=(short)RANK::KING+1;++rank){
        for(short suit = (short)SUIT::CLUBS;suit!=(short)SUIT::SPADES+1;++suit){
            pair<short,short> newCard;
            key++;
            newCard.first = static_cast<short>(rank);
            newCard.second = static_cast<short>(suit);
            cards.push_back(newCard);
        }
    }
    
    // print all card on deck
    showDeck();
}
void Deck::drawCard(){
    
    card dc = cards.back();
    
    // step 1: save cards are drawn into deck.disCardCards
    disCardedCards.push(cards.back());

    // step 2: remove cards are drawn from deck
    cards.pop_back();
    
    // set size of deck
    size--;
    
}
void Deck::resetDeck(set<card>& ds){
    cards.insert(cards.end(),ds.begin(),ds.end());
    size = SIZE_DECK;
    status = static_cast<short>(DECK_STATUS::FULL);
}
void Deck::showDeck(){ // print cards
    cout << endl<<"********"<<"Deck cards:"<<"***********";
    cout << endl;
    cout << "\tRANK\tSUIT";
    cout << endl;
    int count = 0;
    for(auto card = cards.begin();card!= cards.end();++card){
        cout<<++count<<"."<<"\t"<<sRank(card->first)<<"\t"<<sSuit(card->second)<<endl;
    }
    cout<<endl;
}   



