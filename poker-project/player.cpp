#include <iostream>
#include "player.h"

using namespace std;

    player::player(){
       tokens = 100;
       cout  << tokens << endl;
       handName = "Not enough cards";
    }

    vector<int> player::getHand(){
        return bestHand;
    }
    void player::setCard1(int index){
        card1 = index;
    }
    void player::setCard2(int index){
        card2 = index;
    }
    int player::getTokens(){
        return tokens;
    }
    int player::getCard1(){
        return card1;
    }
    int player::getCard2(){
        return card2;
    }

