#ifndef DELBOOK_H
#define DELBOOK_H

#include <QDialog>
#include<QList>
namespace Ui {
class delBook;
}

class delBook : public QDialog
{
    Q_OBJECT

public:
    explicit delBook(QWidget *parent = nullptr);
    ~delBook();
    int readdata();//��ȡ�ļ����ݵĺ���
    void Deleteoneline(int nNum,QString &strall);//ɾ��ĳһ�еĺ�����nNum����ĳһ�У��ӵ�0�п�ʼ��������strall���ļ������е�����
    void deleteOnelineInFile(int nNUmLine);
    void deleter(QString &strall);
    void clearFace();

private slots:

    void on_ok_but_clicked();

    void on_no_but_clicked();

private:
    Ui::delBook *ui;
    QList<QString> del_lines;//����ļ����ݵ�����

};

#endif // DELBOOK_H
