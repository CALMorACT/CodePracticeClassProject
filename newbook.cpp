#include "newbook.h"
#include "ui_newbook.h"
#include<QString>
#include<QMessageBox>
#include<QtDebug>
#include<QFile>
#include<QTextStream>
#include<QIODevice>
newBook::newBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newBook)
{
    ui->setupUi(this);
}

newBook::~newBook()
{
    delete ui;
}

void newBook::on_ok_bu_clicked()
{
    QString name=this->ui->name->text();
    QString writer=this->ui->writer->text();
    QString id=this->ui->id->text();
    QString num=this->ui->num->text();

    QString content=name+"\n"+writer+"\n"+id+"\n"+num;
    QString cnt=name+" "+writer+" "+id+" "+num+" "+num+"\n";
    if(name.length()<1||num.length()<1){
        QMessageBox::critical(this,"wrong","your input doesn't match","ok");
    }
    else{
    int ret=QMessageBox::question(this,"pleas confirm",content,"yes","no");
    if(ret==0){
        clearUserFace();
        writeToFile(cnt);
    }
    }

}
void newBook::clearUserFace(){
    this->ui->name->setText("");
    this->ui->writer->setText("");
    this->ui->id->setText("");
    this->ui->num->setText("");
}
void newBook::writeToFile(QString cnt){
    QFile file("book.txt");
    if(!file.open(QIODevice::Append| QIODevice::Text)){
        QMessageBox::critical(this,"wrong","unable to open file!","ok");//打开失败反馈给用户
        return;
    }
    QTextStream out(&file);
    out<<cnt;
    file.close();
}

void newBook::on_no_bu_clicked()
{
    this->close();
}
