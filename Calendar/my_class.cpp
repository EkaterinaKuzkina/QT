#include "my_class.h"

my_class::my_class(QWidget *parent) : QWidget(parent)
{
    gridLayout = new QGridLayout (this);
    gridLayout_2 = new QGridLayout (this);
    label_year= new QLabel(this);
    list = new QList<QCalendarWidget*>();
    list_lable = new QList<QLabel*>();
    paint_calendar();
}

void my_class::chooseDate(work_shift shift, QCalendarWidget *calendar){  //function for drowing sheldue on the calendar
    int year = calendar->yearShown();
    int m=calendar->monthShown();
    int days;
    QTextCharFormat format;
    QTextCharFormat format2;
    if (m==2){                     //deciding if the year is leap
        if (((year%4==0)&(year%100!=0))||(year%400==0)){
            days=29;
        }
        else days=28;
    }
    else if (((m<8)&&(m%2!=0))||(((m>7)&&(m<13)&&((m%2)==0)))){
        days=31;
    }
    else if (((m>7)&&(m<13)&&((m%2)!=0))||((m<8)&&(m%2==0))){
        days=30;
    }
    format.setBackground(Qt::lightGray);
    format2.setBackground(Qt::white);
    for (int i = 1; i < days+1;){   //painting right days
        calendar->setDateTextFormat({year,m,i},format2);
        if (flag==true){
            if (work==shift.work){
                work=0;
                flag=false;
            }
            else{
                if (backgr==1){
                    if (work==0){
                        format.setBackground(QColor(255,241,64,150));
                    }
                    if (work==1){
                        format.setBackground(QColor(70,113,213,170));
                    }
                }
                calendar->setDateTextFormat({year,m,i},format);
                work++;
                if (work==shift.work){
                    work=0;
                    flag=false;
                }
                i++;
            }
        }
        else if (flag==false){
            free++;
            if (free==shift.free){
                free=0;
                flag=true;
            }
            i++;
        }
    }
}

void my_class::clear_widget(){
    for(int i=0; i<list->size(); i++){
        gridLayout->removeWidget(list->at(i));
    }
    for(int i=0; i<list_lable->size(); i++){
        gridLayout->removeWidget(list_lable->at(i));
    }
    this->resize(0,0);

}

void my_class::paint_calendar(){  //function for painting calendar
    qDebug()<<"paint_calendar"<<endl;
    QCalendarWidget *calendar_1 = new QCalendarWidget;
    QCalendarWidget *calendar_2 = new QCalendarWidget;
    QCalendarWidget *calendar_3 = new QCalendarWidget;
    QCalendarWidget *calendar_4 = new QCalendarWidget;
    QCalendarWidget *calendar_5 = new QCalendarWidget;
    QCalendarWidget *calendar_6 = new QCalendarWidget;
    QCalendarWidget *calendar_7 = new QCalendarWidget;
    QCalendarWidget *calendar_8 = new QCalendarWidget;
    QCalendarWidget *calendar_9 = new QCalendarWidget;
    QCalendarWidget *calendar_10 = new QCalendarWidget;
    QCalendarWidget *calendar_11 = new QCalendarWidget;
    QCalendarWidget *calendar_12 = new QCalendarWidget;
    list->append(calendar_1);
    list->append(calendar_2);
    list->append(calendar_3);
    list->append(calendar_4);
    list->append(calendar_5);
    list->append(calendar_6);
    list->append(calendar_7);
    list->append(calendar_8);
    list->append(calendar_9);
    list->append(calendar_10);
    list->append(calendar_11);
    list->append(calendar_12);
    for (int i = 0; i<12; i++){
        list->at(i)->setNavigationBarVisible(false);
        list->at(i)->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    }
    QLabel *label_1= new QLabel(calendar_1);
    QLabel *label_2= new QLabel(calendar_2);
    QLabel *label_3= new QLabel(calendar_3);
    QLabel *label_4= new QLabel(calendar_4);
    QLabel *label_5= new QLabel(calendar_5);
    QLabel *label_6= new QLabel(calendar_6);
    QLabel *label_7= new QLabel(calendar_7);
    QLabel *label_8= new QLabel(calendar_8);
    QLabel *label_9= new QLabel(calendar_9);
    QLabel *label_10= new QLabel(calendar_10);
    QLabel *label_11= new QLabel(calendar_11);
    QLabel *label_12= new QLabel(calendar_12);
    label_1->setText("Январь");
    label_2->setText("Февраль");
    label_3->setText("Март");
    label_4->setText("Апрель");
    label_5->setText("Май");
    label_6->setText("Июнь");
    label_7->setText("Июль");
    label_8->setText("Август");
    label_9->setText("Сентябрь");
    label_10->setText("Октябрь");
    label_11->setText("Ноябрь");
    label_12->setText("Декабрь");

    list_lable->append(label_1);
    list_lable->append(label_2);
    list_lable->append(label_3);
    list_lable->append(label_4);
    list_lable->append(label_5);
    list_lable->append(label_6);
    list_lable->append(label_7);
    list_lable->append(label_8);
    list_lable->append(label_9);
    list_lable->append(label_10);
    list_lable->append(label_11);
    list_lable->append(label_12);
}

