#include "fontsize.h"
#include "ui_fontsize.h"

fontSize::fontSize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fontSize)
{
    ui->setupUi(this);
    ui->label->setText("12");

    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &fontSize::sliderValueChanged);
    connect(ui->pushButton, &QPushButton::clicked, this, &fontSize::sliderValueChangeComfirmed);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &fontSize::sliderValueChangeCanceled);

    this->setWindowTitle("字体大小");
}

fontSize::~fontSize()
{
    delete ui;
}

void fontSize::setSliderValue(int value)
{
    ui->horizontalSlider->setValue(value);
}

void fontSize::sliderValueChanged()
{
    ui->label->setText(QString::number(ui->horizontalSlider->value()));
}

void fontSize::sliderValueChangeComfirmed()
{
    emit changeComfirmed(ui->horizontalSlider->value());
}

void fontSize::sliderValueChangeCanceled()
{
    this->hide();
}
