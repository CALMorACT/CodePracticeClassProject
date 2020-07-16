/*
 * @Author: your name
 * @Date: 2020-07-15 16:08:20
 * @LastEditTime: 2020-07-15 16:53:02
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \CodePracticeClassProject\mainwindow.cpp
 */ 
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QMessageBox>
#include <QApplication>
#include <QtSql>
#include<logindlg.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(readFromFile()==-1){
        QMessageBox::critical(this,"wrong","unable to open file","ok");
        this->close();
    }
    this->model=new QStandardItemModel;
    //设置表头
    this->model->setHorizontalHeaderItem(0,new QStandardItem("title"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("writer"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("id"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("num"));

    this->ui->tableView->setModel(model);
    this->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    showAll();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_returnBtn_clicked()
{
    this->hide();
    emit returnsignal();
}

void MainWindow::on_changepwdBtn_clicked()
{
    this->hide();
    emit changepwdsignal();
}
int MainWindow::readFromFile(){
    QFile file("book.txt");
    if(!file.open(QIODevice::ReadOnly| QIODevice::Text)){
        return -1;//打开失败返回-1
    }
    QTextStream in(&file);
    while(!in.atEnd()){
        QString line=in.readLine();
        bok_lines.append(line);
    }
    file.close();
    return 0;
}


void MainWindow::on_check_clicked()
{
        int index=this->ui->cbb_but->currentIndex();
        if(index==0)
        {
            QMessageBox::warning(this,"Warning","Please select a search method!",QMessageBox::Yes);
        }
        /*
         * index:
         * 1: 按照书名
         * 2: 按照作者
         * 3: 按照编号
        */
        else{
            this->model->clear();
            this->model->setHorizontalHeaderItem(0,new QStandardItem("title"));
            this->model->setHorizontalHeaderItem(1,new QStandardItem("writer"));
            this->model->setHorizontalHeaderItem(2,new QStandardItem("id"));
            this->model->setHorizontalHeaderItem(3,new QStandardItem("num"));
            this->ui->tableView->setModel(model);
            this->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            QString cnt=this->ui->le_line->text().trimmed();
            if(cnt!=""){
                doQuery(index,cnt);
            }
        }
}
int MainWindow::cmp(QString str1,QString str2){
    int index=1;
    int temp=1;
    int index2=0;
    int j=0;
    for(j=0;j<str1.length();j++){
        if(str1.at(j)==str2.at(0)&&(str1.length()-j)>=str2.length()){
             index2=1;
            int i=0;
            for(i=0;i<str2.length();i++){//第二循环开头
                if(str1.at(j)!=str2.at(i)){
                    temp=0;
                }
                j++;
                if(temp==0){
                    index=0;
                    temp=1;
                    break;
                }
            }//第二循环结尾
            if(temp==1){
                index=1;
                break;
            }
        }
    }
    int all=index+temp;
    if(index2==0){
        all=0;
    }
    return all;
}
void MainWindow::display(int row,QStringList subs){//传入行和书的信息
    int i=0;
    for(i=0;i<subs.length()-1;i++){
        this->model->setItem(row,i,new QStandardItem(subs.at(i)));
    }
}
void MainWindow::doQuery(int index,QString cnt){
    int i=0;
    int row=0;
    for(i=0;i<bok_lines.length();i++){
        QString line=bok_lines.at(i);//从容器中得到每一行的数据
        line=line.trimmed();
        QStringList subs=line.split(" ");//将各个数据分离
        switch (index){
        case 1:
            if(cmp(subs.at(0),cnt)){

                display(row++,subs);
            }
            break;
        case 2:
            if(cmp(subs.at(1),cnt)){

                display(row++,subs);
            }
            break;
        case 3:
            if(cnt==subs.at(2)){

                display(row++,subs);
            }
            break;//按书的编号

        }
    }
}

 int MainWindow::borrowBook(QString id){
    int i=0;
    int index=0;
    int index2=1;
    for(i=0;i<bok_lines.length();i++){
        QString line=bok_lines.at(i);//从容器中得到每一行的数据
        line=line.trimmed();
        QStringList subs=line.split(" ");//将各个数据分离
        if(id==subs.at(2)){//判断是否有这本书
            index2=0;
            int num=subs.at(3).toInt();
            qDebug()<<num;

            if(num>0){
                num--;
                qDebug()<<num;
                QString cnt0=QString::number(num,10);
                qDebug()<<cnt0;
                QString cnt=subs.at(0)+" "+subs.at(1)+" "+subs.at(2)+" "+cnt0+" "+subs.at(4)+"\n";
                ChangeInFile(i,cnt);
                break;
            }
            else if(num==0){
                QMessageBox::critical(this,"sorry","there is no surplus!","ok");//没有剩余量
                index=1;
                break;
            }

        }
}
    if(index2==1){
        QMessageBox::critical(this,"sorry","no such book!","ok");
        index=2;//文档中没有这个图书
    }
    return index;
 }
 void MainWindow::deleter(QString &strall){
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
 void MainWindow::ChangeInFile(int nNUmLine,QString cnt){

     QString strall;
     QFile readfile("book.txt");
     if(readfile.open(QIODevice::ReadOnly)){
         QTextStream stream(&readfile);
         strall=stream.readAll();//将文件内容全部放入strall中
     }
     readfile.close();
     deleter(strall);
     int ret=Change(nNUmLine,strall,cnt);
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

 }
int MainWindow::Change(int nNum,QString &strall,QString cnt){
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
       if(nNum==nLine-1&&nLine>1){
            int len =strall.length();
            strall.replace(nIndex+1,len-nIndex,cnt);
            lastline=1;
        }
    else if(nNum==nLine-1&&nLine==1){
        int len =strall.length();
        strall.replace(nIndex+0,len-nIndex,cnt);
        lastline=1;
    }
    return lastline;
}
}
int MainWindow::returnBook(QString id){
   int i=0;
   int index=0;
   int index2=1;
   for(i=0;i<bok_lines.length();i++){
       QString line=bok_lines.at(i);//从容器中得到每一行的数据
       line=line.trimmed();
       QStringList subs=line.split(" ");//将各个数据分离
       if(id==subs.at(2)){//判断是否有这本书
           index2=0;
           int num=subs.at(3).toInt();
               num++;
               QString cnt0=QString::number(num,10);
               QString cnt=subs.at(0)+" "+subs.at(1)+" "+subs.at(2)+" "+cnt0+" "+subs.at(4)+"\n";
               ChangeInFile(i,cnt);
           break;
       }
}
   if(index2==1){
       QMessageBox::critical(this,"sorry","no such book!","ok");
       index=2;//文档中没有这个图书
   }
   return index;
}

void MainWindow::showAll(){
    QFile file("book.txt");
    if(!file.open(QIODevice::ReadOnly| QIODevice::Text)){
        QMessageBox::critical(this,"wrong","unable to open file!","ok");//打开失败反馈给用户
        return;
    }
    QTextStream in(&file);
    bok_lines.clear();
    while(!in.atEnd()){
        QString line=in.readLine();
        bok_lines.append(line);
    }

    file.close();
    int i=0;
    for(i=0;i<bok_lines.length();i++){
        QString line=bok_lines.at(i);//从容器中得到每一行的数据
        line=line.trimmed();
        QStringList subs=line.split(" ");
        int j=0;
        for(j=0;j<subs.length()-1;j++){
            this->model->setItem(i,j,new QStandardItem(subs.at(j)));
        }
}
}

void MainWindow::on_pushButton_clicked()
{
    this->refresh();
}
void MainWindow::refresh(){
    ui->bookidEdit->clear();
    ui->le_line->clear();
    this->model->clear();
    this->model=new QStandardItemModel;
    //设置表头
    this->model->setHorizontalHeaderItem(0,new QStandardItem("title"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("writer"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("id"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("num"));

    this->ui->tableView->setModel(model);
    this->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
   showAll();
}

void MainWindow::display2(int row,QStringList subs){
    int i=0;
    for(i=0;i<subs.length()-2;i++){
        this->model->setItem(row,i,new QStandardItem(subs.at(i)));
    }
}
void MainWindow::doQuery2(QString cnt0,QString cnt1,QString cnt2){
    int i=0;
    int row=0;
    for(i=0;i<bok_lines.length();i++){
        QString line=bok_lines.at(i);//从容器中得到每一行的数据
        line=line.trimmed();
        QStringList subs=line.split(" ");//将各个数据分离

            if(cnt0==subs.at(2)||cnt1==subs.at(2)||cnt2==subs.at(2)){//判断文档里是否有与三个id相同的

                display2(row++,subs);
            }


        }
    }


void MainWindow::on_borrowBtn_clicked()
{
    QString bookid,studentid;
    bookid=ui->bookidEdit->text().trimmed();
    studentid=loginDlg::userid;
    if(bookid==""){
            QMessageBox::warning(this,"Warning","Please enter the bookid!",QMessageBox::Yes);
        }
    else{

        //QString类型变量bookid即为学生想借的书的id，查询book文件内是否有书号等于变量bookid的书，并且馆内是否还有库存，如果没有则分别发出不同的警告，如果有就将
        //库存量减一

        int ret=borrowBook(bookid);//返回值为0->借阅成功
                                   //返回值为1->剩余量不足
                                   //返回值为2->没有这本书


        //如果输入的bookid存在并且馆内有此书则执行以下代码
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
        db.setDatabaseName("list.db"); //数据库连接命名。
        if(!db.open()) //打开数据库
        {
            close();
        }
        else{
            QSqlQuery query(db);
            query.exec("select name,id,bookid1,bookid2,bookid3 from student where id >= 0 ");
            while(query.next()){
                QString id=query.value(1).toString();
                if(id==studentid){
                    QString bookid1=query.value(2).toString(),bookid2=query.value(3).toString(),bookid3=query.value(4).toString();
                    if(bookid1=="0"){
                        int ret=borrowBook(bookid);
                        if(ret==0){
                            QString updatesql=QString("update student set bookid1 = '%1' where id = '%2'").arg(bookid).arg(id);
                            bool a=query.exec(updatesql);
                            if(a){
                                QMessageBox::question(this,"Borrow successfully!","Borrow successfully!!!","ok");
                                ui->bookidEdit->clear();
                            }
                            else{
                                QMessageBox::warning(this,"Warning","Borrow unsuccessfully!",QMessageBox::Yes);
                            }
                        }
                        break;
                    }
                    else if(bookid2=="0"){
                        int ret=borrowBook(bookid);
                        if(ret==0){
                            QString updatesql=QString("update student set bookid2 = '%1' where id = '%2'").arg(bookid).arg(id);
                            bool a=query.exec(updatesql);
                            if(a){
                                QMessageBox::question(this,"Borrow successfully!","Borrow successfully!!!","ok");
                                ui->bookidEdit->clear();
                            }
                            else{
                                QMessageBox::warning(this,"Warning","Borrow unsuccessfully!",QMessageBox::Yes);
                            }
                        }
                        break;
                    }
                    else if(bookid3=="0"){
                        int ret=borrowBook(bookid);
                        if(ret==0){
                            QString updatesql=QString("update student set bookid3 = '%1' where id = '%2'").arg(bookid).arg(id);
                            bool a=query.exec(updatesql);
                            if(a){
                                QMessageBox::question(this,"Borrow successfully!","Borrow successfully!!!","ok");
                                ui->bookidEdit->clear();
                            }
                            else{
                                QMessageBox::warning(this,"Warning","Borrow unsuccessfully!",QMessageBox::Yes);
                            }
                        }
                        break;
                    }
                    else{
                        QMessageBox::warning(this,"Warning","You have borrowed three books!",QMessageBox::Yes);
                        ui->bookidEdit->clear();
                        break;
                    }
                }
            }
        }
    }
}

void MainWindow::on_remandBtn_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
    db.setDatabaseName("list.db"); //数据库连接命名
    if(!db.open()) //打开数据库
    {
        close();
    }
    else{
        QSqlQuery query(db);
        QString bookid,studentid;
        bookid=ui->bookidEdit->text().trimmed();
        studentid=loginDlg::userid;
        if(bookid==""){
                QMessageBox::warning(this,"Warning","Please enter the bookid!",QMessageBox::Yes);
            }
        else{
            bool a=0;
            query.exec("select name,id,bookid1,bookid2,bookid3 from student where id >= 0 ");
            while(query.next()){
                QString id=query.value(1).toString();
                if(id==studentid){
                    QString bookid1=query.value(2).toString(),bookid2=query.value(3).toString(),bookid3=query.value(4).toString();
                    if(bookid1==bookid){
                        QString updatesql=QString("update student set bookid1 = '0' where id = '%1'").arg(id);
                        a=query.exec(updatesql);
                        if(a){
                            QMessageBox::question(this,"Return successfully!","Return successfully!!!","ok");
                            ui->bookidEdit->clear();
                        }
                        else{
                            QMessageBox::warning(this,"Warning","Return unsuccessfully!",QMessageBox::Yes);
                        }
                        break;
                    }
                    else if(bookid2==bookid){
                        QString updatesql=QString("update student set bookid2 = '0' where id = '%1'").arg(id);
                        a=query.exec(updatesql);
                        if(a){
                            QMessageBox::question(this,"Return successfully!","Return successfully!!!","ok");
                            ui->bookidEdit->clear();
                        }
                        else{
                            QMessageBox::warning(this,"Warning","Return unsuccessfully!",QMessageBox::Yes);
                        }
                        break;
                    }
                    else if(bookid3==bookid){
                        QString updatesql=QString("update student set bookid3 = '0' where id = '%1'").arg(id);
                        a=query.exec(updatesql);
                        if(a){
                            QMessageBox::question(this,"Return successfully!","Return successfully!!!","ok");
                            ui->bookidEdit->clear();
                        }
                        else{
                            QMessageBox::warning(this,"Warning","Return unsuccessfully!",QMessageBox::Yes);
                        }
                        break;
                    }
                    else{
                        a=0;
                        QMessageBox::warning(this,"Warning","Bookid error or you did not borrow this book!",QMessageBox::Yes);
                        ui->bookidEdit->clear();
                        break;
                    }
                }
            }
            if(a){
                //将该书的库存量加一,该书书号变量为bookid，变量类型为QString
                int ret=returnBook(bookid);/***0代表归还成功*/
                                           //2代表没有这本书
            }
        }
    }
}

void MainWindow::on_borrowed_clicked()
{
    ui->le_line->clear();
    ui->bookidEdit->clear();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
        db.setDatabaseName("list.db"); //数据库连接命名。
        if(!db.open()) //打开数据库
        {
            close();
        }
        else{
            QSqlQuery query(db);
            QString studentid;
            studentid=loginDlg::userid;
            query.exec("select name,id,bookid1,bookid2,bookid3 from student where id >= 0 ");
            while(query.next()){
                QString id=query.value(1).toString();
                if(id==studentid){
                    QString bookid1=query.value(2).toString(),bookid2=query.value(3).toString(),bookid3=query.value(4).toString();


                    this->model->clear();
                            this->model->setHorizontalHeaderItem(0,new QStandardItem("title"));
                            this->model->setHorizontalHeaderItem(1,new QStandardItem("writer"));
                            this->model->setHorizontalHeaderItem(2,new QStandardItem("id"));

                            this->ui->tableView->setModel(model);
                            this->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
                            bok_lines.clear();
                            readFromFile();
                            doQuery2(bookid1,bookid2,bookid3);


                }
            }
        }
}
