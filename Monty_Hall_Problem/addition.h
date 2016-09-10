#ifndef ADDITION_H
#define ADDITION_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class addition;
}

class addition : public QDialog
{
    Q_OBJECT

public:
    explicit addition(MainWindow *parent_);
    ~addition();

private slots:
    void on_pushButton_clicked();

private:
    Ui::addition *ui;
    MainWindow *parent;
};

#endif // ADDITION_H
