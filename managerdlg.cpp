#include "managerdlg.h"
#include "ui_managerdlg.h"
managerDlg::managerDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::managerDlg)
{
    ui->setupUi(this);
}

managerDlg::~managerDlg()
{
    delete ui;
}

void managerDlg::on_returnBtn_clicked()
{
    this->hide();
    emit returnsignal();
}

void managerDlg::on_changepwdBtn_clicked()
{
    this->hide();
    emit changepwdsignal();
}

void managerDlg::on_studentlistBtn_clicked()
{
    this->hide();
    emit studentlistsignal();
}

void managerDlg::on_booklistBtn_clicked()
{
    this->hide();
    emit booklistsignal();
}
