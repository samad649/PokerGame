#include <iostream>
#include "game.h"
using namespace std;

int main(){

    cout<<"Welcome to the table"<<endl;
    cout<<"How many players would you like in the game"<<endl;
    bool start = false;
    unsigned players = 0;

        cout<<"Please enter a number (2-10) - ";
        cin>>players;

    while(!start){
        if(players >= 2 && players <= 10){
            start = true;
            cout<<endl<<"Starting "<< players <<" player game....."<<endl;
            }
        else{
            if(cin.fail()){
                cin.clear();
                 cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            cout<<endl<<"invalid number given please re-enter number (2-10) - ";
            cin>>players;
            }
    }
        //=====AFTER INPUT HAS BEEN TAKEN=====//
        game newGame(players);
        //---Game Start & assign cards to all players--//
        newGame.assign();
        cout << "Card 1:";
        newGame.getDeck().printCard(newGame.getUser().getCard1());
        cout << "Card 2:";
        newGame.getDeck().printCard(newGame.getUser().getCard2());
        //decide to either play or fold
        cout << "This is the Flop" << endl;
        newGame.flop();
        newGame.getDeck().printCard(newGame.flop1);
        newGame.getDeck().printCard(newGame.flop2);
        newGame.getDeck().printCard(newGame.flop3);
        //decide to continue or fold
        cout << "This is the Turn" << endl;
        newGame.turn();
        newGame.getDeck().printCard(newGame.turn1);
        cout << "This is the River" << endl;
        newGame.river();
        newGame.getDeck().printCard(newGame.river1);
        return 1;
}