#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QMessageBox>
#include <QApplication>
#include <QtSql>
#include<logindlg.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->bookidEdit->clear();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
    db.setDatabaseName("list.db"); //数据库连接命名
    if(!db.open()) //打开数据库
    {
    close();
    }
    QSqlQueryModel* model=new QSqlQueryModel;
    model->setQuery("select title,bookid,writer,num from book");
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_returnBtn_clicked()
{
    this->hide();
    emit returnsignal();
}

void MainWindow::on_changepwdBtn_clicked()
{
    this->hide();
    emit changepwdsignal();
}
void MainWindow::refresh()
{
    ui->bookidEdit->clear();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
    db.setDatabaseName("list.db"); //数据库连接命名
    if(!db.open()) //打开数据库
    {
    close();
    }
    QSqlQueryModel* model=new QSqlQueryModel;
    model->setQuery("select title,bookid,writer,totalnum,num from book");
    ui->tableView->setModel(model);
}

void MainWindow::on_borrowBtn_clicked()
{   QString bookid,studentid;
    bookid=ui->bookidEdit->text();
    studentid=loginDlg::userid;

    //QString类型变量bookid即为学生想借的书的id，查询book文件内是否有书号等于变量bookid的书，并且馆内是否还有库存，如果没有则分别发出不同的警告，如果有就将
    //库存量减一




    //如果输入的bookid存在并且馆内有此书则执行以下代码
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
    db.setDatabaseName("list.db"); //数据库连接命名。
    if(!db.open()) //打开数据库
    {
        close();
    }
    else{
        QSqlQuery query(db);
        query.exec("select name,id,bookid1,bookid2,bookid3 from student where id >= 0 ");
        while(query.next()){
            QString id=query.value(1).toString();
            if(id==studentid){
                QString bookid1=query.value(2).toString(),bookid2=query.value(3).toString(),bookid3=query.value(4).toString();
                if(bookid1=="0"){
                    QString updatesql=QString("update student set bookid1 = '%1' where id = '%2'").arg(bookid).arg(id);
                    bool a=query.exec(updatesql);
                    if(a){
                        QMessageBox::information(this,"Borrow successfully!","Borrow successfully!!!",QMessageBox::Yes);
                        ui->bookidEdit->clear();
                    }
                    else{
                        QMessageBox::warning(this,"Warning","Borrow unsuccessfully!",QMessageBox::Yes);
                    }
                    break;
                }
                else if(bookid2=="0"){
                    QString updatesql=QString("update student set bookid2 = '%1' where id = '%2'").arg(bookid).arg(id);
                    bool a=query.exec(updatesql);
                    if(a){
                        QMessageBox::information(this,"Borrow successfully!","Borrow successfully!!!",QMessageBox::Yes);
                        ui->bookidEdit->clear();
                    }
                    else{
                        QMessageBox::warning(this,"Warning","Borrow unsuccessfully!",QMessageBox::Yes);
                    }
                    break;
                }
                else if(bookid3=="0"){
                    QString updatesql=QString("update student set bookid3 = '%1' where id = '%2'").arg(bookid).arg(id);
                    bool a=query.exec(updatesql);
                    if(a){
                        QMessageBox::information(this,"Borrow successfully!","Borrow successfully!!!",QMessageBox::Yes);
                        ui->bookidEdit->clear();
                    }
                    else{
                        QMessageBox::warning(this,"Warning","Borrow unsuccessfully!",QMessageBox::Yes);
                    }
                    break;
                }
                else{
                    QMessageBox::warning(this,"Warning","You have borrowed three books!",QMessageBox::Yes);
                    ui->bookidEdit->clear();
                    break;
                }
            }
        }
    }
}

void MainWindow::on_remandBtn_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
    db.setDatabaseName("list.db"); //数据库连接命名。
    if(!db.open()) //打开数据库
    {
        close();
    }
    else{
        QSqlQuery query(db);
        QString bookid,studentid;
        bookid=ui->bookidEdit->text();
        studentid=loginDlg::userid;
        bool a=0;
        query.exec("select name,id,bookid1,bookid2,bookid3 from student where id >= 0 ");
        while(query.next()){
            QString id=query.value(1).toString();
            if(id==studentid){
                QString bookid1=query.value(2).toString(),bookid2=query.value(3).toString(),bookid3=query.value(4).toString();
                if(bookid1==bookid){
                    QString updatesql=QString("update student set bookid1 = '0' where id = '%1'").arg(id);
                    a=query.exec(updatesql);
                    if(a){
                        QMessageBox::information(this,"Return successfully!","Return successfully!!!",QMessageBox::Yes);
                        ui->bookidEdit->clear();
                    }
                    else{
                        QMessageBox::warning(this,"Warning","Return unsuccessfully!",QMessageBox::Yes);
                    }
                    break;
                }
                else if(bookid2==bookid){
                    QString updatesql=QString("update student set bookid2 = '0' where id = '%1'").arg(id);
                    a=query.exec(updatesql);
                    if(a){
                        QMessageBox::information(this,"Return successfully!","Return successfully!!!",QMessageBox::Yes);
                        ui->bookidEdit->clear();
                    }
                    else{
                        QMessageBox::warning(this,"Warning","Return unsuccessfully!",QMessageBox::Yes);
                    }
                    break;
                }
                else if(bookid3==bookid){
                    QString updatesql=QString("update student set bookid3 = '0' where id = '%1'").arg(id);
                    a=query.exec(updatesql);
                    if(a){
                        QMessageBox::information(this,"Return successfully!","Return successfully!!!",QMessageBox::Yes);
                        ui->bookidEdit->clear();
                    }
                    else{
                        QMessageBox::warning(this,"Warning","Return unsuccessfully!",QMessageBox::Yes);
                    }
                    break;
                }
                else{
                    a=0;
                    QMessageBox::warning(this,"Warning","Bookid error or you did not borrow this book!",QMessageBox::Yes);
                    ui->bookidEdit->clear();
                    break;
                }
            }
        }
        if(a){
            //将该书的库存量加一,该书书号变量为bookid，变量类型为QString
            a=1;//占位，可删








        }
    }
}

void MainWindow::on_mybookBtn_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
    db.setDatabaseName("list.db"); //数据库连接命名。
    if(!db.open()) //打开数据库
    {
        close();
    }
    else{
        QSqlQuery query(db);
        QString studentid;
        studentid=loginDlg::userid;
        query.exec("select name,id,bookid1,bookid2,bookid3 from student where id >= 0 ");
        while(query.next()){
            QString id=query.value(1).toString();
            if(id==studentid){
                QString bookid1=query.value(2).toString(),bookid2=query.value(3).toString(),bookid3=query.value(4).toString();





            }
        }
    }
}

void MainWindow::on_allbookBtn_clicked()
{
    ui->bookidEdit->clear();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
    db.setDatabaseName("list.db"); //数据库连接命名
    if(!db.open()) //打开数据库
    {
    close();
    }
    QSqlQueryModel* model=new QSqlQueryModel;
    model->setQuery("select title,bookid,writer,totalnum,num from book");
    ui->tableView->setModel(model);
}
