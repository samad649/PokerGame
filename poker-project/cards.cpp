#include "cards.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
using namespace std;
//constructor
cards::cards(){
    for(unsigned i = 0; i < 52; i++){
        deck[i]=new string[2];
    }
    // C=clubs, D=diamonds, H=hearts, S=spades
    //52 cards (0 index = suit) (1 index = card value)
    //sets the aces
    for(unsigned i = 0; i < 52; i+=13){
        deck[i][1]="A";
    }
    //sets the Jacks
    for(unsigned i = 10; i < 52; i+=13){
        deck[i][1]="J";
    }
    //sets the Queens
    for(unsigned i = 11; i < 52; i+=13){
        deck[i][1]="Q";
    }
    //sets the Kings
    for(unsigned i = 12; i < 52; i+=13){
        deck[i][1]="K";
    }
    //sets the suits
    for(unsigned i = 0; i < 52; i++){
        if(i<13){deck[i][0]="C";}
        else if(i<26){deck[i][0]="D";}
        else if(i<39){deck[i][0]="H";}
        else if(i<52){deck[i][0]="S";}
    }
    //sets the numbered cards
    for(int x = 1; x < 52; x+=13){
        unsigned start = x;
    for(unsigned i = 2; i < 11; i++){
        deck[start][1] = to_string(i);
        start++;

    }
    }
}
 //destructor
//cards::~cards(){
//clear();
//}
//shuffles the deck
void cards::shuffle(){
//--Create List of 0 and push indexes into it
//---Create List of 52 and use random to generate a random index betweeen 0-51
// After pop that index push into other list to get a randomizes list of the 51 different indexes


//vector with randomized order of indexes
vector<int> randomized;
//puts indexes of the deck in indexes vector
for(unsigned i = 0; i < deckSize; i++){
    deckOrder.push_back(i);
}

int decreaser = deckSize;
int randNum;

while(deckOrder.size()!=0){
    unsigned seed=time(0);
    srand(seed);
    randNum = rand() % decreaser;
    randomized.push_back(deckOrder.at(randNum));
    deckOrder.erase(deckOrder.begin()+randNum);
    decreaser--; 
}
deckOrder = randomized;

for(int i = 0; i < deckOrder.size(); i++){
   // cout<<deckOrder.at(i)<<" ";
}
}
//deallocates the 2d dynamic memory
void cards::clear(){
        for(unsigned i = 0; i < deckSize; i++){
        delete[] deck[i];
    }
    delete[] deck;
}
//reset deck to default values
void cards::reset(){
// takes the deck and resets it to the default deck order and size
deckSize = 52;
deckOrder.clear();
for(unsigned i = 0; i < deckSize; i++){
    deckOrder.push_back(i);
}
}
//will get an index which we will use to get card card from 2d string array
int cards::getCard(){
int card = deckOrder.at(deckOrder.size()-1);
deckOrder.pop_back();
deckSize -=1;
return card;
}
//will return the suit of the card given index
string cards::getSuit(int index){
    return deck[index][0];
}
//will return the value of a card given index
string cards::getValue(int index){
    return deck[index][1];
}
// returns string of card
string cards::getCardStr(int index){
    return deck[index][1] + " of " + deck[index][0];
}
//prints out the card given index
void cards::printCard(int index){
    
    cout << deck[index][1] << " of " << deck[index][0]<<endl;
    
}
//converts a string of the card value to an integer J=11,Q=12,K=13,A=1
int cards::getCardVal(int index){
    string val = getValue(index);
     if(val=="A"){
        return 1;
    }
    else if(val=="J"){
       return 11;
    }
    else if(val=="Q"){
        return 12;
    }
    else if(val=="K"){
       return 13;
    }
    else{
    return stoi(val);
    }
}