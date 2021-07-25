#include "path.h"
#include "ui_path.h"
#include<QSqlDatabase>
#include<QSqlRecord>
#include<QSqlQuery>
#include<QDebug>
path::path(QString user,QString pw,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::path)
{
    ui->setupUi(this);
    username = user;
    password = pw;
}

path::~path()
{
    delete ui;
}

void path::on_pushButton_clicked()
{
    QSqlDatabase dataBase;
    dataBase = QSqlDatabase::addDatabase("QMYSQL");
    dataBase.setHostName("rm-bp17157up21536v6k4o.mysql.rds.aliyuncs.com");
    dataBase.setUserName("rmdjzz");
    dataBase.setPassword("RMdjzz007");
    dataBase.setDatabaseName("rmdjzz");
    dataBase.open();
    QSqlQuery query(dataBase);
    QString field1 = "username=" + username;
    QString field2 = "password=" + password;
    query.prepare("update user set savepath=? where username=?");
    query.addBindValue(ui->lineEdit->text());
    query.addBindValue(username);
    query.exec();
    this->update();
    this->close();
}
