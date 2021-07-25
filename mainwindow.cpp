#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QWidget>
#include<subwindow.h>
#include<QFileDialog>
#include<string>
#include<fstream>
#include<QMessageBox>
#include<QStandardItemModel>
#include<QFont>
#include<QFile>
#include<QDebug>
#include<QTextStream>
#include<QTextCodec>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlRecord>
#include"path.h"
MainWindow::MainWindow(QString user,QString pw,QWidget *parent)
    : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    path = "";
    Filename = "";
    username = user;
    password = pw;
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
    QString sql = "select savepath from user where "+field1+" and "+field2;
    query.exec(sql);

    QSqlRecord rec = query.record();
    query.exec(sql);
    while(query.next())
    {
        rec = query.record();
        int snocol = rec.indexOf("savepath");
        defaultPath = query.value(snocol).toString();

        qDebug()<<defaultPath;
    }
    sp = new path(username,password);
    rightPath = defaultPath;
    font =  QFont("宋体",12,QFont::Bold);
    this->setWindowState(Qt::WindowMaximized);
    model = new QFileSystemModel();
    model->setRootPath(defaultPath);
    ui -> treeView -> setModel ( model );
    ui->treeView->setRootIndex(model->index(defaultPath));
    ui->toolBar->setFixedHeight(100);
    ui->treeView->setHeaderHidden(true);
//    ui->treeView->setWindowTitle("目录");

    ui->treeView->setColumnHidden(1, true);
    ui->treeView->setColumnHidden(2, true);
    ui->treeView->setColumnHidden(3, true);
    ui->treeView->setStyleSheet("color:#FFFFFF");
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    textedit = new TextEdit();
    textedit->setFont(font);
    textedit->setTextColor(Qt::white);
    textedit->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->splitter_3->addWidget(textedit);
    this->textedit->hide();
    connect(this->fontSizeDialog, &fontSize::changeComfirmed, this, &MainWindow::setFontSize);
    connect(this->ui->action_about,SIGNAL(triggered()),this,SLOT(showInfo()));
    connect(ui->treeView, SIGNAL(customContextMenuRequested(const QPoint& )), this, SLOT(ShowContextMenu(const QPoint&)));

    this->defaultFileter << "*.txt" << "*.doc" << "*.pptx" << "*.pdf" << "*.docx" << "*.ppt" << "*.xlsx";
    model->setNameFilters(defaultFileter);
    model->setNameFilterDisables(false);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_open_triggered()
{
        QFileDialog dialog;
        dialog.setFileMode(QFileDialog::ExistingFile);
        dialog.setViewMode(QFileDialog::Detail);
        dialog.setOption(QFileDialog::ReadOnly, true);
        dialog.setWindowTitle(QString("QAXwidget操作文件"));
        dialog.setDirectory(QString("./"));
        dialog.setNameFilter(QString("所有文件(*.*);;excel(*.xlsx);;word(*.docx *.doc);;pdf(*.pdf)"));
        if (dialog.exec())
        {
        //根據文件後綴打開
            QStringList files = dialog.selectedFiles();

            for(auto filename : files)
            {
                Filename = filename;
                if(filename.endsWith(".xlsx"))
                {
                    this->OpenExcel(filename);
                }
                else if(filename.endsWith(".docx") || filename.endsWith(".doc"))
                {
                    this->OpenWord(filename);
                }  else if(filename.endsWith(".pdf"))
                {
                  this->OpenPdf(filename);
                }else if(filename.endsWith(".ppt")||filename.endsWith(".pptx")){
                    this->OpenPPT(filename);
                }else if(filename.endsWith(".txt")){
                    this->OpenTXT(filename);
                }
            }
        }
}

void MainWindow::OpenExcel(QString &filename)
{
    this->textedit->hide();
    ui->lineEdit->setEnabled(false);
    ui->lineEdit->setText(getFileName(filename));
    ui->axWidget->dynamicCall("SetVisible (bool Visible)","false");//不顯示窗體
    ui->axWidget->setProperty("DisplayAlerts", false);
    QString s = getFileName(filename);
    ui->axWidget->setControl(filename);
    ui->axWidget->show();

}

void MainWindow::OpenWord(QString &filename)
{
//    ui->axWidget->clear();
    this->textedit->hide();
    ui->lineEdit->setEnabled(false);
    ui->lineEdit->setText(getFileName(filename));
    ui->axWidget->dynamicCall("SetVisible (bool Visible)","false");
    ui->axWidget->setProperty("DisplayAlerts", false);
    QString s = getFileName(filename);
    ui->axWidget->setControl(filename);
    ui->axWidget->show();
}

