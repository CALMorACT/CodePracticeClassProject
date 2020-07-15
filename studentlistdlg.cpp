/*
 * @Author: your name
 * @Date: 2020-07-15 16:08:20
 * @LastEditTime: 2020-07-15 16:53:26
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \CodePracticeClassProject\studentlistdlg.cpp
 */ 
#include "studentlistdlg.h"
#include "ui_studentlistdlg.h"
#include <QApplication>
#include <QtGui>
#include <QMessageBox>
#include <QApplication>
#include <QtSql>
studentlistDlg::studentlistDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::studentlistDlg)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
    db.setDatabaseName("list.db"); //数据库连接命名
    if(!db.open()) //打开数据库
    {
    close();
    }
    QSqlQueryModel* model=new QSqlQueryModel;
    model->setQuery("select name,id,bookid1,bookid2,bookid3 from student where id>0");
    ui->tableView->setModel(model);
}

studentlistDlg::~studentlistDlg()
{
    delete ui;
}

void studentlistDlg::on_returnBtn_clicked()
{
    this->hide();
    emit returnsignal();
}
//刷新显示
void studentlistDlg::refresh()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
    db.setDatabaseName("list.db"); //数据库连接命名
    if(!db.open()) //打开数据库
    {
    close();
    }
    QSqlQueryModel* model=new QSqlQueryModel;
    model->setQuery("select name,id,bookid1,bookid2,bookid3 from student where id>0");
    ui->tableView->setModel(model);
}
