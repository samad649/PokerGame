#include <iostream>
#include "game.h"
#include "player.h"
#include "cards.h"
#include <string>
#include <vector>
// std::pair
#include <utility>
using namespace std;
//contructor
game::game(unsigned players):players(players){
        user.name = "player 1";
         list = new player[players-1];
         int playernum = 1;
         for(int i = 0; i < players -1; i++){
            list[i].name = "CPU"+to_string(playernum); 
            playernum++;
         }
        //assign();
}
//destructor
//game::~game(){

//}
player& game::getUser(){
    return user;
}
player* game::getPlayerlist(){
    return list;
}
cards game::getDeck(){
    return gameDeck;
}
pair<int*,int> game::getCardlist(player p){
    pair<int*, int> newPair;
    int* plist;

    if(flop1 == -1){
        newPair.second = 2;
        plist = new int[2];
         plist[0]=user.getCard1();
         plist[1]=user.getCard2();
         newPair.first=plist;
    }
    else if(turn1 == -1){
        newPair.second = 5;
        plist = new int[5];
         plist[0]=user.getCard1();
         plist[1]=user.getCard2();
         plist[2]=flop1;plist[3]=flop2;plist[4]=flop3;
         newPair.first=plist;
    }
    else if(river1 == -1){
        newPair.second = 6;
        plist = new int[6];
         plist[0]=user.getCard1();
         plist[1]=user.getCard2();
         plist[2]=flop1;plist[3]=flop2;plist[4]=flop3;
         plist[5]=turn1;
         newPair.first=plist;
    }
    else{
        newPair.first=plist;
        newPair.second = 7;
        plist = new int[7];
         plist[0]=user.getCard1();
         plist[1]=user.getCard2();
         plist[2]=flop1;plist[3]=flop2;plist[4]=flop3;
         plist[5]=turn1;
         plist[6]=river1;
         newPair.first=plist;
    }
    return newPair;
}
void game::assign(){
    gameDeck.shuffle();
    user.setCard1(gameDeck.getCard());
    user.setCard2(gameDeck.getCard());

        for(int i = 0; i < (players-1); i++){
        list[i].setCard1(gameDeck.getCard());
        list[i].setCard2(gameDeck.getCard());
        }
        //flop();
}
void game::flop(){

    flop1 = gameDeck.getCard();
    flop2 = gameDeck.getCard();
    flop3 = gameDeck.getCard();
   // turn();
}
void game::turn(){
       turn1 = gameDeck.getCard();
      // river();
}
void game::river(){
      river1 = gameDeck.getCard();
      // gameDeck.printCard(flop1);
     //  gameDeck.printCard(flop2);
     //  gameDeck.printCard(flop3);
     //  gameDeck.printCard(river1);
      // gameDeck.printCard(turn1);
        pair<int*,int> userPair = getCardlist(user);
       
       //user.bestHand = bestHand(userPair.first,userPair.second,user);
       //cout << user.handName << endl;
      // cout << user.handVal << endl;

}
void game::gameMenu(){
 
}

