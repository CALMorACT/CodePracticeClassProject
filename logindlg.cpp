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
//��¼
void loginDlg::on_loginBtn_clicked(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //������ݿ�����
    db.setDatabaseName("list.db"); //���ݿ���������
    if(!db.open()) //�����ݿ�
    {
    close();
    }
    //����ѧ������������ѧ�ż������Ӧ����
    QSqlQuery query(db); //����ִ����� QSL ���
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
            //����ǹ����ߵ�¼������ת�������߽���
            if(userid=="manager"){
                emit managerlogin();
            }
            //������ǹ����ߵ�¼������ת��ͶƱ����
            else{
                emit login();
            }
        }
    }
    //�����ѧ��������δ�ҵ�ƥ�����ͷ�������
    if(a==0){
        QMessageBox::warning(this,"Warning","User name or password  error!",QMessageBox::Yes);
    }
}
//�˳�
void loginDlg::on_exitBtn_clicked(){
    close();
}
//ע��
void loginDlg::on_registerBtn_clicked()
{
    ui->usrLineEdit->clear();
    ui->pwdLineEdit->clear();
    this->hide();
    emit registersignal();
}
