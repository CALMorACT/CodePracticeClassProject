/*
 * @Author: your name
 * @Date: 2020-07-15 16:08:20
 * @LastEditTime: 2020-07-15 16:52:50
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \CodePracticeClassProject\main.cpp
 */ 
#include "mainwindow.h"
#include <QApplication>
#include<logindlg.h>
#include <QtGui>
#include <QMessageBox>
#include <QApplication>
#include <QtSql>
#include<managerdlg.h>
#include<registerdlg.h>
#include<changepwddlg.h>
#include<studentlistdlg.h>
#include<booklistdlg.h>
#include<QFile>
int main(int argc, char *argv[])
{
    /*
        两张表：
            student: name, id, password, bookid1, bookid2, bookid3
            book: title, bookid, writer, totalnum, num
            除totalnum和num为int，其余均为varchar
            如果想做日期，为student增加booktime1 booktime2 booktime3 均为varchar，通过qdate::currentdate()获取日期
            通过tostring和fromstring转换
            表book更改成了文件方式

        */
    QFile file("book.txt");
    if(!file.open(QIODevice::Append| QIODevice::Text)){
        return 0;
    }
    file.close();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
    db.setDatabaseName("list.db"); //数据库连接命名
    if(!db.open()) //打开数据库
    {
    return 0;
    }
    QSqlQuery query(db); //以下执行相关 QSL 语句
    query.exec("create table student(name varchar,id varchar primary key,password varchar,bookid1 varchar,bookid2 varchar,bookid3 vachar)");
    query.exec("insert into student values('manager','manager','123456','0','0','0')");
    //向表中插入 1 条记录,管理者
    query.exec("create table book(title varchar,bookid varchar primary key,writer varchar,totalnum int,num int)");
    QApplication a(argc, argv);
    MainWindow w;
    loginDlg l;
    registerDlg r;
    managerDlg m;
    changepwdDlg c;
    studentlistDlg s;
    booklistDlg b;
    QObject::connect(&l,SIGNAL(login()),&w,SLOT(show()));
    QObject::connect(&l,SIGNAL(managerlogin()),&m,SLOT(show()));
    QObject::connect(&l,SIGNAL(registersignal()),&r,SLOT(show()));
    QObject::connect(&r,SIGNAL(returnsignal()),&l,SLOT(show()));
    QObject::connect(&m,SIGNAL(returnsignal()),&l,SLOT(show()));
    QObject::connect(&w,SIGNAL(returnsignal()),&l,SLOT(show()));
    QObject::connect(&w,SIGNAL(changepwdsignal()),&c,SLOT(show()));
    QObject::connect(&m,SIGNAL(changepwdsignal()),&c,SLOT(show()));
    QObject::connect(&c,SIGNAL(returnmanagerDlg()),&m,SLOT(show()));
    QObject::connect(&c,SIGNAL(returnsignal()),&w,SLOT(show()));
    QObject::connect(&m,SIGNAL(studentlistsignal()),&s,SLOT(show()));
    QObject::connect(&s,SIGNAL(returnsignal()),&m,SLOT(show()));
    QObject::connect(&m,SIGNAL(booklistsignal()),&b,SLOT(show()));
    QObject::connect(&b,SIGNAL(returnsignal()),&m,SLOT(show()));
    QObject::connect(&m,SIGNAL(studentlistsignal()),&s,SLOT(refresh()));
    QObject::connect(&m,SIGNAL(booklistsignal()),&b,SLOT(refresh()));
    QObject::connect(&l,SIGNAL(login()),&w,SLOT(refresh()));
    l.show();

    return a.exec();
}
