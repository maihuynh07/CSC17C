#include <iostream>
#include <string> // include string class in c++
#include <set>
#include <algorithm>
using namespace std;
#ifndef HELPER_H
#define HELPER_H
/*enum class SUIT{ SPADES=1, DIAMONDS=2, HEARTS=3,CLUBS =4};// 4 suits of cards in Poker game
enum class RANK{ ACE=1, TWO =2, THREE =3, FOUR=4, FIVE =5, SIX =6, SEVEN =7, EIGHT =8, NINE=9, TEN=10, JACK=11, QUEEN=12, KING = 13}; // value or rank of card from 2-10 and JACK,QUEEN,KING and ACE = one
*/
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
static const short TWOPAIR = 2; // number of cards of 2 pair
static const short ONEPAIR = 2; // number of cards of 1 pair
static const short LOWCARD = 5; // define rank of high card, to decide drawing card or not
static const short FULL_SCORE = 100; // highest score in a game.

typedef pair<short, short> card;

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
};
/*
bool comparator(card& card1,card& card2){
        if(card1.second == card2.second)
        return card1.first < card2.first;
        return card1.second < card2.second;
}*/
template <class T>
static void shuffle(const T &cards) // shuffle cards
{
    
}
// sort cards by rank
template <class T>
static void sortByRank(T &cards){
    
}; 
static string sRank(const short& rank){
    switch(rank){
        case 0: return "ACE";
        case 1: return "TWO";
        case 2: return "THREE";
        case 3: return "FOUR";
        case 4: return "FIVE";
        case 5: return "SIX";
        case 6: return "SEVEN";
        case 7: return "EIGHT";
        case 8: return "NINE";
        case 9: return "TEN";
        case 10: return "JACK";
        case 11: return "QUEEN";
        case 12: return "KING";
        default: return "KING"; 
    }
}
static string sSuit(const short& suit){
    switch(suit){
        case 0: return string("SPADES");
        case 1: return string("DIAMONDS");
        case 2: return string("HEARTS"); 
        default: return string("CLUBS");
    }
}
template <class T>
static void showCards(const T& cards,string topic){ // print cards
    cout << endl<<"********"<<topic<<"***********";
    cout << endl;
    cout << "\tRANK\tSUIT";
    cout << endl;
    int count = 0;
    for(auto card = cards.begin();card!=cards.end();++card){
        cout<<++count<<"."<<"\t"<<sRank(card->first)<<"\t"<<sSuit(card->second)<<endl;
    }
    cout<<endl;
}
static void displayMessage(string message){
    cin.clear();
    cout<<endl<<message;
}
/* @name: compareSuit: comparator function that orders the cards according to the second (suit). 
 *                     if the second is the same, compare the first value (rank)
 * parameter: card1,card2 is a pair card
 * return: true or false
 */

#endif /* HELPER_H */

