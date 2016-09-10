#include "addition.h"
#include "ui_addition.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

addition::addition(MainWindow *parent_) :
    parent(parent_),
    ui(new Ui::addition)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
}

addition::~addition()
{
    delete ui;
}

void addition::on_pushButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(this,"Зберегти файл", "/", "Текстовий файл(*.htm)");

    QFile file(path);

    file.open(QIODevice::WriteOnly);

    QTextStream textStream(&file);

    textStream.setCodec("UTF-8");

    textStream << (QString)"<!doctype html><html><head><title>Тестова сторінка</title><meta charset=\"utf-8\" /></head><body><table width=\"100%\" border=\"2\">";

    for(int i = 0; i < 3; i++)
        parent->randList[i].clear();

    for(int i = 0; i < ui->spinBox->value(); i++)
    {
        parent->generate();
        textStream << "<tr>";
        textStream << "<th>" << i + 1 << "</th>";
        for(int j = 0; j < 3; j++)
        {
            parent->randList[j].enqueue(parent->things[j]);
            textStream << "<th>"
                       << (parent->things[j] == 0 ? (QString)"Автомобіль" : (QString)"Коза")
                       << "</th>";
        }
        textStream << "</tr>";
    }

    textStream << "</table></body></html>";

    file.close();
    this->close();
    parent->on_pushButtonClear_clicked();
}