//returns a vector of valued cards that is the best hand based on the pool of the list of cards
vector<int> game::bestHand(int* cards, int length,player &p){

//holds the cards values
int val[length];
//vectors so hold and manipulate card values and patterns
vector<int> hand;
vector<int> handT;
// hold int value A=1 J=11 Q=12 K=13
for(unsigned i = 0; i < length; i++){
      val[i]=gameDeck.getCardVal(cards[i]);
}
for(int i = 0; i < length; i++){
    for(int j = i; j < length;j++){
        if(val[j] < val[i]){
            //switches value list
            int temp = val[i];
            val[i]=val[j];
            val[j]=temp;
            //switches cards list that was passed as parameter
             temp = cards[i];
            cards[i] = cards[j];
            cards[j] = temp;

        }
    }
}
//-----BOTH LIST ARE NOW ORGANIZED FROM LEAST TO GREATEST CARD ORDER-----//

//counter for the number of each suit
int clubs=0;
int hearts=0;;
int spades=0;
int diamonds=0;
//since there can be 7 cards to choose from its possible the hand has 3 pairs or 2 threes
int pairs[6] = {-1,-1,-1,-1,-1,-1};
short pairCount = 0;
int threes[6] = {-1,-1,-1,-1,-1,-1};
short threeCount = 0;
int fours[4] = {-1,-1,-1,-1};
bool holdFour = false;

//temp values that change and reset every loop
bool pair = false;
bool three = false;
bool four = false;
bool twoPair = false;
bool fullhouse = false;


int prev = -1;

bool straight = false;
int straightCount = 0;
int straightList[7]={-1,-1,-1,-1,-1,-1,-1};
int straightDuplicates[2]={-1,-1};
int duplicateCount = 0;

for(int i = 0; i < length; i++){
   // deals with card suits
    if(gameDeck.deck[cards[i]][0]=="C"){
        clubs++;
    }
    else if(gameDeck.deck[cards[i]][0]=="H"){
        hearts++;
    }
    else if(gameDeck.deck[cards[i]][0]=="D"){
        diamonds++;
    }
    else{
        spades++;
    }
//---------------deals with card values-------------------//

//----repeating card values-----//
        //-------Checks for 4s-------//
    if(val[i]==prev && three == true){
        four = true;
        three = false;
        handT.push_back(cards[i]);
       // cout<<"found four"<<" ";
    }
    //-------Checks for 3s-------//
    else if(val[i]==prev && pair == true){
        three = true;
        pair = false;
        handT.push_back(cards[i]);
      //  cout<<"found three"<<" ";
        
    }
    //-----------Checks for pairs------//
    else if(val[i]==prev){
        handT.push_back(cards[i-1]);
        handT.push_back(cards[i]);
       // cout<<"found pair"<<" ";
        pair = true;
    }

    if(val[i] != prev || i==length-1){
    if(four == true){
        fours[0]=handT.at(0);
        fours[1]=handT.at(1);
        fours[2]=handT.at(2);
        fours[3]=handT.at(3);
        four = false;
        holdFour = true;
    }
    else if(three == true){
        //checks if a three of a kind has been previously entered
        if(threes[0] == -1){
            threes[0]=handT.at(0);
            threes[1]=handT.at(1);
            threes[2]=handT.at(2);
        }
        else{
            threes[3]=handT.at(0);
            threes[4]=handT.at(1);
            threes[5]=handT.at(2);
        }
        three = false;
        threeCount++;
    }
    else if(pair == true){
        //checks if first 2 slots are empty
        if(pairs[0]==-1){
            pairs[0]= handT.at(0);
            pairs[1]= handT.at(1);
        }
        //checks if 2nd 2 slots are empty
        else if(pairs[2]==-1){
            pairs[2]= handT.at(0);
            pairs[3]= handT.at(1);
        }
        //puts it in the last 2 slots
        else{
            pairs[4]= handT.at(0);
            pairs[5]= handT.at(1);
        } 
        pair = false;
        pairCount++;
    }
    handT.clear();
    }
//-------deal with sequence---------//
//if you find an increment of 1 in sorted list start straight calculations
if(val[i]==prev+1){
    if(straightCount==0){
        straightList[straightCount]=cards[i-1];
        straightCount+=1;
    }
    straightList[straightCount]=cards[i];
    straightCount+=1;
}
//if there is a dup we still must account for straight possibility
else if(val[i]==prev && duplicateCount < 2){
    //do nothing
    if(straightDuplicates[0] == -1){
        straightDuplicates[0] = cards[i];
    }
    else{
        straightDuplicates[1] = cards[i];
    }
    duplicateCount++;
}
//if neither of 2 is true we must cancel current straight and reset all variables
else if(val[i]!=prev){
    straightList[0]=-1; straightList[1]=-1; straightList[2]=-1; straightList[3]=-1; straightList[4]=-1; straightList[5]=-1; straightList[6]=-1; 
    straightCount = 0;
    straightDuplicates[0] = -1;
     straightDuplicates[1] = -1;
     duplicateCount = 0;
}
//------------USE VECTOR hand SO IT DOESNT INTERFERE WITH THE SAME VALUE CHECKS----------//
// checks if a straight ever is completed
if(straightCount == 5){
    straight = true;
    for(int i = 4; i >= 0; i--){
        hand.push_back(straightList[i]);
    }
    for(int i = 0; i < duplicateCount; i++){
        hand.push_back(straightDuplicates[i]);
        straightDuplicates[i] = -1;
    }
}
//if a straight continues past 5 cards
if(straightCount>5){
    hand.insert(hand.begin(),straightList[straightCount-1]);
    if(straightDuplicates[0] != -1){
        hand.insert(hand.begin(),straightDuplicates[0]);
    }
        if(straightDuplicates[1] != -1){
        hand.insert(hand.begin(),straightDuplicates[1]);
    }
}
//checks for the 1 exception of the straight finishing as an ace since the loop stops at the highest numerical value assigned(k==13)
if(straightCount >= 4 && gameDeck.deck[straightList[straightCount-1]][1]=="K"){
    if(val[0]==1){
        //make sure if there are multiple aces at the beginning we get the right suit
        if(gameDeck.deck[straightList[straightCount-1]][0] == gameDeck.deck[cards[1]][0] && val[1] == 1){
            straightList[straightCount]=cards[1];
        }
        else if(gameDeck.deck[straightList[straightCount-1]][0] == gameDeck.deck[cards[2]][0] && val[2] == 1){
            straightList[straightCount]=cards[2];
        }
        else{
            straightList[straightCount]=cards[0];
        }
        if(straight == false){
        straight = true;
        for(int i = straightCount; i > straightCount-5 ; i--){
            hand.push_back(straightList[i]);
            }
        }
        else{
            hand.insert(hand.begin(),straightList[straightCount]);
        }

    }
}
    prev = val[i];



}
for(int i = 0; i < length; i++){
    cout << val[i]<<" ";
}
cout << endl;

//--------------FLUSH---------------------//
//--------VECTOR handT will hold flush cards---------//
bool flush = false;
if(diamonds>=5 || clubs>=5 || hearts>=5 || spades>=5){
flush = true;
if(diamonds>=5){
for(int i = length-1; i >= 0; i--){
    if(gameDeck.deck[cards[i]][0]=="D"){
        handT.push_back(cards[i]);
    }
}
}
else if(clubs>=5){
for(int i = length-1; i >= 0; i--){
    if(gameDeck.deck[cards[i]][0]=="C"){
        handT.push_back(cards[i]);
    }
}
}
else if(hearts>=5){
for(int i = length-1; i >= 0; i--){
    if(gameDeck.deck[cards[i]][0]=="H"){
        handT.push_back(cards[i]);
    }
}
}
else{
    for(int i = length-1; i >= 0; i--){
    if(gameDeck.deck[cards[i]][0]=="S"){
        handT.push_back(cards[i]);
    }
}
}
//-----------------FLUSH END-------------------------------//
}

//DETERMINE BEST HAND HERE AFTER DETERMINING PAIRS STRAIGHT FLUSHES ETC....
//
//handT has flush and hand has straight
//
//check for straight and royal flush
if(straight == true && flush == true){
    //handles royale and straight flush
vector<int> handF = straightFlush(gameDeck.getSuit(handT.at(0)),hand,p);
if(handF.size() != 0){
return handF;
}
}

//four of a kind
if(holdFour==true){
hand.clear();
hand.push_back(fours[0]);
hand.push_back(fours[1]);
hand.push_back(fours[2]);
hand.push_back(fours[3]);
p.handName = "Four of a Kind";
p.handVal = 8;
return hand;
}
//full house
if(threeCount==1 && pairCount>=1 ||  threeCount>1){
    p.handName = "Full House";
    p.handVal = 7;
    hand.clear();
    if(threeCount>1){
        hand.push_back(threes[3]);
        hand.push_back(threes[4]);
        hand.push_back(threes[5]);
        hand.push_back(threes[1]);
        hand.push_back(threes[2]);
        return hand;
        }
    else{
    hand.push_back(threes[0]);
    hand.push_back(threes[1]);
    hand.push_back(threes[2]);
    if(pairCount==2){
    hand.push_back(pairs[2]);
    hand.push_back(pairs[3]);
    return hand;
    }
    else{
        hand.push_back(pairs[0]);
        hand.push_back(pairs[1]);
        }
    }
    return hand;
}

//flush
if(flush == true){
    p.handName = "Flush";
    p.handVal = 6;
while(handT.size()!=5 || gameDeck.deck[handT.back()][1]=="A"){
    if(gameDeck.deck[handT.back()][1]=="A"){
        handT.insert(handT.begin(),handT.at(handT.size()-1));
    }
    handT.pop_back();
}
return handT;
}
//straight
if(straight == true){
    p.handName = "Straight";
    p.handVal = 5;
while(hand.size()!=5){
    hand.pop_back();
}
return hand;
}
//three of a kind
if(threeCount==1){
    p.handName = "Three of a Kind";
    p.handVal = 4;
hand.clear();
hand.push_back(threes[0]);
hand.push_back(threes[1]);
hand.push_back(threes[2]);
return hand;
}
//two pair
if(pairCount>=2){
    p.handName = "Two Pair";
    p.handVal = 3;
hand.clear();
hand.push_back(pairs[(pairCount*2)-1]);
hand.push_back(pairs[(pairCount*2)-2]);
hand.push_back(pairs[(pairCount*2)-3]);
hand.push_back(pairs[(pairCount*2)-4]);
return hand;
}
//pair
if(pairCount==1){
    p.handName = "Pair";
    p.handVal = 2;
hand.push_back(pairs[1]);
hand.push_back(pairs[0]);
return hand;
}

//high card
//returns the single highest card value in deck

if(val[0] == 1){
    hand.clear();
    hand.push_back(cards[0]);
}
else{
    hand.clear();
    hand.push_back(cards[length - 1]);
}
p.handName = "High Card " + gameDeck.getValue(hand.at(0));
p.handVal = 1;
return hand;
}

