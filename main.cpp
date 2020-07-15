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
int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
    db.setDatabaseName("list.db"); //数据库连接命名
    if(!db.open()) //打开数据库
    {
    return 0;
    }
    QSqlQuery query(db); //以下执行相关 QSL 语句
    query.exec("create table student(name varchar,id varchar primary key,password varchar,bookid1 varchar,bookid2 varchar,bookid3 vachar)");
    query.exec("insert into student values('manager','manager','123456','-1','-1','-1')");
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
