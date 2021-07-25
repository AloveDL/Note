#ifndef PATH_H
#define PATH_H

#include <QWidget>

namespace Ui {
class path;
}

class path : public QWidget
{
    Q_OBJECT

public:
    explicit path(QString user,QString pw,QWidget *parent = nullptr);
    ~path();

private slots:
    void on_pushButton_clicked();

private:
    Ui::path *ui;
    QString username;
    QString password;
    QString savepath;
};

#endif // PATH_H
