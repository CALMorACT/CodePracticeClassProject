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
    void clearUserFace();//确认后清屏

private slots:
    void on_ok_bu_clicked();

    void on_no_bu_clicked();

private:
    Ui::newBook *ui;
};

#endif // NEWBOOK_H
