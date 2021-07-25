#ifndef FONTSIZE_H
#define FONTSIZE_H

#include <QDialog>

namespace Ui {
class fontSize;
}

class fontSize : public QDialog
{
    Q_OBJECT

signals:
    void fontSizeSliderValueChanged();
    void changeComfirmed(int fontSize);

private slots:
    void sliderValueChanged();
    void sliderValueChangeComfirmed();
    void sliderValueChangeCanceled();

public:
    explicit fontSize(QWidget *parent = nullptr);
    ~fontSize();
    void setSliderValue(int value);

private:
    Ui::fontSize *ui;
};

#endif // FONTSIZE_H
