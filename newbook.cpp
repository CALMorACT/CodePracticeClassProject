/*
 * @Author: your name
 * @Date: 2020-07-15 16:08:20
 * @LastEditTime: 2020-07-16 11:32:28
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \CodePracticeClassProject\newbook.cpp
 */ 
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
    QString name=this->ui->name->text().trimmed();
    QString writer=this->ui->writer->text().trimmed();
    QString id=this->ui->id->text().trimmed();
    QString num=this->ui->num->text().trimmed();
    int index=2;

    QString content="name "+name+"\n"+"writer "+writer+"\n"+"id "+id+"\n"+"num "+num;
    QString cnt=name+" "+writer+" "+id+" "+num+" "+num+"\n";
    if(name.length()<1||num.length()<1||id.length()<1||num.length()<1){
        QMessageBox::critical(this,"wrong","your input doesn't match","ok");
        index=0;
    }
    else if(checkid(id)){
        QMessageBox::critical(this,"wrong","id already exists,please re-enter!","ok");
        index=0;
    }
    else if(checkblank(name)||checkblank(writer)||checkblank(id)||checkblank(num)){
        QMessageBox::critical(this,"wrong","your input doesn't match!","ok");
            qDebug()<<"here";
        index=0;
    }

    else if(index==2){
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
        //文件打开失败反馈
        QMessageBox::critical(this,"wrong","unable to open file!","ok");
        return;
    }
    QTextStream out(&file);
    out<<cnt;
    file.close();
    QMessageBox::question(this,"congratulation","operation was successful","ok");


}

void newBook::on_no_bu_clicked()
{
    clearUserFace();
    this->close();
}

// 判断是否唯一
int newBook::checkid(QString id){
    bok_lines.clear();
    QFile file("book.txt");
    if(!file.open(QIODevice::ReadOnly| QIODevice::Text)){
        return -1;//打开失败返回-1
    }
    QTextStream in(&file);
    while(!in.atEnd()){
        QString line=in.readLine();
        bok_lines.append(line);
    }
    file.close();
    int temp=0;
    int i=0;
    for(i=0;i<bok_lines.length();i++){
        QString line=bok_lines.at(i);//从容器中得到每一行的数据
        line=line.trimmed();
        QStringList subs=line.split(" ");
        if(id==subs.at(2)){//判断和文档中有没有重复的id
            temp=1;
            break;
        }
    }
    return temp;
}
int newBook::checkblank(QString cnt){
    int temp=0;
    int i=0;
    for(i=0;i<cnt.length();i++){
        if(cnt.at(i)==" "){
            temp=1;
            break;
        }
    }
    return temp;
}
