#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "my_class.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

    void on_spinBox_2_valueChanged(int arg1);

    void on_comboBox_2_currentIndexChanged(int index);

private:
    Ui::Widget *ui;
    my_class *widget;
    int year_temp;
};

#endif // WIDGET_H
