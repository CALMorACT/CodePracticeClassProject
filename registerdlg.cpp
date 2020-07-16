/*
 * @Author: your name
 * @Date: 2020-07-15 16:08:20
 * @LastEditTime: 2020-07-15 16:33:38
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \CodePracticeClassProject\registerdlg.cpp
 */ 
#include "registerdlg.h"
#include "ui_registerdlg.h"
#include <QMessageBox>
#include <QtSql>
#include <QApplication>
#include <QtGui>
registerDlg::registerDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerDlg)
{
    ui->setupUi(this);
}

registerDlg::~registerDlg()
{
    delete ui;
}
//确认注册
void registerDlg::on_registerBtn_clicked()
{
    //检查注册信息是否有未填项
    if(ui->nameEdit->text().trimmed()==""||ui->registerid->text().trimmed()==""||ui->registerpwd->text()==""||ui->registerpwd2->text()==""){
        QMessageBox::warning(this,"Warning","Name,id , password one or password two is empty!",QMessageBox::Yes);
    }
    else{
        //检查两次密码是否一致
        if(ui->registerpwd->text()==ui->registerpwd2->text()){
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
            db.setDatabaseName("list.db"); //数据库连接命名，“学生名单”
            if(!db.open()) //打开数据库
            {
            close();
            }
            //检查是否重复注册
            QSqlQuery query(db); //以下执行相关 QSL 语句
            query.exec("select name,id,password from student where id >= '0'");
            int a=0;
            while(query.next()){
                QString id=query.value(1).toString();
                QString password=query.value(2).toString();
                if(ui->registerid->text().trimmed()==id){
                    a=1;
                    QMessageBox::warning(this,"Warning","This id has already been registered!",QMessageBox::Yes);
                }
            }
            if(a==1){
                ui->nameEdit->clear();
                ui->registerid->clear();
                ui->registerpwd->clear();
                ui->registerpwd2->clear();
                this->hide();
                emit returnsignal();
            }
            else{
                QString name,id, password;
                name=ui->nameEdit->text().trimmed();
                id=ui->registerid->text().trimmed();
                password=ui->registerpwd->text();
                QString i=QString("insert into student values('%1','%2','%3','0','0','0')").arg(name).arg(id).arg(password);
                if(query.exec(i)){
                   QMessageBox::question(this,"Registered successfully!","Registered successfully!!!","ok");
                   ui->nameEdit->clear();
                   ui->registerid->clear();
                   ui->registerpwd->clear();
                   ui->registerpwd2->clear();
                   this->hide();
                   emit returnsignal();
                }
                else{
                QMessageBox::warning(this,"Warning","Registered unsuccessfully!",QMessageBox::Yes);
                }
            }
        }
        else{
            QMessageBox::warning(this,"Warning","Password one and password two are different!",QMessageBox::Yes);
        }
    }
}
//返回
void registerDlg::on_returnBtn_clicked()
{
    ui->nameEdit->clear();
    ui->registerid->clear();
    ui->registerpwd->clear();
    ui->registerpwd2->clear();
    this->hide();
    emit returnsignal();
}
