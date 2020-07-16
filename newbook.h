/*
 * @Author: your name
 * @Date: 2020-07-15 16:08:20
 * @LastEditTime: 2020-07-16 11:34:33
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \CodePracticeClassProject\newbook.h
 */ 
#ifndef NEWBOOK_H
#define NEWBOOK_H

#include <QDialog>
#include<QString>

namespace Ui {
class newBook;
}

class newBook : public QDialog
{
    Q_OBJECT

public:
    explicit newBook(QWidget *parent = nullptr);
    ~newBook();
    void writeToFile(QString cnt);
    void clearUserFace();
    int checkid(QString id);
    int checkblank(QString cnt);

private slots:
    void on_ok_bu_clicked();

    void on_no_bu_clicked();

private:
    Ui::newBook *ui;
    QList<QString> bok_lines;
};

#endif
