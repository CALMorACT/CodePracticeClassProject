#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QDialog>

namespace Ui {
class addBook;
}

class addBook : public QDialog
{
    Q_OBJECT

public:
    explicit addBook(QWidget *parent = nullptr);
    ~addBook();

private slots:
    void on_pushButton_clicked();

private:
    Ui::addBook *ui;
};

#endif // ADDBOOK_H
