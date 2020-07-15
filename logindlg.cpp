#include "logindlg.h"
#include "ui_logindlg.h"
#include <QtGui>
#include <QMessageBox>
#include <QApplication>
#include <QtSql>
QString loginDlg::userid;
loginDlg::loginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDlg)
{
    ui->setupUi(this);
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);
}

loginDlg::~loginDlg()
{
    delete ui;
}
//登录
void loginDlg::on_loginBtn_clicked(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
    db.setDatabaseName("list.db"); //数据库连接命名
    if(!db.open()) //打开数据库
    {
    close();
    }
    //检索学生名单，查找学号及密码对应的项
    QSqlQuery query(db); //以下执行相关 QSL 语句
    query.exec("select name,id,password from student where id >= '0'");
    int a=0;
    while(query.next()){
        QString id=query.value(1).toString();
        QString password=query.value(2).toString();
        if(ui->usrLineEdit->text()==id&&ui->pwdLineEdit->text()==password){
            userid=ui->usrLineEdit->text();
            ui->usrLineEdit->clear();
            ui->pwdLineEdit->clear();
            a=1;
            this->hide();
            //如果是管理者登录，则跳转到管理者界面
            if(userid=="manager"){
                emit managerlogin();
            }
            //如果不是管理者登录，则跳转到投票界面
            else{
                emit login();
            }
        }
    }
    //如果在学生名单中未找到匹配的项就发出警告
    if(a==0){
        QMessageBox::warning(this,"Warning","User name or password  error!",QMessageBox::Yes);
    }
}
//退出
void loginDlg::on_exitBtn_clicked(){
    close();
}
//注册
void loginDlg::on_registerBtn_clicked()
{
    ui->usrLineEdit->clear();
    ui->pwdLineEdit->clear();
    this->hide();
    emit registersignal();
}
