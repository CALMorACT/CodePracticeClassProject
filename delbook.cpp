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
        QMessageBox::critical(this,"wrong","unable to open file","ok");//打开文件失败，反馈给用户
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
        return -1;//打开失败返回-1
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
    int nLine=0;//存放文件中数据的行数
    int Index=0;
    //算出行数nLine
    while(Index!=-1){
        Index=strall.indexOf('\n',Index+1);
        nLine++;
    }
    //删除的是第0行内容
    if(nNum==0){
        int nIndex=strall.indexOf('\n');//计算出第一个换行符的位置
        strall.remove(0,nIndex+1);//删除从第0个字符到第一个换行符的内容
    }
    else{
        int ntemp=nNum;
        int nIndex=0,nIndex2=0;
        while(ntemp--){
            nIndex=strall.indexOf('\n',nIndex+1);//这里会更新nIndex
            if(nIndex!=-1){//说明是有效的
                nIndex2=strall.indexOf('\n',nIndex+1);
            }
        }//计算出要删除行的字符起始位置和终止位置
        //删除的不是最后一行
        if(nNum<nLine-1){
            strall.remove(nIndex+1,nIndex2-nIndex);
        }
        //删除的是最后一行
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
        strall=stream.readAll();//将文件内容全部放入strall中
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
        QString line=del_lines.at(i);//从容器中得到每一行的数据
        line=line.trimmed();
        QStringList subs=line.split(" ");//将各个数据分离
        if(id==subs.at(2)&&name==subs.at(0)&&writer==subs.at(1)){//比较文件中的编号和用户所输入的编号，如果相等则进行删除操作
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
    int nLine=0;//存放文件中数据的行数
    int Index=0;
    //算出行数nLine
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

