#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include<QSqlDatabase>
#include"mainwindow.h"
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    QSqlDatabase dataBase;
    MainWindow mainwindow;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
