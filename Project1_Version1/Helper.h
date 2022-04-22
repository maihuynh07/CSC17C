#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string> // include string class in c++
#include <set>
#include <algorithm>
using namespace std;

// name definitions
enum class SUIT:short{ CLUBS, DIAMONS, HEARTS, SPADES };// 4 suits of cards in Poker game
enum class RANK:short{ ACE, TWO , THREE , FOUR, FIVE , SIX , SEVEN, EIGHT , NINE, TEN, JACK, QUEEN, KING}; // value or rank of card from 2-10 and JACK,QUEEN,KING and ACE = one
enum class DECK_STATUS:short{ FULL, DEALED}; // define status of deck
enum class GAME_STATUS:short{ START, PLAYING, END}; // define state of a game
enum class GAME_STATE:short{ START, DEAL,DRAW,SCORE,SHOW ,REPLAY} ; // state of a game
enum class QUESTION: short{ START, CHANGECARD, NUMBEROFCARD,DISCARDCARD,REPLAY};// sequence questions will ask players
enum class MESSAGE: short { WELCOME, WIN, LOOSE, TIE, END, INTEGER}; // messages to display to players 
enum class ANSWER: short {YES,NO}; // answer of players
enum class HAND_RANKS: short{HIGHCARD,ONEPAIR,TWOPAIR,THREEOFKIND,STRAIGHT,FLUSH,FULLHOUSE,FOUROFKIND,STRAIGHTFLUSH,ROYALFLUSH}; // descriptions of hand ranks (from lowest to highest)

static const string YES = "Y"; 
static const string NO = "N";
static const short SIZE_DECK = 52; // number of cards of Poker game
static const short SIZE_HAND = 5; // number of cards of a hand Poker
static const short FOUROFKIND = 4 ; // number of cards of "four of kind" 
static const short THREEOFKIND = 3; // number of cards of three of kind
static const short TWOPAIR = 4; // number of cards of 2 pair
static const short ONEPAIR = 2; // number of cards of 1 pair
static const short LOWCARD = 5; // define rank of high card, to decide drawing card or not
static const short FULL_SCORE = 100; // highest score in a game.

typedef pair<short, short> card; // define type named card

struct comp {
    template <typename T>
  
    // Comparator function
    bool operator()(const T& l,
                    const T& r) const
    {
        if (l.second != r.second) {
            return l.second < r.second;
        }
        return l.first < r.first;
    }
};  // Comparison function for sorting the set by increasing order of its pair's second value (suit). if second is the same, sort on first (rank)

class Helper{
public:
    string sRank(const short& rank); // convert from short to name of rank
    string sSuit(const short& suit); // convert from short to name of suit
    void showCards(const set<card>& cards,string topic); // display cards on players
    void displayMessage(string message); // show message to players
};

#endif /* HELPER_H */