void MainWindow::OpenPPT(QString &filename)
{

    this->textedit->hide();
    ui->lineEdit->setEnabled(false);

    ui->lineEdit->setText(getFileName(filename));
    ui->axWidget->dynamicCall("SetVisible (bool Visible)","false");
    ui->axWidget->setProperty("DisplayAlerts", false);
//    QString s = getFileName(filename);
    ui->axWidget->setControl(filename);
    ui->axWidget->show();
}
void MainWindow::OpenTXT(QString &filename)
{
    ui->axWidget->hide();
    this->textedit->show();
//    this->CloseOffice();
    this->textedit->setText("");
    this->textedit->setEnabled(true);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit->setText(getFileName(filename));
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QFile file(filename);

    if (file.open(QIODevice ::ReadOnly | QIODevice ::Text))
    {
        QTextStream textStream(&file);
        while (!textStream.atEnd())
        {
            QByteArray line = file.readLine();
            QString str = codec->toUnicode(line);
            this->textedit->append(str);
        }
    }else{
        QMessageBox ::information(NULL, NULL, "open file error");
    }
    QString s = getFileName(filename);

}

void MainWindow::OpenPdf(QString &filename)
{
    this->textedit->hide();
    ui->lineEdit->setEnabled(false);
    ui->lineEdit->setText(getFileName(filename));

    if(!ui->axWidget->setControl("Adobe PDF Reader"))
        QMessageBox::critical(nullptr, "Error", "沒有安裝pdf！");
    ui->axWidget->dynamicCall(
                "LoadFile(const QString&)",
                filename);
//    ui->axWidget->dynamicCall("SetVisible (bool Visible)", "false");
    ui->axWidget->show();
}

void MainWindow::CloseOffice()
{
    if(ui->axWidget)
    {
        ui->axWidget->close();
        ui->axWidget->clear();
    }
}

QString MainWindow::getFileName(QString filename){
    QString result="";
    for(int i=filename.size()-1;i>0;i--){
        if(filename[i]=='/' || filename[i]=='/'){
            break;
        }else{
            result.insert(0,filename[i]);
        }
    }
    return result;
}

void MainWindow::on_window_max_triggered()
{
    emit showMaximized();
}

void MainWindow::on_window_min_triggered()
{
    emit showMinimized();
}

void MainWindow::on_action_C_triggered()
{
  if(ui->lineEdit->hasFocus()){
      ui->lineEdit->copy();
  }if (textedit->hasFocus()){
      textedit->copy();
  }
}

void MainWindow::on_action_V_triggered()
{
  if(ui->lineEdit->hasFocus()){
      ui->lineEdit->paste();
  }if (textedit->hasFocus()){
      textedit->paste();
  }
}

void MainWindow::on_action_X_triggered()
{
  if(ui->lineEdit->hasFocus()){
      ui->lineEdit->cut();
  }if (textedit->hasFocus()){
      textedit->cut();
  }
}

void MainWindow::on_action_create_triggered()
{
    ui->axWidget->hide();
    textedit->show();
    textedit->setEnabled(true);
    textedit->setText("");
    ui->lineEdit->setEnabled(false);
    ui->lineEdit->setText("Untitled");
}

void MainWindow::on_action_save_triggered()
{
    QFileDialog fileDialog;
    if(ui->lineEdit->text().isEmpty()){
        return;
    }
    else if(ui->lineEdit->text()=="Untitled"){
        QString fileName = fileDialog.getSaveFileName(nullptr,"Open File",defaultPath,"Text File(*.txt)");

        if(fileName == "")
        {
            return;
        }
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(nullptr,"错误","保存失败!");
            return;
        }
        else
        {
            QTextStream textStream(&file);
            QString str = this->textedit->toPlainText();
            textStream<<str;
            QMessageBox::warning(nullptr,"提示","保存成功!");
            Filename = fileName;
            file.close();
            ui->lineEdit->setText(getFileName(fileName));
        }
    }else{
        QFile file(Filename);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(nullptr,"错误","保存失败!");
            return;
        }
        else
        {
            QTextStream textStream(&file);
            QString str = this->textedit->toPlainText();
            textStream<<str;
            QMessageBox::warning(nullptr,"提示","保存成功!");
            file.close();
            ui->lineEdit->setText(getFileName(Filename));
        }
    }
    ui->treeView->update();
}

