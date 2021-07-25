#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include<QSqlDatabase>
#include"mainwindow.h"
#include "QPainter"
#include "QPaintEvent"
#include"register.h"
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    MainWindow* mainwindow;
    QSqlDatabase dataBase;
    Register* m_register;
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
