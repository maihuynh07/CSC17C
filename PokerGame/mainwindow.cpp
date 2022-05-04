#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Poker.h"
#include <QPixmap>
#include <QWidgetItem>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1600,1200);
    // image with correctly scale
    QString stylesheet = "image-position:left center;";
    ui->image1_1->setStyleSheet(stylesheet);
    ui->image1_2->setStyleSheet(stylesheet);
    ui->image1_3->setStyleSheet(stylesheet);
    ui->image1_4->setStyleSheet(stylesheet);
    ui->image1_5->setStyleSheet(stylesheet);

    game = new Poker();

    ui->btnStart->setEnabled(true);
    ui->btnDiscard_player->setEnabled(false);
    ui->btnSkip->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}


void MainWindow::on_btnStart_clicked()
{
    game->initializeGame();
    game->update(static_cast<short>(GAME_STATE::START));

    ui->btnStart->setEnabled(false);
    ui->btnDiscard_player->setEnabled(true);
    ui->btnSkip->setEnabled(true);

    render(0);
}


void MainWindow::on_btnDiscard_player_clicked()
{
    bool checked = ui->groupBox_1->isChecked();
    int position = -1;
    if(checked){
        position = ui->groupBox_1->toolTip().toInt();
        game->setDiscardedPoss(position);
        isDraw = true;
    }

    checked = ui->groupBox_2->isChecked();
    if(checked){
        position = ui->groupBox_2->toolTip().toInt();
        game->setDiscardedPoss(position);
        isDraw = true;
    }

    checked = ui->groupBox_3->isChecked();
    if(checked){
        position = ui->groupBox_3->toolTip().toInt();
        game->setDiscardedPoss(position);
        isDraw = true;
    }

    checked = ui->groupBox_4->isChecked();
    if(checked){
        position = ui->groupBox_4->toolTip().toInt();
        game->setDiscardedPoss(position);
        isDraw = true;
    }

    checked = ui->groupBox_5->isChecked();
    if(checked){
        position = ui->groupBox_5->toolTip().toInt();
        game->setDiscardedPoss(position);
        isDraw = true;
    }

    // call update game
    game->update(static_cast<short>(GAME_STATE::DRAW));

    // render game again
    render(2);

    // get result string
    QString result = game->getResult().c_str();
    result += ". Do you want to replay?";
    // display message result
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Result",result,
                                                              QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes){
        game->resetGame();
        resetCard();
    }
    else{
        QApplication::quit();
    }

}
void MainWindow::render(int i){

    // get path of images of 5 cards of players
    deque<string> images = game->getImages(0);

    // draw card1
    string fileName = ":/images/Images/"+images[0];
    QString qfileName = QString::fromStdString(fileName.c_str());
    QPixmap pix1(qfileName);
    ui->image1_1->setPixmap(pix1);

    // draw card2
    fileName = ":/images/Images/"+images[1];
    qfileName = QString::fromStdString(fileName.c_str());
    QPixmap pix2(qfileName);
    ui->image1_2->setPixmap(pix2);

    // draw card3
    fileName = ":/images/Images/"+images[2];
    qfileName = QString::fromStdString(fileName.c_str());
    QPixmap pix3(qfileName);
    ui->image1_3->setPixmap(pix3);

    // draw card4
    fileName = ":/images/Images/"+images[3];
    qfileName = QString::fromStdString(fileName.c_str());
    QPixmap pix4(qfileName);
    ui->image1_4->setPixmap(pix4);

    // draw card5
    fileName = ":/images/Images/"+images[4];
    qfileName = QString::fromStdString(fileName.c_str());
    QPixmap pix5(qfileName);
    ui->image1_5->setPixmap(pix5);

    if(i==1 || i==2){

        // get path of images of 5 cards of dealer
        images = game->getImages(1);

        // draw card1
        string fileName = ":/images/Images/"+images[0];
        QString qfileName = QString::fromStdString(fileName.c_str());
        QPixmap pix1(qfileName);
        ui->image2_1->setPixmap(pix1);

        // draw card2
        fileName = ":/images/Images/"+images[1];
        qfileName = QString::fromStdString(fileName.c_str());
        QPixmap pix2(qfileName);
        ui->image2_2->setPixmap(pix2);

        // draw card3
        fileName = ":/images/Images/"+images[2];
        qfileName = QString::fromStdString(fileName.c_str());
        QPixmap pix3(qfileName);
        ui->image2_3->setPixmap(pix3);

        // draw card4
        fileName = ":/images/Images/"+images[3];
        qfileName = QString::fromStdString(fileName.c_str());
        QPixmap pix4(qfileName);
        ui->image2_4->setPixmap(pix4);

        // draw card5
        fileName = ":/images/Images/"+images[4];
        qfileName = QString::fromStdString(fileName.c_str());
        QPixmap pix5(qfileName);
        ui->image2_5->setPixmap(pix5);
    }

    ui->centralwidget->update();
    // remove images
    images.clear();
}


void MainWindow::on_btnSkip_clicked()
{
    // call update game
    game->update(static_cast<short>(GAME_STATE::SHOW));

    // render game again
    render(2);

    // get result string
    QString result = game->getResult().c_str();
    result += ". Do you want to replay?";

    // display message result
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Result",result,
                                                              QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes){
        game->resetGame();
        resetCard();
    }
    else{
        QApplication::quit();
    }
}
void MainWindow::resetCard(){

    // reset image of card
    string fileName = ":/images/Images/cardBack.png";
    QString qfileName = QString::fromStdString(fileName.c_str());
    QPixmap pix(qfileName);
    ui->image1_1->setPixmap(pix);
    ui->image1_2->setPixmap(pix);
    ui->image1_3->setPixmap(pix);
    ui->image1_4->setPixmap(pix);
    ui->image1_5->setPixmap(pix);

    ui->image2_1->setPixmap(pix);
    ui->image2_2->setPixmap(pix);
    ui->image2_3->setPixmap(pix);
    ui->image2_4->setPixmap(pix);
    ui->image2_5->setPixmap(pix);

    // reset groupbox checked
    ui->groupBox_1->setChecked(true);
    ui->groupBox_2->setChecked(true);
    ui->groupBox_3->setChecked(true);
    ui->groupBox_4->setChecked(true);
    ui->groupBox_5->setChecked(true);

    // reset btn
    ui->btnStart->setEnabled(true);
    ui->btnDiscard_player->setEnabled(false);
    ui->btnSkip->setEnabled(false);
}

