#include "register.h"
#include "ui_register.h"
#include<QSqlDatabase>
#include<QSqlRecord>
#include<QSqlQuery>
#include<QDebug>
#include<QMessageBox>
Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_clicked()
{
    this->close();
}

void Register::on_pushButton_2_clicked()
{
    if(ui->lineEdit_2->text()!=ui->lineEdit_3->text()){
        QMessageBox::critical(this,"错误","两次输入的密码不相同");
    }else{
        QSqlDatabase dataBase;
        dataBase = QSqlDatabase::addDatabase("QMYSQL");
        dataBase.setHostName("rm-bp17157up21536v6k4o.mysql.rds.aliyuncs.com");
        dataBase.setUserName("rmdjzz");
        dataBase.setPassword("RMdjzz007");
        dataBase.setDatabaseName("rmdjzz");
        dataBase.open();
        QSqlQuery query(dataBase);
        query.prepare("INSERT INTO user (username, password, savepath) "
                              "VALUES (:username, :password, :savepath)");
        query.bindValue(":username", ui->lineEdit->text());
        query.bindValue(":password", ui->lineEdit_2->text());
        query.bindValue(":savepath", "");
        query.exec();

        this->close();
    }
}
