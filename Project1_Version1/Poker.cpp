#define demo
#define oneplayer

#include "Poker.h"
#include <algorithm>
#include <cstdlib> //srand()
#include <sstream>
#include <stack> // using stringstream to convert string to int
void Poker::initializeGame(){
    
    // initialize status of game
    status = static_cast<short>(GAME_STATUS::START);
    question = static_cast<short>(QUESTION::START);
    state = static_cast<short>(GAME_STATE::START);
    
    // initialize list of questions
    questions.insert({static_cast<short>(QUESTION::START),"Do you want to play a game (y/n): "});
    questions.insert({static_cast<short>(QUESTION::CHANGECARD),"Do you want to change any card (y/n): "});
    questions.insert({static_cast<short>(QUESTION::NUMBEROFCARD),"How many cards you want to draw (number > 0): "});
    questions.insert({static_cast<short>(QUESTION::DISCARDCARD),"Cards you want to discard (ex: 1 2 3, start position = 1): "});
    questions.insert({static_cast<short>(QUESTION::REPLAY),"Do you want to replay a game (y/n): "});
    
    // initialize list of messages
    messages.insert({static_cast<short>(MESSAGE::WELCOME),"Welcome you to FIVE DRAW POKER game"});
    messages.insert({static_cast<short>(MESSAGE::WIN),"You win"});
    messages.insert({static_cast<short>(MESSAGE::LOOSE),"You loose"});
    messages.insert({static_cast<short>(MESSAGE::END),"Good bye"});
    messages.insert({static_cast<short>(MESSAGE::INTEGER),"Please enter an positive integer from 1-5"});
    
    // initialize answer types
    replies.insert({"Y",static_cast<short>(ANSWER::YES)});
    replies.insert({"N",static_cast<short>(ANSWER::NO)});
    
}
void Poker::getInput(){
#ifdef oneplayer
    if(status==static_cast<short>(GAME_STATE::START)){
        short rep;
        // display message to players :"Do you want to play a new game (y/n)?";
        displayMessage(questions[question]); 
        cin>>rep;
        cin.ignore();
        // set answer of players
        player.setReply(rep);
        
        // set question to next question
        ++question; 
        return;
    }
    if(status==static_cast<short>(GAME_STATE::DEAL)){
        
        int numberOfCard = 0; // number of card which player will discard;
        while(state != static_cast<short>(GAME_STATE::DRAW)){
            string rep;
            displayMessage(questions[question]);
            // if ask player "Do you want to change any card (y/n):"
            if(question == static_cast<short>(QUESTION::CHANGECARD)){
                cin.clear();
                getline(cin,rep);
                cin.ignore();
                // save answer of players
                player.setReply(replies[rep]);
                
                // if player choose  not draw
                if(replies[rep] == static_cast<short>(ANSWER::NO) ){
                    
                    // go to next state
                    state == static_cast<short>(GAME_STATE::DRAW);
                    break;
                }
            }
            // if player type number of card will be discarded
            if(question == static_cast<short>(QUESTION::NUMBEROFCARD)){
                // using stringstream to convert rep(string) to numberOfCard(int)
                cin.ignore();
                getline(cin,rep);
                stringstream number(rep);
                number >> numberOfCard; 
            }
            // if player type position of cards will be discarded
            if(question == static_cast<short>(QUESTION::DISCARDCARD)){
                int number, count = 1;
                
                // get pos from user input
                while(count<=numberOfCard){
                    cin >> number;
                    if(number<=0 or number>SIZE_HAND){ // guarantee number of card is always smaller SIZE_HAND
                        displayMessage(messages[static_cast<short>(MESSAGE::INTEGER)]);
                        count = 1;
                    }
                    else{
                        // save to discardedPos
                        player.setDiscardedPoss(number);
                        
                        // save cards are drawn into deck.disCardCards
                        deck.disCardedCards.push(deck.cards.back());
                        deck.cards.pop_back();
                        count++;
                    }
                }
                
                // go to next state
                state = static_cast<short>(GAME_STATE::DRAW);
            }
            
            // set question to next question
            ++question; 
        }
        return;
    }
#endif
    
}
void Poker::update(){
#ifdef oneplayer
    
    if(state == static_cast<short>(GAME_STATE::START)){
        if(player.getReply() ==  static_cast<short>(ANSWER::YES)){
            // save state of game
            state = static_cast<short>(GAME_STATE::DEAL);
            status = static_cast<short>(GAME_STATUS::PLAYING);
            
            dealCard();
            rankHand();
        }
    }
    if(state == static_cast<short>(GAME_STATE::DRAW)){
        drawCard();
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
#ifdef demo
    player.setCardsDemo();
#endif
    player.sortBySuit();

    if(player.isFlush()) displayMessage("Players has a flush");
    if(player.isStraight()) displayMessage("Players has a straight");
    if(player.isStraightFlush()) displayMessage("Players has a isStraightFlush");
    if(player.isRoyalFlush()) displayMessage("Players has a isRoyalFlush");
    if(player.isFourOfKind()) displayMessage("Players has a isFourOfKind");
    if(player.isFullHouse()) displayMessage("Players has a isFullHouse");
    if(player.isThreeOfKind()) displayMessage("Players has a isThreeOfKind");
    if(player.isTwoPair()) displayMessage("Players has a isTwoPair");
    if(player.isPair()) displayMessage("Players has a isPair");
    showCards(player.getCards(),string("Cards after sort by suit:"));
    showCards(player.getRankedCards(),"\nRanked Cards: \n");
#endif
}
void Poker::drawCard(){
    player.changeCards(deck.disCardedCards);
}

void Poker::render(){
#ifdef demo
    //showCards(dealer.getCards(),string("Cards on poker hand (dealer):"));
    showCards(player.getCards(),string("Cards on poker hand (player):"));
#endif
}

