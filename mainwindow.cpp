/*
 * @Author: your name
 * @Date: 2020-07-15 16:08:20
 * @LastEditTime: 2020-07-15 16:53:02
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \CodePracticeClassProject\mainwindow.cpp
 */ 
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QMessageBox>
#include <QApplication>
#include <QtSql>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
    db.setDatabaseName("list.db"); //数据库连接命名
    if(!db.open()) //打开数据库
    {
    close();
    }
    this->model = new QStandardItemModel;
    this->model->setHorizontalHeaderItem(0,new QStandardItem("title"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("writer"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("id"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("num"));
    this->model->setHorizontalHeaderItem(4,new QStandardItem("totalnum"));
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

void MainWindow::on_searchmyborrowBtn_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
    db.setDatabaseName("list.db"); //数据库连接命名
    if(!db.open()) //打开数据库
    {
        close();
    }

}

void MainWindow::refresh()
{
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
