#define demo
#define oneplayer

#include "Poker.h"
#include <algorithm>
#include <cstdlib> //srand()
#include <sstream>
#include <stack> // using stringstream to convert string to int
#include <map>
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
    messages.insert({static_cast<short>(MESSAGE::LOOSE),"You tie"});
    messages.insert({static_cast<short>(MESSAGE::END),"Good bye"});
    messages.insert({static_cast<short>(MESSAGE::INTEGER),"Please enter an positive integer from 1-5"});
    
    // initialize answer types
    replies.insert({"Y",static_cast<short>(ANSWER::YES)});
    replies.insert({"N",static_cast<short>(ANSWER::NO)});
    
}
void Poker::getInput(){
#ifdef oneplayer
    if(state==static_cast<short>(GAME_STATE::START)){
        string rep;
        
        // display message to players :"Do you want to play a new game (y/n)?";
        displayMessage(questions[question]); 
        getline(cin,rep);
        // save answer of players
        transform(rep.begin(), rep.end(), rep.begin(), ::toupper);
        player.setReply(replies[rep]);
        
        // set question to next question
        ++question; 
        return;
    }
    if(state==static_cast<short>(GAME_STATE::DEAL)){
        
        int numberOfCard = 0; // number of card which player will discard;
        while(state == static_cast<short>(GAME_STATE::DEAL)){
            string rep;
            displayMessage(questions[question]);
            
            // if ask player "Do you want to change any card (y/n):"
            if(question == static_cast<short>(QUESTION::CHANGECARD)){
                getline(cin,rep);
                // save answer of players
                transform(rep.begin(), rep.end(), rep.begin(), ::toupper);
                player.setReply(replies[rep]);
                
                // if player choose  not draw
                if(replies[rep] == static_cast<short>(ANSWER::NO) ){
                    
                    // go to next state
                    state = static_cast<short>(GAME_STATE::DRAW);
                    question +=3;
                    break;
                }
            }
            
            // if player type number of card will be discarded
            if(question == static_cast<short>(QUESTION::NUMBEROFCARD)){
                // using stringstream to convert rep(string) to numberOfCard(int)
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
                        
                        // remove cards are drawn from deck
                        deck.cards.pop_back();
                        count++;
                    }
                }
                
                cin.ignore();
                cin.clear();
                
                // go to next state
                state = static_cast<short>(GAME_STATE::DRAW);
            }
            
            // set question to next question
            ++question; 
        }
        return;
    }
    if(state == static_cast<short>(GAME_STATE::REPLAY)){
        string rep;
        cin.clear();
        displayMessage(questions[question]); 
        getline(cin,rep);
        // save answer of players
        transform(rep.begin(), rep.end(), rep.begin(), ::toupper);
        player.setReply(replies[rep]);
        
        if(player.getReply() == static_cast<short>(ANSWER::YES)){
            status = static_cast<short>(GAME_STATUS::START);
            question = static_cast<short>(QUESTION::START);
            state = static_cast<short>(GAME_STATE::START);
        }
        else{
            status = static_cast<short>(GAME_STATUS::END);
        }
        // set question to next question
        ++question; 
    }
#endif
    
}
void Poker::update(){
#ifdef oneplayer
    
    if(state == static_cast<short>(GAME_STATE::START)){
        if(player.getReply() ==  static_cast<short>(ANSWER::YES)){
            
            // set state of game
            state = static_cast<short>(GAME_STATE::DEAL);
            status = static_cast<short>(GAME_STATUS::PLAYING);
            
            dealCard();
            rankHand();
        }
    }
    if(state == static_cast<short>(GAME_STATE::DRAW)){
        drawCard();
        rankHand();
        state = static_cast<short>(GAME_STATE::SCORE);
    }
    if(state == static_cast<short>(GAME_STATE::SCORE)){
        score();
        state = static_cast<short>(GAME_STATE::SHOW);
        return;
    }
    if(state == static_cast<short>(GAME_STATE::SHOW)){
        state = static_cast<short>(GAME_STATE::REPLAY);
        return;
    }
    
#endif
}

void Poker::dealCard(){
    
    //step1: shuffle 52 cards on deck
    srand(unsigned(time(0)));// Use a different seed value so that we don't get same result each time we run this program
    random_shuffle(deck.cards.begin(), deck.cards.end());// using built-in random generator
  
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
#endif    
    
}
void Poker::rankHand(){

#ifdef oneplayer
    player.rank();
    dealer.rank();
    
    showCards(player.getRankedCards(),"Player Ranked Cards: ");
    showCards(dealer.getRankedCards(),"Dealer Ranked Cards: ");
#endif
}
void Poker::drawCard(){
    
    if(!deck.disCardedCards.empty()) 
    {
        player.changeCards(deck.disCardedCards);
        player.sortBySuit();
    }
    AIComputer();
    
}

