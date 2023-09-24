#include <string>
#include <vector>
#pragma once
#ifndef CARDS_H
#define CARDS_H
using std::string;
using std::vector;

class cards{
private:
//variables
unsigned deckSize = 52;
//vector holds indexes of the deck
vector<int> deckOrder;
public:
//public deck pool
string** deck = new string*[52];
//constructor
cards();
//destuctor
//~cards();
//functions
//changes the deck order vector of indexes
void shuffle();
//deallocates dyanamic memory
void clear();
//resets the deck to default values
void reset();
//returns last index of the deckOrder vector and updates the decksize & pops that value from the vector
int getCard();
//returns the suit of the card given index
string getSuit(int index);
//returns value of a card given index
string getValue(int index);
//returns the card as a string with the actual suit and value
string getCardStr(int index);
//prints out the card given index
void printCard(int index);
//get card value represented as an integer J=11,Q=12,K=12,A=1
int getCardVal(int index);
};

#endif
