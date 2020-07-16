#include "booklistdlg.h"
#include "ui_booklistdlg.h"
#include <QApplication>
#include <QtGui>
#include <QMessageBox>
#include <QApplication>
#include <QtSql>
#include<QTextStream>
#include<QStringList>
#include<QSqlQuery>
#include<modifybook.h>
booklistDlg::booklistDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::booklistDlg)
{
    ui->setupUi(this);
   if(readFromFile()==-1){
       QMessageBox::critical(this,"wrong","unable to open file","ok");
       this->close();
   }
   this->model=new QStandardItemModel;
   //设置表头
   this->model->setHorizontalHeaderItem(0,new QStandardItem("title"));
   this->model->setHorizontalHeaderItem(1,new QStandardItem("writer"));
   this->model->setHorizontalHeaderItem(2,new QStandardItem("id"));
   this->model->setHorizontalHeaderItem(3,new QStandardItem("num"));
   this->model->setHorizontalHeaderItem(4,new QStandardItem("totalnum"));

   this->ui->tableView->setModel(model);
   this->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

booklistDlg::~booklistDlg()
{
    delete ui;
}

void booklistDlg::on_returnBtn_clicked()
{
    this->hide();
    emit returnsignal();
}

void booklistDlg::on_add_clicked()
{
    this->a.clearUserFace();
    this->a.show();
}
int booklistDlg::readFromFile(){
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
    return 0;
}


void booklistDlg::on_btn_search_clicked()
{
    try {
           int index=this->ui->cbb_method->currentIndex();
           ui->le_cnt->textEdited(m_sLastSearch);
           QString cnt=this->ui->le_cnt->text().trimmed();
           if(index==0)
           {
               QMessageBox::warning(this,"Warning","Please select a search method!",QMessageBox::Yes);
           }
           /*
            * index:
            * 1: 按照书名
            * 2: 按照作者
            * 3: 按照编号
           */
           else{
               this->model->clear();
               this->model->setHorizontalHeaderItem(0,new QStandardItem("title"));
               this->model->setHorizontalHeaderItem(1,new QStandardItem("writer"));
               this->model->setHorizontalHeaderItem(2,new QStandardItem("id"));
               this->model->setHorizontalHeaderItem(3,new QStandardItem("num"));
               this->model->setHorizontalHeaderItem(4,new QStandardItem("totalnum"));

               this->ui->tableView->setModel(model);
               this->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
               m_sLastSearch = cnt;
               if(cnt!=""){
                   doQuery(index,cnt);
               }
           }
       } catch (const char* err) {
           QMessageBox::critical(this,"wrong",err,"ok");
       }

}
void booklistDlg::doQuery(int index,QString cnt){
    int i=0;
    int row=0;
    for(i=0;i<bok_lines.length();i++){
        QString line=bok_lines.at(i);//从容器中得到每一行的数据
        line=line.trimmed();
        QStringList subs=line.split(" ");//将各个数据分离
        switch (index){
        case 1:
            if(cmp(subs.at(0),cnt)){

                display(row++,subs);
            }
            break;
        case 2:
            if(cmp(subs.at(1),cnt)){

                display(row++,subs);
            }
            break;
        case 3:
            if(cnt==subs.at(2)){

                display(row++,subs);
            }
            break;//按书的编号

        }
    }
}
void booklistDlg::display(int row,QStringList subs){//传入行和书的信息
    int i=0;
    for(i=0;i<subs.length();i++){
        this->model->setItem(row,i,new QStandardItem(subs.at(i)));
    }
}
int booklistDlg::cmp(QString str1,QString str2){
    int index=1;
    int temp=1;
    int index2=0;
    int j=0;
    for(j=0;j<str1.length();j++){
        if(str1.at(j)==str2.at(0)&&(str1.length()-j)>=str2.length()){
             index2=1;
            int i=0;
            for(i=0;i<str2.length();i++){//第二循环开头
                if(str1.at(j)!=str2.at(i)){
                    temp=0;
                }
                j++;
                if(temp==0){
                    index=0;
                    temp=1;
                    break;
                }
            }//第二循环结尾
            if(temp==1){
                index=1;
                break;
            }
        }
    }
    int all=index+temp;
    if(index2==0){
        all=0;
    }
    return all;
}

void booklistDlg::on_deleteBtn_clicked()
{
    b.clearFace();
    b.show();
}

void booklistDlg::on_pushButton_clicked()
{
    this->refresh();
}

void booklistDlg::on_reviseBtn_clicked()
{
    c.clearUserFace();
    c.show();
}
void booklistDlg::refresh(){
    ui->le_cnt->clear();
    this->model->clear();
        this->model->setHorizontalHeaderItem(0,new QStandardItem("title"));
        this->model->setHorizontalHeaderItem(1,new QStandardItem("writer"));
        this->model->setHorizontalHeaderItem(2,new QStandardItem("id"));
        this->model->setHorizontalHeaderItem(3,new QStandardItem("num"));
        this->model->setHorizontalHeaderItem(4,new QStandardItem("totalnum"));

        this->ui->tableView->setModel(model);
        this->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QFile file("book.txt");
    if(!file.open(QIODevice::ReadOnly| QIODevice::Text)){
        QMessageBox::critical(this,"wrong","unable to open file!","ok");//打开失败反馈给用户
        return;
    }
    QTextStream in(&file);
    bok_lines.clear();
    while(!in.atEnd()){
        QString line=in.readLine();
        bok_lines.append(line);
    }

    file.close();
    int i=0;
    for(i=0;i<bok_lines.length();i++){
        QString line=bok_lines.at(i);//从容器中得到每一行的数据
        line=line.trimmed();
        QStringList subs=line.split(" ");
        int j=0;
        for(j=0;j<subs.length();j++){
            this->model->setItem(i,j,new QStandardItem(subs.at(j)));
        }
    }

}
