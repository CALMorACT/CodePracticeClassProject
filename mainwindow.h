#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_changepwdBtn_clicked();
    void refresh();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
