#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
class player{
private:
//currency implemented later
int tokens;
//-1 will be the default value if card isnt there
int card1= -1;
int card2= -1;
//will keep track of the highest hand of a player
public:
    player();
    std::vector<int> bestHand;
    int handVal;
    std::string name;
    std::string handName;
    int getCard1();
    int getCard2();
    int getTokens();
    void setCard1(int index);
    void setCard2(int index);
    std::vector<int> getHand();
};

#endif