void my_class::orient_port(){
    this->resize(400, 600);
    this->updateGeometry();
    int m = 0;
    int l = 0;
    for (int i=0; i<8; i++){
        for (int j=0; j<3; j++){
            if (i%2==0){
                gridLayout->addWidget(list_lable->at(l), i,j, Qt::AlignCenter);
                list_lable->at(l)->setContentsMargins(0, 20, 0 ,0);
                l++;
            }
            else {
                gridLayout->addWidget(list->at(m), i, j,  Qt::AlignJustify);
                list->at(m)->setContentsMargins(10, 0, 10, 0);
                m++;
            }
        }
    }
    gridLayout->setContentsMargins(0, 10,0,20);
    this->setMaximumWidth(400);
    this->resize(400, 600);
    label_year->setGeometry(300, 10, 30, 20);
}

void my_class::orient_album(){
 this->resize(gridLayout->sizeHint().width(), 400);
    this->resize(0,0);
    int m = 0;
    int l = 0;
    for (int i=0; i<6; i++){
        for (int j=0; j<4; j++){
            if (i%2==0){
                gridLayout->addWidget(list_lable->at(l), i,j, Qt::AlignCenter);
                list_lable->at(l)->setContentsMargins(0, 20, 10 ,10);
                l++;
            }
            else {
                gridLayout->addWidget(list->at(m), i, j,  Qt::AlignJustify);
                list->at(m)->setContentsMargins(10, 0, 10, 0);
                m++;

            }
        }
    }
    gridLayout->setContentsMargins(10, 20,10,20);
    this->setMaximumHeight(400);
   this->resize(gridLayout->sizeHint().width(), 10);
    label_year->setGeometry(400, 10, 30, 20);
}

void my_class::drowCalendar(int year){  //function for drowing choosing year
    qDebug()<<"drowCalendar"<<endl;
    label_year->clear();                //clearning year's label
    label_year->setText(QString::number(year));
    flag=true;                          //true-work, false-free
    free=free_1;                        //setting number of free and work days
    work=work_1;
    for (int y=2000;  y<year+1; y++){   //loop for definition of shedule
        for (int m=0; m<12; m++){
            list->at(m)->setCurrentPage(y,m+1);
            list->at(m)->setSelectionMode(QCalendarWidget::NoSelection);
        }
        for (int i=0; i<list->size(); i++){
            chooseDate(shift, list->at(i));  //function for drowing sheldue on the calendar
        }
    }
}
void my_class::save(){  //save func
    QPixmap snapShot;
    snapShot=QWidget::grab();
    snapShot.save("/Users/ekaterinakuzkina/calen/smapshot.png");
}

void my_class::wheelEvent(QWheelEvent *event){
    event->ignore();
}
