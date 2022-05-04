#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Poker.h"
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

    // event click of button start
    void on_btnStart_clicked();

    // event click of button discard
    void on_btnDiscard_player_clicked();


    // render cards
    void render(int = 0);// default render cards of players, 1 = render cards of player, 2 = render dealer+player

    // event to show down round
    void on_btnSkip_clicked();

    // draw card back on player and dealer
    void resetCard();


private:
    Ui::MainWindow *ui;
    Poker *game;
    bool isDraw; // true if user discards some cards, false if no cards is discarded
};
#endif // MAINWINDOW_H
