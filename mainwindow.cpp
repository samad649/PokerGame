#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>
#include "poker-project/game.h"
#include "poker-project/cards.h"
#include "poker-project/player.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <utility>
#include <vector>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->programStack->setCurrentIndex(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// username was entered button
void MainWindow::on_enterButton_clicked()
{
     userName = ui->userBox->toPlainText();
    if(userName == ""){
        ui->errorMsg->setText("Enter a username");
        ui->userBox->setPlainText("");
    }
    else if(userName.contains(" ")){
         ui->errorMsg->setText("username cant contain spaces");
        ui->userBox->setPlainText("");
    }
    else if(userName.length() > 10){
         ui->errorMsg->setText("username is too long");
         ui->userBox->setPlainText("");
    }
    else{
         ui->greeting->setText("Hello, " + userName);
    ui->programStack->setCurrentIndex(1);
    }

}

//create game Button
void MainWindow::on_createButton_clicked()
{
    ui->programStack->setCurrentIndex(3);
}




void MainWindow::on_startButton_clicked()
{
    unsigned playerNum = ui->playerCount->value();
    money = ui->moneyCount->value();
    ui->programStack->setCurrentIndex(4);
     newGame = new game(playerNum);
    ui->gameStack->setCurrentIndex(0);
     ui->foldButton->hide();
    ui->dealButton->show();
    ui->handDisplay->setText("Hand: N/A");
    ui->moneyDisplay->setText(QString::number(money)+"$");
    ui->usernameDisplay->setText(userName);

}


void MainWindow::on_foldButton_clicked()
{
     delete newGame;
     ui->programStack->setCurrentIndex(3);
     ui->card1->setStyleSheet("");
     ui->card2->setStyleSheet("");
     //clear all widgets in gameControls
     int itemCount = ui->gameControls->count();
     for(int i = 0; i < itemCount; i++){
    ui->gameControls->itemAt(i)->widget()->hide();
     }
     int cardCount = ui->community->count();
     for(int i = 0; i < cardCount; i++){
    ui->community->itemAt(i)->widget()->setStyleSheet("");
     }


}


void MainWindow::on_playButton_clicked()
{
     ui->gameStack->setCurrentIndex(1);
     newGame->flop();
       ui->t1->hide();
       ui->r1->hide();
        ui->f1->setStyleSheet("image:url(images/cards/fronts/"+ QString::number(newGame->flop1) +".svg)");
       ui->f2->setStyleSheet("image:url(images/cards/fronts/"+ QString::number(newGame->flop2) +".svg)");
        ui->f3->setStyleSheet("image:url(images/cards/fronts/"+ QString::number(newGame->flop3) +".svg)");
        ui->playButton->hide();
        ui->gameControls->addWidget(ui->turnButton);
        ui->turnButton->show();
        std::pair<int*, int> currentHand = newGame->getCardlist(newGame->getUser());
        vector<int> vectorHand = newGame->bestHand(currentHand.first,currentHand.second,newGame->getUser());
        ui->handDisplay->setText("Hand: "+QString::fromStdString(newGame->getUser().handName));


}


void MainWindow::on_winnerButton_clicked()
{
     ui->winnerButton->hide();
     ui->winnerLabel->setText(QString::fromStdString(newGame->getUser().handName));
}


void MainWindow::on_joinButton_clicked()
{
    ui->programStack->setCurrentIndex(2);
}

void MainWindow::playerInfo(){

}
void MainWindow::on_dealButton_clicked()
{
    newGame->assign();
    ui->card1->setStyleSheet("image:url(images/cards/fronts/"+ QString::number(newGame->getUser().getCard1()) +".svg)");
    ui->card2->setStyleSheet("image:url(images/cards/fronts/"+ QString::number(newGame->getUser().getCard2()) +".svg)");
    ui->dealButton->hide();
    ui->foldButton->show();
    ui->playButton->show();
    ui->gameControls->addWidget(ui->foldButton);
    ui->gameControls->addWidget(ui->playButton);


}


void MainWindow::on_riverButton_clicked()
{
    newGame->river();
    ui->r1->show();
    ui->r1->setStyleSheet("image:url(images/cards/fronts/"+ QString::number(newGame->river1) +".svg)");
    ui->gameStack->setCurrentIndex(3);
    ui->riverButton->hide();
    std::pair<int*, int> currentHand = newGame->getCardlist(newGame->getUser());
    vector<int> vectorHand = newGame->bestHand(currentHand.first,currentHand.second,newGame->getUser());
    ui->handDisplay->setText("Hand: "+QString::fromStdString(newGame->getUser().handName));
}


void MainWindow::on_turnButton_clicked()
{
    ui->gameStack->setCurrentIndex(2);
    newGame->turn();
    ui->t1->show();
    ui->t1->setStyleSheet("image:url(images/cards/fronts/"+ QString::number(newGame->turn1) +".svg)");
    ui->gameControls->addWidget(ui->riverButton);
    ui->riverButton->show();
    ui->turnButton->hide();
    std::pair<int*, int> currentHand = newGame->getCardlist(newGame->getUser());
    vector<int> vectorHand = newGame->bestHand(currentHand.first,currentHand.second,newGame->getUser());
    ui->handDisplay->setText("Hand: "+QString::fromStdString(newGame->getUser().handName));
}

