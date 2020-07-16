#ifndef STUDENTLISTDLG_H
#define STUDENTLISTDLG_H

#include <QDialog>

namespace Ui {
class studentlistDlg;
}

class studentlistDlg : public QDialog
{
    Q_OBJECT

public:
    explicit studentlistDlg(QWidget *parent = 0);
    ~studentlistDlg();

private slots:
    void on_returnBtn_clicked();
    void refresh();

    void on_listBtn_clicked();

    void on_searchBtn_clicked();

signals:
    void returnsignal();
private:
    Ui::studentlistDlg *ui;
};

#endif // STUDENTLISTDLG_H
