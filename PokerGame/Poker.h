#define oneplayer
#ifndef POKER_H
#define POKER_H
#include "PokerHand.h"
#include "Deck.h"
#include "Helper.h"

class Poker: public Helper{
#ifdef oneplayer
    PokerHand player;
    PokerHand dealer;
#else
    list<PokerHand> player;
#endif
    Deck deck;
    short status ; // status of game
    short state; // state of a game
    short question; // question to players
    map<short,string> messages; // messages to display to players through a game
    map<short,string> questions; // questions to players through a game
    map<string, short> replies; // answer of players
public:
    void initializeGame(); // initialize a game
    void getInput(); // get input from users
    void update(); 
    void render();
    short getStatus() const{return status;}; // get status of game
    void setStatus(short ss){status = ss;}; // set status of game
    short getState() const{return state;}; // get state of game
    void setState(short st){state = st;}; // set state of game
    void dealCard(); // deal five cards per 1 player
    void drawCard(); // exchange some cards on players and deck
    void rankHand(); // rank players to score
    
    /*  ************************************************************************
     *  @name: score: manipulate score of players in a game.
     *  Hands are ranked as follows (from high to low):
        •	Straight Flush
        •	Four of a Kind
        •	Full House
        •	Flush
        •	Straight
        •	Three of a Kind
        •	Two Pair
        •	Pair
        •	High Card
     * *************************************************************************/
    void score(); 
    
    /****************************************************************************
     * @name: AIComputer(): play role as dealer, process drawing card or not, do after player draw card.
     * *************************************************************************/
    void AIComputer();
    
    void resetGame(); // reset game after user choose replay

    set<card> getCards(int role) const{ return role==0?player.getCards():dealer.getCards();};

    deque<string> getImages(int role)const; // return list of path of images of 5 cards of players(0) or dealer(1)
    bool setDiscardedPoss(int num); // save position of a card which is discarded, and draw 1 card from the deck
    short update(short);// update game with short is state current and if bool is true, ignore do this step
    string getResult();// return score of player if role = 0, dealer if role = 1
private:

};

#endif /* POKER_H */

