#ifndef MANAGERDLG_H
#define MANAGERDLG_H

#include <QDialog>

namespace Ui {
class managerDlg;
}

class managerDlg : public QDialog
{
    Q_OBJECT

public:
    explicit managerDlg(QWidget *parent = 0);
    ~managerDlg();

private slots:
    void on_returnBtn_clicked();

    void on_changepwdBtn_clicked();

    void on_studentlistBtn_clicked();

    void on_booklistBtn_clicked();

signals:
    void returnsignal();
    void changepwdsignal();
    void studentlistsignal();
    void booklistsignal();
private:
    Ui::managerDlg *ui;
};

#endif // MANAGERDLG_H
