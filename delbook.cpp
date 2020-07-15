#include "delbook.h"
#include "ui_delbook.h"
#include <QString>
#include<QTextStream>
#include<QFile>
#include<QMessageBox>
#include<QDebug>
delBook::delBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delBook)
{
    ui->setupUi(this);
    if(readdata()==-1){
        QMessageBox::critical(this,"wrong","unable to open file","ok");//���ļ�ʧ�ܣ��������û�
        this->close();
    }
}

delBook::~delBook()
{
    delete ui;
}

int delBook::readdata(){
    QFile file("book.txt");
    if(!file.open(QIODevice::ReadOnly| QIODevice::Text)){
        return -1;//��ʧ�ܷ���-1
    }
    QTextStream in(&file);
    while(!in.atEnd()){
        QString line=in.readLine();
        del_lines.append(line);
    }
    file.close();
    int i=0;
    for(i=0;i<del_lines.length();i++){

    }
    return 0;
}

void delBook::Deleteoneline(int nNum, QString &strall){
    int nLine=0;//����ļ������ݵ�����
    int Index=0;
    //�������nLine
    while(Index!=-1){
        Index=strall.indexOf('\n',Index+1);
        nLine++;
    }
    //ɾ�����ǵ�0������
    if(nNum==0){
        int nIndex=strall.indexOf('\n');//�������һ�����з���λ��
        strall.remove(0,nIndex+1);//ɾ���ӵ�0���ַ�����һ�����з�������
    }
    else{
        int ntemp=nNum;
        int nIndex=0,nIndex2=0;
        while(ntemp--){
            nIndex=strall.indexOf('\n',nIndex+1);//��������nIndex
            if(nIndex!=-1){//˵������Ч��
                nIndex2=strall.indexOf('\n',nIndex+1);
            }
        }//�����Ҫɾ���е��ַ���ʼλ�ú���ֹλ��
        //ɾ���Ĳ������һ��
        if(nNum<nLine-1){
            strall.remove(nIndex+1,nIndex2-nIndex);
        }
        //ɾ���������һ��
        else if(nNum==nLine-1){
            int len =strall.length();
            strall.remove(nIndex,len-nIndex);
        }
    }
}
void delBook::deleteOnelineInFile(int nNUmLine){
    QString strall;
    QFile readfile("book.txt");
    if(readfile.open(QIODevice::ReadOnly)){
        QTextStream stream(&readfile);
        strall=stream.readAll();//���ļ�����ȫ������strall��
    }
    readfile.close();
    deleter(strall);
    Deleteoneline(nNUmLine,strall);
    QString strall2=strall+'\n';
    QFile writefile("book.txt");
    if(!writefile.open(QIODevice::WriteOnly|QIODevice::Text)){
        return;
    }
    QTextStream out(&writefile);
    out<<strall2;
    writefile.close();
}



void delBook::on_no_but_clicked()
{
    this->close();
}
void delBook::on_ok_but_clicked()
{
    QString id=this->ui->le_id->text();
    QString name=this->ui->le_name->text();
    QString writer=this->ui->le_writer->text();

    int i=0;
    int temp=0;
    for(i=0;i<del_lines.length();i++){
        QString line=del_lines.at(i);//�������еõ�ÿһ�е�����
        line=line.trimmed();
        QStringList subs=line.split(" ");//���������ݷ���
        if(id==subs.at(2)&&name==subs.at(0)&&writer==subs.at(1)){//�Ƚ��ļ��еı�ź��û�������ı�ţ������������ɾ������
                deleteOnelineInFile(i);
                temp=1;
                QMessageBox::question(this,"congratulation","operation was successful","ok");
                clearFace();
    }

}
    if(temp==0){
        QMessageBox::critical(this,"warning","no such book was found","ok");
    }
}
void delBook::deleter(QString &strall){
    int nLine=0;//����ļ������ݵ�����
    int Index=0;
    //�������nLine
    while(Index!=-1){
        Index=strall.indexOf('\r',Index+1);
        nLine++;
    }
    int index1=0,index2=0;
    int temp=nLine;
    while(temp--){
        index1=strall.indexOf('\r',index2);
        index2=index1;
        strall.remove(index1,1);
    }
}
void delBook::clearFace(){
    this->ui->le_id->setText("");
    this->ui->le_name->setText("");
    this->ui->le_writer->setText("");
}