void Poker::render(){
    if(state == static_cast<short>(GAME_STATE::SHOW)){
        if(dealer.getScore() < player.getScore()){
            displayMessage(messages[static_cast<short>(MESSAGE::WIN)]);
        }
        else if(dealer.getScore()> player.getScore()){
            displayMessage(messages[static_cast<short>(MESSAGE::LOOSE)]);
        }
        else
            displayMessage(messages[static_cast<short>(MESSAGE::TIE)]); 
        
    }
    if(status == static_cast<short>(GAME_STATUS::END)){
        displayMessage(messages[static_cast<short>(MESSAGE::END)]);
        exit(0);
    }
}
void Poker::score(){
    set<card> cp = player.getCards();
    set<card> cd = dealer.getCards();
    
    if(player.getHandRank() == dealer.getHandRank()){
        
        if(dealer.getHandRank() == static_cast<short>(HAND_RANKS::ROYALFLUSH)){
            player.setScore(FULL_SCORE/2);
            dealer.setScore(FULL_SCORE/2);
            return;
        }
        
        // type: 2D 3D 4D 5D 6D
        if(dealer.getHandRank() == static_cast<short>(HAND_RANKS::STRAIGHTFLUSH)){
            auto itd = cd.end();
            auto itp = cp.end();
            if (itd->first == itp->first){
                player.setScore(FULL_SCORE/2);
                dealer.setScore(FULL_SCORE/2);
            }
            else if(itd->first > itp->first){
                dealer.setScore(FULL_SCORE);
                player.setScore(0);
            }
            else{
                dealer.setScore(0);
                player.setScore(FULL_SCORE);
            }
            return;
        }
        
        // type: xxxx y , x yyyy
        if(dealer.getHandRank() == static_cast<short>(HAND_RANKS::FOUROFKIND)){
            
            // get pos of four of kind
            auto itd = next(cd.begin(),dealer.getStartRank());
            auto itp = next(cp.begin(),player.getStartRank());
            
            // step 1: compare four of kind on first element 
            if(itd->first > itp->first){
                dealer.setScore(FULL_SCORE);
                player.setScore(0);
            }
            else if(itd->first < itp->first){
                dealer.setScore(0);
                player.setScore(FULL_SCORE);
            }
            
            // step 2: if four of kind tie, compare high card
            else {
                
                // remove four of kind from set of cards to get high card
                cd.erase(itd,next(itd,TWOPAIR));
                cp.erase(itp,next(itp,TWOPAIR)); 
                
                itd = cd.begin();
                itp = cp.begin();
                
                if(itd->first > itp->first){
                    dealer.setScore(FULL_SCORE);
                    player.setScore(0);
                }
                else if(itd->first < itp->first){
                    dealer.setScore(0);
                    player.setScore(FULL_SCORE);
                }
                else{
                    player.setScore(FULL_SCORE/2);
                    dealer.setScore(FULL_SCORE/2);
                }
                    
            }
            return;
        }
        
        // type: xxx yy, xx yyy
        if(dealer.getHandRank() == static_cast<short>(HAND_RANKS::FULLHOUSE)){
            
            // get pos of three of kind
            auto itd = next(cd.begin(),dealer.getStartRank());
            auto itp = next(cp.begin(),player.getStartRank());
            
            // step 1: at first, compare three of kind
            if(itd->first > itp->first){
                dealer.setScore(FULL_SCORE);
                player.setScore(0);
            }
            else if(itd->first < itp->first){
                dealer.setScore(0);
                player.setScore(FULL_SCORE);
            }
            
            // step 2: compare remained one pair
            else{
                
                // remove three of kind from set of cards to get remained pair
                cd.erase(itd,next(itd,THREEOFKIND));
                cp.erase(itp,next(itp,THREEOFKIND));
                
                itd = cd.begin();
                itp = cp.begin();
                
                if(itd->first > itp->first){
                    dealer.setScore(FULL_SCORE);
                    player.setScore(0);
                }
                else if(itd->first < itp->first){
                    dealer.setScore(0);
                    player.setScore(FULL_SCORE);
                }
                else{
                    dealer.setScore(FULL_SCORE/2);
                    player.setScore(FULL_SCORE/2);
                }
            }
            return;
        }
        
        // type: 2D 9D 3D 6D 5D
        if(dealer.getHandRank() == static_cast<short>(HAND_RANKS::FLUSH)){
            
            auto itp = cp.rbegin();
            auto itd = cd.rbegin();
            for(;itp != cp.rend(),itd != cd.rend(); ++itp,++itd){
                if((*itd).first == (*itp).first) continue;
                if((*itd).first > (*itp).first){
                    dealer.setScore(FULL_SCORE);
                    player.setScore(0);
                    break;
                }
                else {
                    dealer.setScore(0);
                    player.setScore(FULL_SCORE);
                    break;
                }
            }
            if(itp == cp.rend()){
                dealer.setScore(FULL_SCORE/2);
                player.setScore(FULL_SCORE/2);
            }
        }
            
        // type: 6D 7S 8J 9D 10H
        if(dealer.getHandRank() == static_cast<short>(HAND_RANKS::STRAIGHT)){
            
            auto itd = prev(cd.end());
            auto itp = prev(cp.end());
            if(itd->first == itp->first){
                dealer.setScore(FULL_SCORE/2);
                player.setScore(FULL_SCORE/2);
            }
            else if (itd->first == itp->first){
                dealer.setScore(FULL_SCORE);
                player.setScore(0);
            }
            else{
                dealer.setScore(0);
                player.setScore(FULL_SCORE);
            }
            return;
        }
        
        // type: xxx y z,  x yyy z, x y zzz
        if(dealer.getHandRank() == static_cast<short>(HAND_RANKS::THREEOFKIND)){
            
            
            short posHighCardP = player.getStartRank();
            short posHighCardD = dealer.getStartRank();
            
            // get pos of three of kind
            auto itd = next(cd.begin(),posHighCardD);
            auto itp = next(cp.begin(),posHighCardP);
            
            // step 1: compare "three of kind" on first element 
            if(itd->first > itp->first){
                dealer.setScore(FULL_SCORE);
                player.setScore(0);
            }
            else if(itd->first < itp->first){
                dealer.setScore(0);
                player.setScore(FULL_SCORE);
            }
            
            // step 2: if threeofkind tie, sequently compare high cards
            else{
                
                // remove threeofkind from set of cards to get list of high card
                cd.erase(itd,next(itd,THREEOFKIND));
                cp.erase(itp,next(itp,THREEOFKIND));
                set<card>::reverse_iterator itd1= cd.rbegin();
                set<card>::reverse_iterator itp1 = cp.rbegin();
                for(;itd1!=cd.rend() && itp1!=cp.rend();++itd1,++itp1){
                        if(itd1->first > itp1->first){
                            dealer.setScore(FULL_SCORE);
                            player.setScore(0);
                        }
                        else if(itd1->first < itp1->first){
                            dealer.setScore(0);
                            player.setScore(FULL_SCORE);
                        }
                        else{
                            dealer.setScore(FULL_SCORE/2);
                            player.setScore(FULL_SCORE/2);
                        }
                }
                    
            }
            return;
        }

        // type: xx yy z,  x yy zz, xx y zz 
        if(dealer.getHandRank() == static_cast<short>(HAND_RANKS::TWOPAIR)){
            
            auto itd = cd.begin();
            auto itp = cp.begin();
            
            short posHighCardD  = dealer.getStartRank();
            short posHighCardP = player.getStartRank();
            
            itd = next(cd.begin(),posHighCardD);
            itp = next(cp.begin(),posHighCardP);
            
            // find pos of max(two pair)
            if( posHighCardD + ONEPAIR < SIZE_HAND) itd= next(itd,ONEPAIR);
            if( posHighCardP + ONEPAIR < SIZE_HAND) itp= next(itp,ONEPAIR);
            
            // step 1: compare max(two pair)
            if(itd->first > itp->first){
                dealer.setScore(FULL_SCORE);
                player.setScore(0);
            }
            else if(itd->first < itp->first){
                dealer.setScore(0);
                player.setScore(FULL_SCORE);
            }
            
            // step 2: if max(two pair) tie, compare remained pair
            else{
                // find pos of remained pair
                itd = posHighCardD + ONEPAIR < SIZE_HAND? prev(itd,ONEPAIR):cd.begin();
                itp = posHighCardP + ONEPAIR < SIZE_HAND? prev(itp,ONEPAIR):cp.begin();
                
                // compare remained pair
                if(itd->first > itp->first){
                    dealer.setScore(FULL_SCORE);
                    player.setScore(0);
                }
                else if(itd->first < itp->first){
                    dealer.setScore(0);
                    player.setScore(FULL_SCORE);
                }

                // step 3: if remained pair tie, compare high card
                else{
                    // find pos of high card
                    itd = next(cd.begin(),(posHighCardD+TWOPAIR)% SIZE_HAND);
                    itp = next(cp.begin(),(posHighCardP+TWOPAIR)% SIZE_HAND);
                    
                    // compare high card
                    if(itd->first > itp->first){
                        dealer.setScore(FULL_SCORE);
                        player.setScore(0);
                    }
                    else if(itd->first < itp->first){
                        dealer.setScore(0);
                        player.setScore(FULL_SCORE);
                    }
                    else
                    {
                        dealer.setScore(FULL_SCORE/2);
                        player.setScore(FULL_SCORE/2);
                    }
                }
                
            }
            
            return;
        }
        
        // type: xx y z t, x yy z t, x y zz t, x y z tt
        if(dealer.getHandRank() == static_cast<short>(HAND_RANKS::ONEPAIR)){
            
            auto itd = cd.begin();
            auto itp = cp.begin();
            
            short posHighCardD  = dealer.getStartRank();
            short posHighCardP = player.getStartRank();
            
            // find pos of pair
            itd = next(cd.begin(),posHighCardD);
            itp = next(cp.begin(),posHighCardP);
            
            
            // step 1: compare pair
            if(itd->first > itp->first){
                dealer.setScore(FULL_SCORE);
                player.setScore(0);
            }
            else if(itd->first < itp->first){
                dealer.setScore(0);
                player.setScore(FULL_SCORE);
            }

            // step 2: if pair tie, compare sequence high card, start from highest card
            else
            {
                // remove pair from set of cards to get list of high card
                cd.erase(itd,next(itd,ONEPAIR));
                cp.erase(itp,next(itp,ONEPAIR));                
                set<card>::reverse_iterator itd1= cd.rbegin();
                set<card>::reverse_iterator itp1 = cp.rbegin();
                for( ;itd1!=cd.rend() && itp1!=cp.rend();++itd1,++itp1){
                        if(itd1->first > itp1->first){
                            dealer.setScore(FULL_SCORE);
                            player.setScore(0);
                        }
                        else if(itd1->first < itp1->first){
                            dealer.setScore(0);
                            player.setScore(FULL_SCORE);
                        }
                        else{
                            dealer.setScore(FULL_SCORE/2);
                            player.setScore(FULL_SCORE/2);
                        }
                }
            }
            return;
        }
        
        // high card
        else{
            
            // compare sequently cards in set , start from highest card
            set<card>::reverse_iterator itd1= cd.rbegin();
            set<card>::reverse_iterator itp1 = cp.rbegin();
            for( ;itd1!=cd.rend() && itp1!=cp.rend();++itd1,++itp1){
                    if(itd1->first > itp1->first){
                        dealer.setScore(FULL_SCORE);
                        player.setScore(0);
                        break;
                    }
                    else if(itd1->first < itp1->first){
                        dealer.setScore(0);
                        player.setScore(FULL_SCORE);
                        break;
                    }
            }
            if(itd1== cd.rend()){
                dealer.setScore(FULL_SCORE/2);
                player.setScore(FULL_SCORE/2);
            }
        }
    }
    else if(player.getHandRank()> dealer.getHandRank()){
        player.setScore(FULL_SCORE);
        dealer.setScore(0);
    }
    else{
        player.setScore(0);
        dealer.setScore(FULL_SCORE);
    }
    
    cp.clear();
    cd.clear();
}
void Poker::AIComputer(){

    dealer.rank();
    
    set<card> cd = dealer.getCards();
    bool flag = false; // flag = true if has drawing card
    
    if(dealer.getSizeHighCard()==0)  return;
    
    //if isFourOfKind() isThreeOfKind() isTwoPair() isPair() isHighCard())
    int count = 0; 

    // step 1: find pos of first high card
    short startRank = dealer.getStartRank();
    short sizeHighCard = dealer.getSizeHighCard();
    short posHighCard = (startRank+(SIZE_HAND-sizeHighCard))%SIZE_HAND;
    auto ithc = next(cd.begin(),posHighCard);

    // step 2: test which high cards need to decide drawing or not
    while(count< sizeHighCard){

        // if high card too low, process drawing card.
        if(ithc->first < LOWCARD){

            // step 2: save to discardedPos
            dealer.setDiscardedPoss(posHighCard+1);   

            // step 3: save cards are drawn into deck.disCardCards
            deck.disCardedCards.push(deck.cards.back());

            // step 4: remove cards are drawn from deck
            deck.cards.pop_back();

            // set flag
            flag = true;
        }

        posHighCard++;
        count++;
        ithc = next(cd.begin(),posHighCard%SIZE_HAND);
    }

    if(flag){

        // step 5: change card
        dealer.changeCards(deck.disCardedCards);

        // arrange cards on suit
        dealer.sortBySuit();
    }
}

