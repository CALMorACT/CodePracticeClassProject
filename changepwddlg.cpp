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
//����
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

//��������
void changepwdDlg::on_changepwdBtn_clicked()
{
    //�����������������Ƿ�Ϊ��
    if(ui->newpwdlineEdit->text()==""||ui->newpwdlineEdit_2->text()==""){
        QMessageBox::warning(this,"Warning","Password one or password two is empty!",QMessageBox::Yes);
    }
    else{
        //�����������������Ƿ�һ��
        if(ui->newpwdlineEdit->text()==ui->newpwdlineEdit_2->text()){
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //������ݿ�����
            db.setDatabaseName("list.db"); //���ݿ�����������
            if(!db.open()) //�����ݿ�
            {
                close();
            }
            else{
                QSqlQuery query(db); //����ִ����� QSL ���
                QString id , newpwd;
                id=loginDlg::userid;
                newpwd=ui->newpwdlineEdit->text();
                QString updatesql=QString("update student set password = '%1' where id = '%2'").arg(newpwd).arg(id);//������¼����Ϣ������������
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
