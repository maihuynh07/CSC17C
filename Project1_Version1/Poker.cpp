#define demo
#define oneplayer

#include "Poker.h"
#include <algorithm>
#include <cstdlib> //srand()
void Poker::initializeGame(){
    status = static_cast<short>(GAME_STATUS::START);
}
void Poker::getInput(){
#ifdef oneplayer
    string rep ;
    cout<<"Do you want to play a new game (y/n)?";
    getline(cin,rep);
    player.setReply(rep);
#endif
    
}
void Poker::update(){
#ifdef oneplayer
    if(player.getReply() == "Y" ||player.getReply() == "y"){
        status = static_cast<short>(GAME_STATUS::PLAYING);
        state = static_cast<short>(GAME_STATE::DRAW);
        dealCard();
        rankHand();
    }
    
#endif
}

void Poker::dealCard(){
    //step1: shuffle 52 cards on deck
    srand(unsigned(time(0)));// Use a different seed value so that we don't get same result each time we run this program
    random_shuffle(deck.cards.begin(), deck.cards.end());// using built-in random generator
#ifdef demo    //display cards on deck only demo mode
    showCards<deque<card>>(deck.cards,"Cards on deck after shuffle"); // print all cards on deck
#endif   
    //step2: deal 5 cards per 1 player , sequence from top of deck 
#ifdef oneplayer
    deque<card>::iterator itDeckCards = deck.cards.begin();
    short keyPlayer = 0;// key for cards of player
    short keyDealer = 0;// key for cards of player
    short dealedCard = 0;// number of cards is dealed
    for(;itDeckCards!=deck.cards.end() && dealedCard<=SIZE_HAND+SIZE_HAND;++itDeckCards,++dealedCard){
        if(dealedCard%2==0) {
            dealer.addCards(keyDealer++,deck.cards.back());
        }
        else{
            player.addCards(keyPlayer++,deck.cards.back());
        }
        deck.cards.pop_back();
    }

#else
    list<PokerHand>::iterator itPlayer = player.begin();
    multimap<short,pairs>::iterator itDeckCards = deck.cards.begin();
    for(;iterator!=player.end();++iterator){
        for(;itDeckCards!=deck.cards.end();++itDeckCards){
            
        }
    }
#endif    
    
}
void Poker::rankHand(){
    
#ifdef oneplayer
    player.sortBySuit();
    if(player.isFlush()) displayMessage("Players has a flush");
    if(player.isStraight()) displayMessage("Players has a straight");
    showCards(player.getCards(),string("Cards on players after sort by suit:"));
    showCards(player.getRankedCards(),"\nRanked Cards: \n");
#endif
}
void Poker::render(){
#ifdef demo
    showCards(dealer.getCards(),string("Cards on poker hand (dealer):"));
    showCards(player.getCards(),string("Cards on poker hand (player):"));
    showCards(deck.cards,"Cards on deck after dealing:"); // print all cards on deck
#endif
}

