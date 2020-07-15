#ifndef CHANGEPWDDLG_H
#define CHANGEPWDDLG_H

#include <QDialog>

namespace Ui {
class changepwdDlg;
}

class changepwdDlg : public QDialog
{
    Q_OBJECT

public:
    explicit changepwdDlg(QWidget *parent = 0);
    ~changepwdDlg();
signals:
    void returnmanagerDlg();
    void returnsignal();
private slots:
    void on_changepwdBtn_clicked();

    void on_returnBtn_clicked();

private:
    Ui::changepwdDlg *ui;
};

#endif // CHANGEPWDDLG_H
