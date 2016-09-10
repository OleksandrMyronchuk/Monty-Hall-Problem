#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QQueue>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void generate();
    short things[3];//0 - car 1, 2 = goat
    QQueue<int> randList[3];

public slots:

    void on_pushButtonClear_clicked();

private slots:
    void on_pushButtonStartGame_clicked();

    void on_pushButtonDoor1_clicked();

    void on_pushButtonDoor2_clicked();

    void on_pushButtonDoor3_clicked();

    void on_pushButtonItDeception_clicked();

    void on_pushButtonAbout_clicked();

    void on_pushButtonExit_clicked();

    void lowerColor();

private:
    void userChoice();
    void action1();
    void action2();
    Ui::MainWindow *ui;
    QPushButton *PBdoors[3];
    QLabel *Ldoors[3];
    QTimer *timer;

    short color;
    short car;
    short openDoor;
    short lastDoor;
    short win;
    short loss;
    short total;
};

#endif // MAINWINDOW_H
