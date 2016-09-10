#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "message.h"
#include "addition.h"
#include <QIcon>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), timer(new QTimer),
    ui(new Ui::MainWindow), win(0), loss(0), total(0)
{
    ui->setupUi(this);

    message *win = new message;
    win->show();

    this->PBdoors[0] = ui->pushButtonDoor1;
    this->PBdoors[1] = ui->pushButtonDoor2;
    this->PBdoors[2] = ui->pushButtonDoor3;

    this->Ldoors[0] = ui->labelDoor1;
    this->Ldoors[1] = ui->labelDoor2;
    this->Ldoors[2] = ui->labelDoor3;

    connect(timer, SIGNAL(timeout()), this, SLOT(lowerColor()));
    timer->setInterval(10);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::on_pushButtonStartGame_clicked()
{    
    ui->pushButtonStartGame->setEnabled(false);
    //random
    // 1 - is car
    // 2, 3 - is goat

    if( randList[0].isEmpty() )
    {
        generate();
    }
    else
    {
        for(int i = 0; i < 3; i++)
            things[i] = randList[i].dequeue();
    }

    for(int i = 0; i < 3; i++)
    {
        //clear
        PBdoors[i]->setEnabled(true);
        this->PBdoors[i]->setIcon(QIcon(":/dir/door.jpg"));
        this->PBdoors[i]->setStyleSheet("QPushButton{background-color: white;}");
        this->Ldoors[i]->setStyleSheet("QLabel{background-color: white;}");
        if(things[i] == 0)
            car = i;
    }

    ui->labelExplanation->setText("Відгадаєте за якіми дверима є автомобіль. (натисніть на двері)");

}

void MainWindow::on_pushButtonDoor1_clicked()
{
    openDoor = 0;
    userChoice();
}

void MainWindow::on_pushButtonDoor2_clicked()
{
    openDoor = 1;
    userChoice();
}

void MainWindow::on_pushButtonDoor3_clicked()
{
    openDoor = 2;
    userChoice();
}

void MainWindow::userChoice()
{
    static bool ind = true;    

    color = 255;
    ui->labelExplanation->setStyleSheet("QLabel{color: rgb(255, 0, 0);}");
    timer->start();

    if(ind)
    {
        action1();
        ind = false;
    }
    else
    {
        action2();
        ind = true;
    }
}

void MainWindow::action1()
{
    this->PBdoors[openDoor]->setStyleSheet("QPushButton{background-color: yellow;}");
    this->Ldoors[openDoor]->setStyleSheet("QLabel{background-color: yellow;}");
    ui->labelExplanation->setText("Я вам допоміг, відкривши одні двері з козою. У вас є шанс змінити свій вибір,"
                                  " що ви зробите ? (натисніть на двері)");

    //random
    // 1 - is car
    // 2, 3 - is goat

    short num;

    if(this->car == openDoor)
    {
        num = rand() % 2;
        if( num == this->car)
            if(++num == 2)
                num = 0;
    }
    else if(this->car != openDoor)
    {
        for(int i = 0; i < 3; i++)
        {
            if(i != this->car && i != openDoor)
            {
                num = i;
                break;
            }
        }
    }

    PBdoors[num]->setEnabled(false);
    PBdoors[num]->setIcon(QIcon(":/dir/goat.jpg"));
    lastDoor = openDoor;
}

void MainWindow::action2()
{
    if(lastDoor != openDoor)
    {
        this->PBdoors[lastDoor]->setStyleSheet("QPushButton{background-color: white;}");
        this->Ldoors[lastDoor]->setStyleSheet("QLabel{background-color: white;}");

        this->PBdoors[openDoor]->setStyleSheet("QPushButton{background-color: yellow;}");
        this->Ldoors[openDoor]->setStyleSheet("QLabel{background-color: yellow;}");
    }

    PBdoors[openDoor]->setEnabled(false);

    if(openDoor == this->car)
    {
        PBdoors[openDoor]->setIcon(QIcon(":/dir/car.jpg"));
        message *win = new message("Вітаю! Ви виграли автомобіль", "Вітаю!");
        win->show();
        ui->labelWin->setText(
                    "<span style=\" color:#00ff7f;\">Перемог: </span>" +
                    QString::number(++this->win)
                    );
    }
    else
    {
        PBdoors[openDoor]->setIcon(QIcon(":/dir/goat.jpg"));
        message *win = new message("Програш! Ви виграли козу", "Програш!");
        win->show();
        ui->labelLoss->setText(
                    "<span style=\" color:#c60000;\">Програшів: </span>" +
                    QString::number(++this->loss)
                    );
    }

    ui->labelTotal->setText(
                "Номер гри: " +
                QString::number(++this->total)
                );

    for(int i = 0; i < 3; i++)
    {
        if(i == this->car)
            PBdoors[i]->setIcon(QIcon(":/dir/car.jpg"));
        else
            PBdoors[i]->setIcon(QIcon(":/dir/goat.jpg"));
    }

    ui->labelExplanation->setText("Для того щоб розпочати гру натисніть \"Розпочати гру\"");
    ui->pushButtonStartGame->setEnabled(true);
}

void MainWindow::generate()
{
    short numRand = rand() % 3 + 1;
    short num = numRand;

    things[2] = num - 1;

    numRand = rand() % 2 + 1;

    if(++num == 4) num = 1;
    things[numRand - 1] = num - 1;

    numRand == 1 ? ++numRand : --numRand;

    if(++num == 4) num = 1;
    things[numRand - 1] = num - 1;
}

void MainWindow::on_pushButtonClear_clicked()
{
    win = 0, loss = 0, total = 0;
    ui->labelWin->setText(
                "<span style=\" color:#00ff7f;\">Перемог: </span>" +
                QString::number(this->win)
                );

    ui->labelLoss->setText(
                "<span style=\" color:#c60000;\">Програшів: </span>" +
                QString::number(this->loss)
                );

    ui->labelTotal->setText(
                "<span style=\" color:#c60000;\">Номер гри: </span>" +
                QString::number(this->total)
                );
}

void MainWindow::on_pushButtonItDeception_clicked()
{
    addition *win = new addition(this);
    win->show();
}

void MainWindow::on_pushButtonAbout_clicked()
{
    message *win = new message("Автор: Мирончук Олександр\nTwitter: https://twitter.com/MyronchukOleks\nEmail: hy677ba@yandex.ua\nreplace.org.ua: Betterthanyou\n\nЦе відкрите програмне забезпечення", "Про програму");
    win->show();
}

void MainWindow::on_pushButtonExit_clicked()
{
    this->close();
}

void MainWindow::lowerColor()
{
    if( --color <= 0 )
    {
        color = 0;
        timer->stop();
    }
    ui->labelExplanation->setStyleSheet("QLabel{color: rgb(" + QString::number(color) + ", 0, 0);}");
}
