#ifndef HELLO_H
#define HELLO_H

#include <QDialog>

namespace Ui {
class message;
}

class message : public QDialog
{
    Q_OBJECT

public:
    explicit message(QWidget *parent = 0);
    explicit message(QString mes, QString title);
    ~message();

private slots:
    void on_pushButton_clicked();

private:
    void init();
    Ui::message *ui;
};

#endif // HELLO_H
