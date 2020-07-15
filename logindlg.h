/*
 * @Author: your name
 * @Date: 2020-07-15 16:08:20
 * @LastEditTime: 2020-07-15 16:32:17
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \CodePracticeClassProject\logindlg.h
 */ 
#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>

namespace Ui {
class loginDlg;
}

class loginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit loginDlg(QWidget *parent = 0);
    ~loginDlg();
    static QString userid;//全局变量，登录者id
private slots:
    void on_exitBtn_clicked();
    void on_loginBtn_clicked();
    void on_registerBtn_clicked();

signals:
    void managerlogin();
    void login();
    void registersignal();
private:
    Ui::loginDlg *ui;
};

#endif // LOGINDLG_H
