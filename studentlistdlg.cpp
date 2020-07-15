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
    ui->lineEdit->clear();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //������ݿ�����
    db.setDatabaseName("list.db"); //���ݿ���������
    if(!db.open()) //�����ݿ�
    {
    close();
    }
    QSqlTableModel* model=new QSqlTableModel;
    model->setTable("student");
    model->setFilter(QObject::tr("bookid1 >= 0 and bookid2 >= 0 and bookid3 >= 0 "));
    model->select();
    model->removeColumn(2);
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
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
//ˢ����ʾ
void studentlistDlg::refresh()
{
    ui->lineEdit->clear();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //������ݿ�����
    db.setDatabaseName("list.db"); //���ݿ���������
    if(!db.open()) //�����ݿ�
    {
    close();
    }
    QSqlTableModel* model=new QSqlTableModel;
    model->setTable("student");
    model->setFilter(QObject::tr("bookid1 >= 0 and bookid2 >= 0 and bookid3 >= 0 "));
    model->select();
    model->removeColumn(2);
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void studentlistDlg::on_searchBtn_clicked()
{
    QString bookid;
    bookid=ui->lineEdit->text();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //������ݿ�����
    db.setDatabaseName("list.db"); //���ݿ���������
    if(!db.open()) //�����ݿ�
    {
    close();
    }
    QSqlTableModel* model=new QSqlTableModel;
    model->setTable("student");
    model->setFilter(QObject::tr("bookid1 = '%1' or bookid2 = '%2' or bookid3 = '%3'").arg(bookid).arg(bookid).arg(bookid));
    model->select();
    model->removeColumn(2);
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void studentlistDlg::on_listBtn_clicked()
{
    ui->lineEdit->clear();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //������ݿ�����
    db.setDatabaseName("list.db"); //���ݿ���������
    if(!db.open()) //�����ݿ�
    {
    close();
    }
    QSqlTableModel* model=new QSqlTableModel;
    model->setTable("student");
    model->setFilter(QObject::tr("bookid1 >= 0 and bookid2 >= 0 and bookid3 >= 0 "));
    model->select();
    model->removeColumn(2);
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

