#include "player.h"
#include "cards.h"
#pragma once
#ifndef GAME_H
#define GAME_H
class game{
private:
cards gameDeck;
player user;
player* list;
unsigned players = 0;
public:
//5 community cards
int flop1 = -1;
int flop2 = -1;
int flop3 = -1;
int river1 = -1;
int turn1 = -1;
//constructor
game(unsigned players);
//destructor
//~game();
//functions
//returns a list of available cards given a player with the community cards(if applicable) & the length
std::pair<int*,int> getCardlist(player p);
//returns reference to user player
player& getUser();
//returns the list of other players
player* getPlayerlist();
//returns the gameDeck used
cards getDeck();
//assign cards at the beginning of the round to X player
void assign();
//assign the 3 cards to flop 
void flop();
//assign turn
void turn();
//assign river
void river();
void gameMenu();
// given a list of cards and a player it will determine the best hand and assign that value to player
vector<player*> winner(player* user, player* list);
//given a players hand of cards(with size of the card list) determines best hand
vector<int> bestHand(int* cards, int length, player &p);
//HELPER FUNCTION for bestHand
vector<int> straightFlush(string flushVal, vector<int> straightCards,player &P);
};
#endif