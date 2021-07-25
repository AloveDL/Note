#include "login.h"
#include "ui_login.h"
#include"mainwindow.h"
#include<QSqlQuery>
#include<QMessageBox>
#include<QDebug>
#include<QSqlRecord>
#include"register.h"
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
    mainwindow = new MainWindow("","");
    mainwindow->show();
}

void Login::on_pushButton_2_clicked()
{
    QSqlQuery query(this->dataBase);
    QString field1 = "username=" + ui->lineEdit->text();
    QString field2 = "password=" + ui->lineEdit_2->text();
    query.prepare("select username from user  where username=? and password=?");
    query.addBindValue(ui->lineEdit->text());
    query.addBindValue(ui->lineEdit_2->text());
//    QString sql = "select savepath from user where "+field1+" and "+field2;
    query.exec();
    QSqlRecord rec = query.record();
    qDebug()<<query.size()<<"dd";
     if(query.size()==0){
        QMessageBox::critical(this,"错误","用户名或者密码错误");
     }else{

         mainwindow = new MainWindow( ui->lineEdit->text(), ui->lineEdit_2->text());
         this->close();
         mainwindow->show();
     }

}
void Login::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::gray,3));
    painter.drawLine(270,470,640,470);
    painter.drawLine(270,580,640,580);

}

void Login::on_pushButton_3_clicked()
{
    m_register = new Register();
    m_register->show();
}
