#include "addbook.h"
#include "ui_addbook.h"
#include <QString>
addBook::addBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addBook)
{
    ui->setupUi(this);
}

addBook::~addBook()
{
    delete ui;
}

void addBook::on_pushButton_clicked()
{
    QString title=
}
