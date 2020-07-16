#ifndef MODIFYBOOK_H
#define MODIFYBOOK_H

#include <QDialog>
#include<QList>
#include<QStandardItem>
#include<QStandardItemModel>

namespace Ui {
class modifyBook;
}

class modifyBook : public QDialog
{
    Q_OBJECT

public:
    explicit modifyBook(QWidget *parent = nullptr);
    ~modifyBook();
    int readFile();
    void doQuery(QString id);
    void display(int row,QStringList subs);
    int MOdify(int nNum,QString &strall,QString cnt);
    void ModifyOnelineInFile(int nNUmLine,QString cnt);
    void deleter(QString &strall);
    void clearUserFace();
    int checkblank(QString cnt);
private slots:
    void on_ok_but_clicked();
    void on_change_but_clicked();

private:
    Ui::modifyBook *ui;
    QStandardItemModel *model;
     QList<QString> bok_lines;
};

#endif // MODIFYBOOK_H
