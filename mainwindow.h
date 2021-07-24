#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMdiArea>
#include<QTreeView>
#include<QStandardItemModel>
#include<QTextEdit>
#include"textedit.h"
#include<QFont>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
//    QTreeWidgetItem *item;  //根节点(根节点下可以有多个子结点)
//    QTreeWidgetItem *itemD; //子节点(子点下可以有多个孙子结点)
//    QTreeWidgetItem *itemW; //子节点
    QStandardItemModel*   model;
    TextEdit * textedit;
    QFont font;
    void OpenExcel(QString &filename);
    void OpenWord(QString &filename);
    void OpenPdf(QString &filename);
    void OpenPPT(QString &filename);
    void OpenTXT(QString &filename);
    void CloseOffice();
    QString getFileName(QString filename);
    ~MainWindow();

private slots:
    void on_action_open_triggered();

    void on_window_max_triggered();

    void on_window_min_triggered();

    void on_action_C_triggered();

    void on_action_create_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
