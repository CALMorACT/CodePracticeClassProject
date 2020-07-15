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
//ȷ��ע��
void registerDlg::on_registerBtn_clicked()
{
    //���ע����Ϣ�Ƿ���δ����
    if(ui->nameEdit->text()==""||ui->registerid->text()==""||ui->registerpwd->text()==""||ui->registerpwd2->text()==""){
        QMessageBox::warning(this,"Warning","Name,id , password one or password two is empty!",QMessageBox::Yes);
    }
    else{
        //������������Ƿ�һ��
        if(ui->registerpwd->text()==ui->registerpwd2->text()){
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //������ݿ�����
            db.setDatabaseName("list.db"); //���ݿ�������������ѧ��������
            if(!db.open()) //�����ݿ�
            {
            close();
            }
            //����Ƿ��ظ�ע��
            QSqlQuery query(db); //����ִ����� QSL ���
            query.exec("select name,id,password from student where id >= '0'");
            int a=0;
            while(query.next()){
                QString id=query.value(1).toString();
                QString password=query.value(2).toString();
                if(ui->registerid->text()==id){
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
                name=ui->nameEdit->text();
                id=ui->registerid->text();
                password=ui->registerpwd->text();
                QString i=QString("insert into student values('%1','%2','%3','0','0','0')").arg(name).arg(id).arg(password);
                if(query.exec(i)){
                   QMessageBox::information(this,"Registered successfully!","Registered successfully!!!",QMessageBox::Yes);
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
//����
void registerDlg::on_returnBtn_clicked()
{
    ui->nameEdit->clear();
    ui->registerid->clear();
    ui->registerpwd->clear();
    ui->registerpwd2->clear();
    this->hide();
    emit returnsignal();
}
