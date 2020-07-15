/*
 * @Author: your name
 * @Date: 2020-07-15 16:08:20
 * @LastEditTime: 2020-07-15 16:52:32
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \CodePracticeClassProject\booklistdlg.h
 */ 
#ifndef BOOKLISTDLG_H
#define BOOKLISTDLG_H

#include <QDialog>
#include"newbook.h"
#include<QFile>
#include<QString>
#include<QList>
#include<QStandardItem>
#include<QStandardItemModel>
#include"delbook.h"
namespace Ui {
class booklistDlg;
}

class booklistDlg : public QDialog
{
    Q_OBJECT

public:
    explicit booklistDlg(QWidget *parent = 0);
    ~booklistDlg();

private slots:
    void on_returnBtn_clicked();
    void display(int row,QStringList subs);//在模型中输出的函数
    void on_add_clicked();
    int readFromFile();//读入数据存入容器的函数
    void doQuery(int index,QString cnt);
    void on_btn_search_clicked();
    int cmp(QString str1,QString str2);

    void on_deleteBtn_clicked();

    void on_pushButton_clicked();

    void on_reviseBtn_clicked();

signals:
    void returnsignal();
private:
    Ui::booklistDlg *ui;
    newBook a;
    QList<QString> bok_lines;
    QStandardItemModel *model;
    delBook b;
    QString m_sLastSearch;
};

#endif // BOOKLISTDLG_H
