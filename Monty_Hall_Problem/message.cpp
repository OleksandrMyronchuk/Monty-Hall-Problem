#include "message.h"
#include "ui_message.h"

message::message(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::message)
{
    init();
}

message::message(QString mes, QString title) :
    ui(new Ui::message)
{
    init();
    this->setWindowTitle(title);
    ui->label->setText(mes);
}

message::~message()
{
    delete ui;
}

void message::on_pushButton_clicked()
{
    this->close();
}

void message::init()
{
    ui->setupUi(this);
    this->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
    this->setWindowModality(Qt::WindowModality::ApplicationModal);
}