void MainWindow::on_action_saveAs_triggered()
{
    if(ui->lineEdit->text().isEmpty()){
        return;
    }
    QString filename = QFileDialog::getSaveFileName(this, tr("Save As"), Filename, tr("Image Files (*.bmp)"));
    if(!filename.isNull())
    {
    //一些处理工作，复制
         QFile::copy(Filename,filename);
         ui->treeView->update();
    }
    else
      return;
}

void MainWindow::on_action_4_triggered()
{
  QColor color = QColorDialog::getColor(Qt::red, nullptr, "选择颜色", QColorDialog::DontUseNativeDialog);
  if (color.isValid())
  {
      textedit->setTextColor(QColor(color.red(),color.green(),color.blue()));
  }
}

void MainWindow::on_action_3_triggered()
{
    this->fontSizeDialog->show();
    this->fontSizeDialog->setSliderValue(textedit->font().pointSize());
}

void MainWindow::setFontSize(int fontSize)
{
    QFont curFont = textedit->font();
    curFont.setPointSize(fontSize);
    textedit->setFont(curFont);
    this->fontSizeDialog->hide();
}

void MainWindow::showInfo()
{
    QMessageBox::about(NULL, "About", "此项目用于合肥工业大学2018级大三下学期企业（科大国创）实训\n小组名：人民当家做组\n成员：孙东东，张泽浩，张伊明，束童，汪凯，张子石，朱禹帆\n版本：1.0");
}

void MainWindow::ShowContextMenu(const QPoint& pos)
{
   QModelIndex curIndex = ui->treeView->indexAt(pos);
   if(curIndex.isValid()){
       QString selectedRowTxt = ui->treeView->model()->itemData(curIndex).values()[0].toString();
       rightPath = model->filePath(curIndex);
       qDebug() << rightPath;
       if(!model->isDir(curIndex)){
               // 创建菜单
               QMenu menu;

               QAction *open = menu.addAction(tr("查看"));
               menu.addSeparator();
               QAction *del = menu.addAction(tr("删除"));
               connect(open,SIGNAL(triggered()),this,SLOT(open()));
               connect(del,SIGNAL(triggered()),this,SLOT(rm()));
               menu.exec(QCursor::pos());
       }else{
               // 创建菜单
               QMenu menu;

               QAction *createfile = menu.addAction(tr("新建文件"));
//               menu.addSeparator();
               QAction *createdir = menu.addAction(tr("新建目录"));
               QAction *deldir = menu.addAction(tr("删除目录"));

               connect(createfile,SIGNAL(triggered()),this,SLOT(createfile()));
               connect(createdir,SIGNAL(triggered()),this,SLOT(createdir()));
               connect(deldir,SIGNAL(triggered()),this,SLOT(rmdir()));
               menu.exec(QCursor::pos());
       }
    }else {
       QMenu menu;

       QAction *createfile = menu.addAction(tr("新建文件"));
       QAction *createdir = menu.addAction(tr("新建目录"));

       connect(createfile,SIGNAL(triggered()),this,SLOT(createfile()));
       connect(createdir,SIGNAL(triggered()),this,SLOT(createdir()));
       menu.exec(QCursor::pos());
    }
}

void MainWindow::open(){
    QFile file(rightPath);
    Filename = file.fileName();
    if(rightPath.endsWith(".xlsx"))
    {
        this->OpenExcel(rightPath);
    }
    else if(rightPath.endsWith(".docx") || rightPath.endsWith(".doc"))
    {
        this->OpenWord(rightPath);
    }  else if(rightPath.endsWith(".pdf"))
    {
      this->OpenPdf(rightPath);
    }else if(rightPath.endsWith(".ppt")||rightPath.endsWith(".pptx")){
        this->OpenPPT(rightPath);
    }else if(rightPath.endsWith(".txt")){
        this->OpenTXT(rightPath);
    }
    rightPath = defaultPath;
}

void MainWindow::rm(){
    QFile file(rightPath);
    if(file.exists()){
        file.remove();
        ui->treeView->update();
    }

}

