#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #C8D3D3;");
    ui->spinBox->setStyleSheet("background-color: #E9EDED;");
    ui->spinBox_2->setStyleSheet("background-color: #E9EDED;");
    ui->pushButton->setText("Открыть");
    ui->pushButton->setStyleSheet("background-color: #E9EDED; border-radius: 10px; border-style: outset; border: 2px solid #F0F0F0;");
    ui->pushButton_2->setText("Сохранить");
    ui->pushButton_2->setStyleSheet("background-color: #E9EDED; border-radius: 10px; border-style: outset; border: 2px solid #F0F0F0;");
    ui->comboBox->setStyleSheet("background-color: #E9EDED;");
    ui->comboBox_2->setStyleSheet("background-color: #E9EDED;");
    widget = new my_class;
    ui->label->setText("Год");
    ui->label_2->setText("Смена");
    ui->label_3->setText("Рабочий график");
    ui->label_4->setText("Ориентация");
    ui->spinBox->setMinimum(2000);
    ui->spinBox->setMaximum(2020);
    ui->spinBox_2->setMinimum(1);
    ui->spinBox_2->setMaximum(2);
    ui->comboBox->insertItem(0, "12 часов ночь, 12 часов день, 2 выходных");
    ui->comboBox->insertItem(1, "Сутки через двое");
    ui->comboBox->insertItem(2, "Сутки через трое");
    ui->comboBox_2->insertItem(0, "Альбомная");
    ui->comboBox_2->insertItem(1, "Портрет");

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    qDebug()<<"Here"<<endl;
    widget->show();
    widget->update();
}

void Widget::on_spinBox_valueChanged(int year_state)
{
    qDebug()<<"on_spinBox_valueChanged";
        widget->drowCalendar(year_state);
        year_temp=year_state;
}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    qDebug()<<"on_comboBox_currentIndexChanged";
    if (index==0){
        widget->shift.free=2;
        widget->shift.work=2;
        widget->backgr=1;
        widget->drowCalendar(year_temp);
    }
    if (index==1){
        widget->shift.free=2;
        widget->shift.work=1;
        widget->drowCalendar(year_temp);
    }
    if (index==2){
        widget->shift.free=3;
        widget->shift.work=1;
        widget->drowCalendar(year_temp);
    }
}

void Widget::on_pushButton_2_clicked()
{
    widget->save();
}

void Widget::on_spinBox_2_valueChanged(int arg)
{
    qDebug()<<"on_spinBox_2_valueChanged";
    if (arg==1){
        widget->free_1=0;
        widget->work_1=0;
        widget->drowCalendar(year_temp);
    }
    if (arg==2){
        widget->free_1=0;
        widget->work_1=1;
        widget->drowCalendar(year_temp);
    }
}

void Widget::on_comboBox_2_currentIndexChanged(int index)
{
    qDebug()<<"combo";
    if (index==0){
          widget->clear_widget();
        widget->orient_album();

    }
    if (index==1){
          widget->clear_widget();
        widget->orient_port();
    }
}
