#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>
#include<QTextEdit>
class subwindow : public QTextEdit
{
    Q_OBJECT
public:
    explicit subwindow(QWidget *parent = nullptr);

signals:

};

#endif // SUBWINDOW_H
