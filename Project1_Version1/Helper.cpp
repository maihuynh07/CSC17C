#include "Helper.h"

string Helper::sRank(const short& rank){
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

string Helper::sSuit(const short& suit){
    switch(suit){
        case 0: return string("SPADES");
        case 1: return string("DIAMONDS");
        case 2: return string("HEARTS"); 
        default: return string("CLUBS");
    }
}

void Helper::showCards(const set<card>& cards,string topic){ // print cards
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

void Helper::displayMessage(string message){
    cin.clear();
    cout<<endl<<message;
}


