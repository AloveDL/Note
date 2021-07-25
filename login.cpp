#include "login.h"
#include "ui_login.h"
#include"mainwindow.h"
#include<QSqlQuery>
#include<QDebug>
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    dataBase = QSqlDatabase::addDatabase("QMYSQL");
    dataBase.setHostName("rm-bp17157up21536v6k4o.mysql.rds.aliyuncs.com");
    dataBase.setUserName("rmdjzz");
    dataBase.setPassword("RMdjzz007");
    dataBase.setDatabaseName("rmdjzz");
    dataBase.open();
    bool ok=dataBase.open();
        if(ok)
        {
          qDebug()<<"open database success";
        }
        else
        {
          qDebug()<<"error open database because";
        }

}
Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    this->hide();
    mainwindow.show();
}

void Login::on_pushButton_2_clicked()
{
    QSqlQuery query(this->dataBase);
    QString field1 = "username=" + ui->lineEdit->text();
    QString field2 = "password=" + ui->lineEdit_2->text();
    QString sql = "select * from user where "+field1+","+field2;
//    QString sql=QString(filed);
     query.exec(sql);
     qDebug()<<query.exec(sql);
     if(query.numRowsAffected()==0){

     }else{
         this->hide();
         mainwindow.show();
     }

}
