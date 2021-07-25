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
#include<QTextStream>
#include<QTextCodec>
//using namespace std;


//QString Last_FileName;
//QString Last_FileContent;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    path = "";
    Filename = "";
    font =  QFont("宋体",12,QFont::Bold);
    this->setWindowState(Qt::WindowMaximized);
    model = new QStandardItemModel( ui-> treeView);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("目录"));
    ui -> treeView -> setModel ( model );
    ui->toolBar->setFixedHeight(100);
//    ui->toolBar->setStyleSheet("background-color:#BBFFFF");
    QStandardItem* pColumnItem = model->horizontalHeaderItem(0);
    textedit = new TextEdit();
    textedit->setFont(font);
    textedit->setTextColor(Qt::white);
    textedit->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->splitter->addWidget(textedit);
    this->textedit->hide();
    pColumnItem->setIcon( QIcon("./icon/PDF.png") );
    pColumnItem->setToolTip(QStringLiteral("这是第一列") );
//    this->setStyleSheet("QMenu::item:selected{background-color:#ff0000;");
    connect(this->fontSizeDialog, &fontSize::changeComfirmed, this, &MainWindow::setFontSize);
    connect(this->ui->action_about,SIGNAL(triggered()),this,SLOT(showInfo()));
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
    this->CloseOffice();
    ui->lineEdit->setEnabled(false);
    ui->lineEdit->setText(getFileName(filename));
    ui->axWidget->dynamicCall("SetVisible (bool Visible)","false");//不顯示窗體
    ui->axWidget->setProperty("DisplayAlerts", false);
    QString s = getFileName(filename);
    QStandardItem* itemProject = new QStandardItem(QIcon(QStringLiteral(":\\icon\\excel.png")),s);
    model->appendRow(itemProject);
    ui->axWidget->setControl(filename);
    ui->axWidget->show();

}

void MainWindow::OpenWord(QString &filename)
{
    this->textedit->hide();
    this->CloseOffice();
    ui->lineEdit->setEnabled(false);

    ui->lineEdit->setText(getFileName(filename));
    ui->axWidget->dynamicCall("SetVisible (bool Visible)","false");
    ui->axWidget->setProperty("DisplayAlerts", false);
    QString s = getFileName(filename);
    ui->axWidget->setControl(filename);
    QStandardItem* itemProject = new QStandardItem(QIcon(QStringLiteral(":\\icon\\word.png")),s);
    model->appendRow(itemProject);
    ui->axWidget->show();
}
void MainWindow::OpenPPT(QString &filename)
{
    this->textedit->hide();
    this->CloseOffice();
    ui->lineEdit->setEnabled(false);

    ui->lineEdit->setText(getFileName(filename));
    ui->axWidget->dynamicCall("SetVisible (bool Visible)","false");
    ui->axWidget->setProperty("DisplayAlerts", false);
    QString s = getFileName(filename);
    ui->axWidget->setControl(filename);
    QStandardItem* itemProject = new QStandardItem(QIcon(QStringLiteral(":\\icon\\PPT.png")),s);
    model->appendRow(itemProject);
    ui->axWidget->show();
}
void MainWindow::OpenTXT(QString &filename)
{
    ui->axWidget->hide();
    this->textedit->show();
    this->CloseOffice();

    this->textedit->setText("");
    this->textedit->setEnabled(true);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit->setText(getFileName(filename));

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QFile file(filename);

    //--打开文件成功
    if (file.open(QIODevice ::ReadOnly | QIODevice ::Text))
    {
        QTextStream textStream(&file);
        while (!textStream.atEnd())
        {
            QByteArray line = file.readLine();

                     //将读取到的行数据转换为Unicode
             QString str = codec->toUnicode(line);
             //将得到的字符设置到编辑框中显示
               this->textedit->append(str);
        }
    }
    else
    {
        QMessageBox ::information(NULL, NULL, "open file error");
    }
    QString s = getFileName(filename);
    QStandardItem* itemProject = new QStandardItem(QIcon(QStringLiteral(":\\icon\\txt.png")),s);
    model->appendRow(itemProject);
//    ui->axWidget->show();
}
void MainWindow::OpenPdf(QString &filename)
{
    this->textedit->hide();
    if(!ui->axWidget->setControl("Adobe PDF Reader"))
        QMessageBox::critical(nullptr, "Error", "沒有安裝pdf！");
    this->ui->gridLayout->addWidget(ui->axWidget);
    ui->axWidget->dynamicCall(
                "LoadFile(const QString&)",
                filename);
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
//  this->CloseOffice();
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
    if(ui->lineEdit->text()=="Untitled"){
        QString fileName = fileDialog.getSaveFileName(nullptr,"Open File","Untitled.txt","Text File(*.txt)");

        if(fileName == "")
        {
            return;
        }
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(nullptr,"error","保存失败!");
            return;
        }
        else
        {
            QTextStream textStream(&file);
            QString str = this->textedit->toPlainText();
            textStream<<str;
            QMessageBox::warning(nullptr,"tip","保存成功!");
            Filename = fileName;
            file.close();
            ui->lineEdit->setText(getFileName(fileName));
        }
    }else{
        QFile file(Filename);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(nullptr,"error","保存失败!");
            return;
        }
        else
        {
            QTextStream textStream(&file);
            QString str = this->textedit->toPlainText();
            textStream<<str;
            QMessageBox::warning(nullptr,"tip","保存成功!");
            file.close();
            ui->lineEdit->setText(getFileName(Filename));
        }
    }

}

void MainWindow::on_action_saveAs_triggered()
{

    QString filename = QFileDialog::getSaveFileName(this, tr("Save As"), Filename, tr("Image Files (*.bmp)"));
    if(!filename.isNull())
    {
    //一些处理工作，复制
            QFile::copy(Filename,filename);
    }
    else
    return;
}




void MainWindow::on_action_4_triggered()
{
  QColor color = QColorDialog::getColor(Qt::red, nullptr, "选择颜色", QColorDialog::DontUseNativeDialog);
//    QTextCursor cursor = textedit->textCursor();
//    cursor.set
  if (color.isValid())
  {
        // color.name() 获取的是 html 表示的颜色名称，比如 #ff0403
        // color.red()、color.green()、color.blue() 获取的是 RGB 对应的3色数值
//        qDebug() << color.name() << color.red() << color.green() << color.blue();
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
//    qDebug() << textedit->font();
    QFont curFont = textedit->font();
    curFont.setPointSize(fontSize);
    textedit->setFont(curFont);
//    qDebug() << textedit->font();

    this->fontSizeDialog->hide();
}
void MainWindow::showInfo()
{
    QMessageBox::about(NULL, "About", "version:1.0");
}