void MainWindow::on_searchB_clicked()
{
    if(ui->searchT->text()==""){
         this->updatefile();
    }else{
    QString filter = ui->searchT->text();
    qDebug() << filter;
    QStringList filters;
    filters <<  "*" + filter + "*.txt" << "*" + filter + "*.doc" << "*" + filter +"*.pptx" << "*" + filter + "*.pdf" << "*" + filter + "*.docx" << "*" + filter + "*.ppt" << "*" + filter + "*.xlsx";
    model->setNameFilterDisables(false);
    model->setNameFilters(filters);

    ui->treeView->update();
    }
}

void MainWindow::createfile(){
  QString filename = QInputDialog::getText(this,"新建文件","请输入文件名");
  QFile file(rightPath + "\\" + filename + ".txt");
  qDebug() << file.fileName();
  if(!file.exists()){
//      file.remove();
      file.open(QIODevice::WriteOnly);
      file.close();
  }else{
    QMessageBox::critical(this,"错误","文件已存在");
  }
  rightPath = defaultPath;
}

void MainWindow::createdir(){
  QString filename = QInputDialog::getText(this,"新建目录","请输入目录名");
  QDir dir(rightPath + "\\" + filename);
  qDebug() << dir.currentPath();
  if(!dir.exists()){
//      file.remove();
      dir.mkdir(dir.path());

  }else{
    QMessageBox::critical(this,"错误","目录已存在");
  }
  rightPath = defaultPath;
}

void MainWindow::rmdir(){
  QDir dir(rightPath);
//  qDebug() << dir.currentPath();
  if(dir.exists()){
//      file.remove();
      dir.rmdir(dir.path());
  }else{
    QMessageBox::critical(this,"错误","目录不存在");
  }
  rightPath = defaultPath;
}

void MainWindow::on_searchT_textChanged(const QString &arg1)
{
  QString filter = ui->searchT->text();
  qDebug() << filter;
  QStringList filters;
  filters <<  "*" + filter + "*.txt" << "*" + filter + "*.doc" << "*" + filter +"*.pptx" << "*" + filter + "*.pdf" << "*" + filter + "*.docx" << "*" + filter + "*.ppt" << "*" + filter + "*.xlsx";
  model->setNameFilterDisables(false);
  model->setNameFilters(filters);
  ui->treeView->update();
}

void MainWindow::on_action_exit_triggered()
{
    exit(1);
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
  QModelIndex curIndex = index;
  if(curIndex.isValid()){
      QString selectedRowTxt = ui->treeView->model()->itemData(curIndex).values()[0].toString();
      rightPath = model->filePath(curIndex);
      qDebug() << rightPath;
      if(!model->isDir(curIndex)){
          QFile file(rightPath);
          Filename = file.fileName();
          if(rightPath.endsWith(".xlsx"))
          {
              this->OpenExcel(rightPath);
          }
          else if(rightPath.endsWith(".docx") || rightPath.endsWith(".doc"))
          {
              this->OpenWord(rightPath);
          }  else if(rightPath.endsWith(".pdf"))
          {
            this->OpenPdf(rightPath);
          }else if(rightPath.endsWith(".ppt")||rightPath.endsWith(".pptx")){
              this->OpenPPT(rightPath);
          }else if(rightPath.endsWith(".txt")){
              this->OpenTXT(rightPath);
          }
          rightPath = defaultPath;
      }
  }
}


void MainWindow::on_action_newDir_triggered()
{
  QString filename = QInputDialog::getText(this,"新建目录","请输入目录名");
  QDir dir(defaultPath + "\\" + filename);
//  qDebug() << dir.currentPath();
  if(!dir.exists()){
//      file.remove();
      dir.mkdir(dir.path());
  }else{
    QMessageBox::critical(this,"错误","目录已存在");
  }
  rightPath = defaultPath;
}

void MainWindow::setPath(QString filename){
    defaultPath = filename;
    rightPath = filename;
}

void MainWindow::on_action_5_triggered()
{
    sp->setWindowTitle("填写路径");
    sp->show();
}

void MainWindow::updatefile(){
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
    QString sql = "select savepath from user where "+field1+" and "+field2;
    query.exec(sql);

    QSqlRecord rec = query.record();
    query.exec(sql);
    while(query.next())
    {
        rec = query.record();
        int snocol = rec.indexOf("savepath");
        defaultPath = query.value(snocol).toString();

        qDebug()<<defaultPath;
    }
    model->setRootPath(defaultPath);
    ui -> treeView -> setModel ( model );
    ui->treeView->setRootIndex(model->index(defaultPath));
    rightPath = defaultPath;
}

void MainWindow::on_action_2_triggered()
{
    this->updatefile();
}
