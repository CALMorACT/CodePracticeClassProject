/*
 * @Author: your name
 * @Date: 2020-07-15 16:08:20
 * @LastEditTime: 2020-07-15 16:21:22
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \CodePracticeClassProject\delbook.h
 */ 
#ifndef DELBOOK_H
#define DELBOOK_H

#include <QDialog>
#include<QList>
namespace Ui {
class delBook;
}

class delBook : public QDialog
{
    Q_OBJECT

public:
    explicit delBook(QWidget *parent = nullptr);
    ~delBook();
    int readdata();//获取文件数据的函数
    void Deleteoneline(int nNum,QString &strall);//删除某一行的函数，nNum代表某一行（从第0行开始计数），strall是文件里所有的内容
    void deleteOnelineInFile(int nNUmLine);
    void deleter(QString &strall);
    void clearFace();

private slots:

    void on_ok_but_clicked();

    void on_no_but_clicked();

private:
    Ui::delBook *ui;
    QList<QString> del_lines;//存放文件数据的容器

};

#endif // DELBOOK_H
