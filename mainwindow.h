/*
 * @Author: your name
 * @Date: 2020-07-16 11:35:25
 * @LastEditTime: 2020-07-16 11:47:31
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \CodePracticeClassProjectc:\Users\26466\Documents\Tencent Files\2646677495\FileRecv\project7\mainwindow.h
 */ 
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStandardItem>
#include<QStandardItemModel>
#include<QFile>
#include<QString>
#include<QList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void returnsignal();
    void changepwdsignal();
private slots:
    void on_returnBtn_clicked();
    void display(int row,QStringList subs);//��ģ��������ĺ���
    void doQuery(int index,QString cnt);//�����ѯ
    /******/
    int readFromFile();//�������ݴ��������ĺ���
    int cmp(QString str1,QString str2);
    void on_changepwdBtn_clicked();
    void refresh();
    void showAll();
    void on_check_clicked();
    void doQuery2(QString cnt0,QString cnt1,QString cnt2);//�ѽ����鼮��ѯ����
    void display2(int row,QStringList subs);//�ѽ����鼮����ʾ����
    void on_pushButton_clicked();

    void on_borrowBtn_clicked();

    void on_remandBtn_clicked();

    void on_borrowed_clicked();
    int borrowBook(QString id);/****************����***************/
    int returnBook(QString id);
    int Change(int nNum,QString &strall,QString cnt);
    void ChangeInFile(int nNUmLine,QString cnt);
    void deleter(QString &strall);

private:
    Ui::MainWindow *ui;
    QList<QString> bok_lines;
    QStandardItemModel *model;
};

#endif // MAINWINDOW_H