//Private Helper
//given a flush and straight is true check if there is a straight that is also a flush or a royal flush
vector<int> game::straightFlush(string flushVal, vector<int> straightCards, player &P){
    //given if there is a flush and a straight run this program to check if there is a straight flush or royal flush
    //will hold the cards if there is 5 and will clear if not
    //return either a 5 card hand or an empty list
    vector<int> SF_hand;
    int suitCount = 0;
    for(int i = 0; i < straightCards.size(); i++){
        if(gameDeck.getSuit(straightCards.at(i)) == flushVal){
            suitCount++;
            SF_hand.push_back(straightCards.at(i));
        }
        else if(gameDeck.getSuit(straightCards.at(i)) != flushVal){
            suitCount = 0;
            SF_hand.clear();
        }
        //copy over if 5 is found
        if(suitCount == 5){
            //royale flush
            if(gameDeck.getValue(SF_hand.at(0)) == "A" && gameDeck.getValue(SF_hand.at(4)) == "10"){
                P.handName = "Royale Flush";
                P.handVal = 10;
            }
            else{
                P.handName = "Straight Flush";
                P.handVal = 9;
            }
            return SF_hand;
        }
    }
    SF_hand.clear();
    return SF_hand;
}

//get winner/winners
vector<player*> game::winner(player* user, player* list){
    //use vector since there can be multiple winners
    //if vector is empty it means its a draw
    vector<player*> winners;
    winners.push_back(user);
    player* highest = winners.front();
    //determine who has the best hand
    for(int i = 0; i < players - 1; i++){
        // if one is higher make him the only winner
        if(list[i].handVal > highest->handVal){
            winners.clear();
            highest = &list[i];
            winners.push_back(highest);
        }
        else if(list[i].handVal == highest->handVal){
            int highestCard, otherCard;
            switch (highest->handVal)
            {
                //ROYAL FLUSH
            case 10:
                //if 2 ppl have royal flush it means it is the 5 cards on the board
                //ITS A DRAW FOR ALL PLAYERS
                winners.clear();
                winners.push_back(user);
                for(int i = 0; i < players-1; i++){
                    winners.push_back(&list[i]);
                }
                return winners;
                //STRAIGHT FLUSH
            case 9:
            // if 2 people have straight flushes determine who has the higher straight
             //compare top card
             //top card of highest
              highestCard = highest->getHand().front();
             //top card of list[i]
              otherCard = list[i].getHand().front();
             // if the current player has a better hand that current highest
            if(gameDeck.getCardVal(otherCard) > gameDeck.getCardVal(highestCard) && gameDeck.getCardVal(highestCard) != 1){
                winners.clear();
                winners.push_back(&list[i]);
                highest = winners.front();
            }
            // checking for ace special case since Ace can also be greater than king
            else if(gameDeck.getCardVal(otherCard) == 1 && gameDeck.getCardVal(highestCard) != 1){
                winners.clear();
                winners.push_back(&list[i]); 
                highest = winners.front();               
            }
            // if they both are straight flushes
            else if(gameDeck.getCardVal(otherCard) == gameDeck.getCardVal(highestCard)){
                winners.push_back(&list[i]); 
            }
                break;
                //FOUR OF A KIND
            case 8:
            //top card of highest
              highestCard = highest->getHand().front();
             //top card of list[i]
              otherCard = list[i].getHand().front();
            if(gameDeck.getCardVal(otherCard) > gameDeck.getCardVal(highestCard) && gameDeck.getCardVal(highestCard) != 1){
                winners.clear();
                winners.push_back(&list[i]);
                highest = winners.front();
            }
            else if(gameDeck.getCardVal(otherCard) == 1 && gameDeck.getCardVal(highestCard) !=1){
                winners.clear();
                winners.push_back(&list[i]);
                highest = winners.front();
            }
                break;
                //FULL HOUSE
                //compare trips if they are same check the pair
            case 7:
             //top card of highest
              highestCard = highest->getHand().front();
             //top card of list[i]
              otherCard = list[i].getHand().front();
              if(gameDeck.getCardVal(otherCard) > gameDeck.getCardVal(highestCard) && gameDeck.getCardVal(highestCard) != 1){
                winners.clear();
                winners.push_back(&list[i]);
                highest = winners.front();
            }
            else if(gameDeck.getCardVal(otherCard) == 1 && gameDeck.getCardVal(highestCard) != 1){
                winners.clear();
                winners.push_back(&list[i]);
                highest = winners.front();
            }
            else if(gameDeck.getCardVal(otherCard) == gameDeck.getCardVal(highestCard)){
                //pair card of highest
             int highestPCard = highest->getHand().at(3);
             //pair card of list[i]
             int otherPCard = list[i].getHand().at(3);
             if(gameDeck.getCardVal(otherPCard) > gameDeck.getCardVal(highestPCard) && gameDeck.getCardVal(highestPCard) != 1){
                winners.clear();
                winners.push_back(&list[i]);
                highest = winners.front();
             }
             else if(gameDeck.getCardVal(otherPCard) == 1 &&gameDeck.getCardVal(highestPCard) !=1){
                winners.clear();
                winners.push_back(&list[i]);
                highest = winners.front();
             }
             else if(gameDeck.getCardVal(otherPCard) == gameDeck.getCardVal(highestPCard)){
                 winners.push_back(&list[i]);
             }
            }
                break;
                //FLUSH
                //flushes are all == (for now)
            case 6:
                winners.push_back(&list[i]);
                break;
                //STRAIGHT
            case 5:
             //compare top card
             //top card of highest
              highestCard = highest->getHand().front();
             //top card of list[i]
              otherCard = list[i].getHand().front();
             // if the current player has a better hand that current highest
            if(gameDeck.getCardVal(otherCard) > gameDeck.getCardVal(highestCard) && gameDeck.getCardVal(highestCard) != 1){
                winners.clear();
                winners.push_back(&list[i]);
                highest = winners.front();
            }
            // checking for ace special case since Ace can also be greater than king
            else if(gameDeck.getCardVal(otherCard) == 1 && gameDeck.getCardVal(highestCard) != 1){
                winners.clear();
                winners.push_back(&list[i]); 
                highest = winners.front();               
            }
            // if they both are straight flushes
            else if(gameDeck.getCardVal(otherCard) == gameDeck.getCardVal(highestCard)){
                winners.push_back(&list[i]); 
            }
                break;
                //THREE OF A KIND
            case 4:
            //top card of highest
              highestCard = highest->getHand().front();
             //top card of list[i]
              otherCard = list[i].getHand().front();
             if(gameDeck.getCardVal(otherCard) > gameDeck.getCardVal(highestCard) && gameDeck.getCardVal(highestCard) !=1){
                winners.clear();
                winners.push_back(&list[i]);
                highest = winners.front();
             }
             else if(gameDeck.getCardVal(otherCard) == 1 &&gameDeck.getCardVal(highestCard) != 1){
                winners.clear();
                winners.push_back(&list[i]);
                highest = winners.front();     
             }
             else if(gameDeck.getCardVal(otherCard) == gameDeck.getCardVal(highestCard)){
                winners.push_back(&list[i]);
             }
                break;
                //TWO PAIR
             case 3:
            //top card of highest
              highestCard = highest->getHand().front();
             //top card of list[i]
              otherCard = list[i].getHand().front();
             if(gameDeck.getCardVal(otherCard) > gameDeck.getCardVal(highestCard) && gameDeck.getCardVal(highestCard) !=1){
                winners.clear();
                winners.push_back(&list[i]);
                highest = winners.front();
             }
             else if(gameDeck.getCardVal(otherCard) == 1 && gameDeck.getCardVal(highestCard) !=1){
                winners.clear();
                winners.push_back(&list[i]);
                highest = winners.front();
             }
             else if(gameDeck.getCardVal(otherCard) == gameDeck.getCardVal(highestCard)){
                //2nd pair card of highest
             int highestPCard = highest->getHand().at(2);
             //2nd pair card of list[i]
             int otherPCard = list[i].getHand().at(2);
             if(gameDeck.getCardVal(otherPCard) > gameDeck.getCardVal(highestPCard) && gameDeck.getCardVal(highestPCard) !=1){
                winners.clear();
                winners.push_back(&list[i]);
                highest = winners.front();
             }
             else if(gameDeck.getCardVal(otherPCard) == 1 && gameDeck.getCardVal(highestPCard) !=1){
                winners.clear();
                winners.push_back(&list[i]);
                highest = winners.front();
             }
             else if(gameDeck.getCardVal(otherPCard) == gameDeck.getCardVal(highestPCard)){
                winners.push_back(&list[i]);
             }
             }
                break;
                //PAIR
            case 2:
             //top card of highest
              highestCard = highest->getHand().front();
             //top card of list[i]
              otherCard = list[i].getHand().front();
             if(gameDeck.getCardVal(otherCard) > gameDeck.getCardVal(highestCard)){
                winners.clear();
                winners.push_back(&list[i]);
                highest = winners.front();
             }
             else if(gameDeck.getCardVal(otherCard) == gameDeck.getCardVal(highestCard)){
                winners.push_back(&list[i]);
             }
                break;
                //HIGH CARD
             case 1:
            //top card of highest
              highestCard = highest->getHand().front();
            //top card of list[i]
              otherCard = list[i].getHand().front();
             //check if list[i] high is > than current highest
             if(gameDeck.getCardVal(otherCard) > gameDeck.getCardVal(highestCard) && gameDeck.getCardVal(highestCard) != 1){
                winners.clear();
                winners.push_back(&list[i]);
                highest = winners.front();
            }
            // checking for ace special case since Ace can also be greater than king
            else if(gameDeck.getCardVal(otherCard) == 1 && gameDeck.getCardVal(highestCard) != 1){
                winners.clear();
                winners.push_back(&list[i]); 
                highest = winners.front();               
            }
            // if they both have same high card
            else if(gameDeck.getCardVal(otherCard) == gameDeck.getCardVal(highestCard)){
                winners.push_back(&list[i]); 
            }
            break;               
            default:
            //empty
                break;
            }
        }
    }
    return winners;
}
