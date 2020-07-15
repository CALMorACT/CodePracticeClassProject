#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStandardItem>
#include<QStandardItemModel>

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
    void searchmyborrow();
private slots:
    void on_returnBtn_clicked();
    void on_searchmyborrowBtn_clicked();
    void on_changepwdBtn_clicked();
    void refresh();

private:
    Ui::MainWindow *ui;
    QStandardItemModel* model;
};

#endif // MAINWINDOW_H
