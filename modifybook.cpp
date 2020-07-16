#include "modifybook.h"
#include "ui_modifybook.h"
#include<QString>
#include<QFile>
#include<QMessageBox>
#include<QTextStream>
#include<QtDebug>
modifyBook::modifyBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifyBook)
{
    ui->setupUi(this);
    if(readFile()==-1){
        QMessageBox::critical(this,"wrong","unable to open file","ok");
        this->close();
    }
    this->model=new QStandardItemModel;
    //设置表头
    this->model->setHorizontalHeaderItem(0,new QStandardItem("title"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("writer"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("id"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("num"));
    this->model->setHorizontalHeaderItem(4,new QStandardItem("totalnum"));

    this->ui->tableView->setModel(model);
    this->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

modifyBook::~modifyBook()
{
    delete ui;
}

void modifyBook::on_ok_but_clicked()
{
     this->model->clear();
     this->model->setHorizontalHeaderItem(0,new QStandardItem("title"));
     this->model->setHorizontalHeaderItem(1,new QStandardItem("writer"));
     this->model->setHorizontalHeaderItem(2,new QStandardItem("id"));
     this->model->setHorizontalHeaderItem(3,new QStandardItem("num"));
     this->model->setHorizontalHeaderItem(4,new QStandardItem("totalnum"));

     this->ui->tableView->setModel(model);
     this->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QString id=this->ui->le_id->text().trimmed();
     bok_lines.clear();
      readFile();
      if(id!=""){
          doQuery(id);
      }
}
void modifyBook::doQuery(QString id){
    int i=0;
    int row=0;
    for(i=0;i<bok_lines.length();i++){
        QString line=bok_lines.at(i);//从容器中得到每一行的数据
        line=line.trimmed();
        QStringList subs=line.split(" ");//将各个数据分离
            if(id==subs.at(2)){
                qDebug()<<"here";
                display(row++,subs);

        }
    }
}
int modifyBook::readFile(){
    QFile file("book.txt");
    if(!file.open(QIODevice::ReadOnly| QIODevice::Text)){
        return -1;//打开失败返回-1
    }
    QTextStream in (&file);
    while(!in.atEnd()){
        QString line=in.readLine();
        bok_lines.append(line);
    }
    file.close();
    return 0;
}

void modifyBook::display(int row, QStringList subs){
    int i=0;
    for(i=0;i<subs.length();i++){
        this->model->setItem(row,i,new QStandardItem(subs.at(i)));
}
}

void modifyBook::deleter(QString &strall){
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
int modifyBook::MOdify(int nNum, QString &strall, QString cnt){
    int nLine=0;//存放文件中数据的行数
    int Index=0;
    int lastline=0;
    //算出行数nLine
    while(Index!=-1){
        Index=strall.indexOf('\n',Index+1);
        nLine++;
    }
    //替换的的是第0行内容
    if(nNum==0&&nLine>1){
        int nIndex=strall.indexOf('\n');//计算出第一个换行符的位置
        qDebug()<<nIndex;
        strall.replace(0,nIndex+1,cnt);//替换一整行的内容
    }
    else{
        int ntemp=nNum;
        int nIndex=0,nIndex2=0;
        while(ntemp--){
            nIndex=strall.indexOf('\n',nIndex+1);//这里会更新nIndex
            if(nIndex!=-1){//说明是有效的
                nIndex2=strall.indexOf('\n',nIndex+1);
            }
        }
        //替换的不是最后一行
        if(nNum<nLine-1){
            strall.replace(nIndex+1,nIndex2-nIndex,cnt);
        }
        //删除的是最后一行
        if(nNum==nLine-1&&nLine==1){
            int len = strall.length();
            strall.replace(nIndex,len-nIndex,cnt);
            lastline=1;
        }
        else if(nNum==nLine-1){
            int len =strall.length();
            strall.replace(nIndex+1,len-nIndex,cnt);
            lastline=1;
        }
    }
    return lastline;
}
void modifyBook::ModifyOnelineInFile(int nNUmLine,QString cnt){
    QString strall;
    QFile readfile("book.txt");
    if(readfile.open(QIODevice::ReadOnly)){
        QTextStream stream(&readfile);
        strall=stream.readAll();//将文件内容全部放入strall中
    }
    readfile.close();
    deleter(strall);
    int ret=MOdify(nNUmLine,strall,cnt);
    if(ret==1){
        QFile writefile("book.txt");
        if(!writefile.open(QIODevice::WriteOnly|QIODevice::Text)){
            return;
        }
        QTextStream out(&writefile);
        out<<strall;
        writefile.close();
    }
    else{
        QString strall2=strall+"\n";
        QFile writefile("book.txt");
        if(!writefile.open(QIODevice::WriteOnly|QIODevice::Text)){
            return;
        }
        QTextStream out(&writefile);
        out<<strall2;
        writefile.close();
    }

     QMessageBox::question(this,"congratulation","operation was successful","ok");



}
void modifyBook::on_change_but_clicked()
{
    QString id=this->ui->le_id->text();
    if(id==""){
        QMessageBox::warning(this,"Warning","Please select a book to modify!",QMessageBox::Yes);
    }
    int index=this->ui->cbb_but->currentIndex();
    QString cnt0=this->ui->line2->text();

    if(checkblank(cnt0)){
        QMessageBox::critical(this,"Warning","input doesn't match!","ok");/***************新增*/
    }
    else if(!checkblank(cnt0)){
    bok_lines.clear();
    readFile();
    int i=0;
    for(i=0;i<bok_lines.length();i++){
        QString line=bok_lines.at(i);//从容器中得到每一行的数据
        line=line.trimmed();
        QStringList subs=line.split(" ");//将各个数据分离
        if(id==subs.at(2)){
        switch (index){
        case 0:
            if(index==0)
            QMessageBox::warning(this,"Warning","Please select edit item!",QMessageBox::Yes);
            break;
        case 1:
            if(index==1){
                QString cnt1=cnt0+" "+subs.at(1)+" "+subs.at(2)+" "+subs.at(3)+" "+subs.at(4)+"\n";
                ModifyOnelineInFile(i,cnt1);
                }
             break;
         case 2:
            if(index==2){
            QString cnt2=subs.at(0)+" "+cnt0+" "+subs.at(2)+" "+subs.at(3)+" "+subs.at(4)+"\n";
                ModifyOnelineInFile(i,cnt2);
                }

            break;
        case 3:
            if(index==3){
            QString cnt3=subs.at(0)+" "+subs.at(1)+" "+subs.at(2)+" "+cnt0+" "+subs.at(4)+"\n";
            ModifyOnelineInFile(i,cnt3);
            }
            break;//修改书的剩余量
         case 4 :
            if(index==4){
            QString cnt4=subs.at(0)+" "+subs.at(1)+" "+subs.at(2)+" "+subs.at(3)+" "+cnt0+"\n";
                ModifyOnelineInFile(i,cnt4);
            }

            break;

        }
        }
    }
    }

}
int modifyBook::checkblank(QString cnt){/************新增*****/
    int temp=0;
    int i=0;
    for(i=0;i<cnt.length();i++){
        if(cnt.at(i)==" "){
            temp=1;
            break;
        }
    }
    return temp;
}
void modifyBook::clearUserFace(){
    ui->le_id->clear();
    ui->line2->clear();
}
