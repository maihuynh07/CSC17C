#include "Deck.h"
Deck::Deck(){
    // set size of deck is 52 cards
    size = SIZE_DECK; 
    // set status of deck is full at the beginning of a game
    status = (short)DECK_STATUS::FULL; 
    short key = 0;
    // create 52 cards of poker game
    for(short rank = (short)RANK::ACE;rank!=(short)RANK::KING+1;++rank){
        for(short suit = (short)SUIT::SPADES;suit!=(short)SUIT::CLUBS+1;++suit){
            pair<short,short> newCard;
            key++;
            newCard.first = static_cast<short>(rank);
            newCard.second = static_cast<short>(suit);
            cards.push_back(newCard);
        }
    }
    // print all card on deck
    Helper<deque<card>>::showCards(cards,string("Cards on deck:"));
    //Helper<unordered_map<short,pairs>>::showCards(cards,string("Cards on deck:"));
}


