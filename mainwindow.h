#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMdiArea>
#include<QTreeView>
#include<QStandardItemModel>
#include<QFileSystemModel>
#include<QTextEdit>
#include"textedit.h"
#include<QFont>
#include <QColorDialog>
#include "fontsize.h"
#include<QMenu>
#include <QInputDialog>
#include"path.h"
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
//    QStandardItemModel*   model;
    MainWindow(QString user,QString pw,QWidget *parent = nullptr);
    QFileSystemModel* model;
    TextEdit * textedit;
    QFont font;
    QString savepath;
//    QString path;
    QString filepath;
    QString Filename;//当前操作文件的完整路径
    QString rightPath;
    QString username;
    QString password;
    void OpenExcel(QString &filename);
    void OpenWord(QString &filename);
    void OpenPdf(QString &filename);
    void OpenPPT(QString &filename);
    void OpenTXT(QString &filename);
    void CloseOffice();
    void setPath(QString filename);
    void updatefile();
    QString getFileName(QString filename);
    ~MainWindow();

private slots:
    void on_action_open_triggered();

    void on_window_max_triggered();

    void on_window_min_triggered();

    void on_action_C_triggered();

    void on_action_create_triggered();

    void on_action_save_triggered();

    void on_action_saveAs_triggered();

    void on_action_V_triggered();

    void on_action_X_triggered();

    void on_action_4_triggered();

    void on_action_3_triggered();

    void setFontSize(int);

    void showInfo();

    void ShowContextMenu(const QPoint& pos);

    void open();

    void rm();
    void on_searchB_clicked();

    void rmdir();

    void createfile();

    void createdir();

    void on_searchT_textChanged(const QString &arg1);


    void on_action_exit_triggered();

    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_action_newDir_triggered();

    void on_action_5_triggered();

    void on_action_2_triggered();

private:
    Ui::MainWindow *ui;
    fontSize *fontSizeDialog = new fontSize();
    QStringList defaultFileter;
    QString defaultPath;
    path* sp;
};
#endif // MAINWINDOW_H
