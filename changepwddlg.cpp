
/*
 * @Author: your name
 * @Date: 2020-07-15 16:08:20
 * @LastEditTime: 2020-07-15 16:20:05
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \CodePracticeClassProject\changepwddlg.cpp
 */ 
#include "changepwddlg.h"
#include "ui_changepwddlg.h"
#include <QtGui>
#include <QMessageBox>
#include <QApplication>
#include <QtSql>
#include<logindlg.h>
changepwdDlg::changepwdDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changepwdDlg)
{
    ui->setupUi(this);
    ui->newpwdlineEdit->setEchoMode(QLineEdit::Password);
    ui->newpwdlineEdit_2->setEchoMode(QLineEdit::Password);
}

changepwdDlg::~changepwdDlg()
{
    delete ui;
}
//返回
void changepwdDlg::on_returnBtn_clicked()
{
    ui->newpwdlineEdit->clear();
    ui->newpwdlineEdit_2->clear();
    this->hide();
    if(loginDlg::userid=="manager"){
        emit returnmanagerDlg();
    }
    else{
        emit returnsignal();
    }
}

//更改密码
void changepwdDlg::on_changepwdBtn_clicked()
{
    //检查两次输入的密码是否为空
    if(ui->newpwdlineEdit->text()==""||ui->newpwdlineEdit_2->text()==""){
        QMessageBox::warning(this,"Warning","Password one or password two is empty!",QMessageBox::Yes);
    }
    else{
        //检查两次输入的密码是否一致
        if(ui->newpwdlineEdit->text()==ui->newpwdlineEdit_2->text()){
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
            db.setDatabaseName("list.db"); //数据库连接命名。
            if(!db.open()) //打开数据库
            {
                close();
            }
            else{
                QSqlQuery query(db); //以下执行相关 QSL 语句
                QString id , newpwd;
                id=loginDlg::userid;
                newpwd=ui->newpwdlineEdit->text();
                QString updatesql=QString("update student set password = '%1' where id = '%2'").arg(newpwd).arg(id);//搜索登录者信息并更改密码项
                bool a=query.exec(updatesql);
                if(a){
                    QMessageBox::information(this,"Change password successfully!","Change password successfully!!!",QMessageBox::Yes);
                    ui->newpwdlineEdit->clear();
                    ui->newpwdlineEdit_2->clear();
                    this->hide();
                    if(loginDlg::userid=="manager"){
                        emit returnmanagerDlg();
                    }
                    else{
                        emit returnsignal();
                    }
                }
                else{
                    QMessageBox::warning(this,"Warning","Change password unsuccessfully!",QMessageBox::Yes);
                }
            }
        }
        else{
            QMessageBox::warning(this,"Warning","Password one and password two are different!",QMessageBox::Yes);
        }
    }
}
