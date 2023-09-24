#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "poker-project/game.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_enterButton_clicked();

    void on_createButton_clicked();

    void on_startButton_clicked();

    void on_foldButton_clicked();

    void on_playButton_clicked();


    void on_winnerButton_clicked();

    void on_joinButton_clicked();

    void on_dealButton_clicked();

    void on_riverButton_clicked();

    void on_turnButton_clicked();

private:
    Ui::MainWindow *ui;
    game* newGame;
    QString userName;
    unsigned money;
    void playerInfo();

};
#endif // MAINWINDOW_H
