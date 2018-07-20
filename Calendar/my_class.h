#ifndef MY_CLASS_H
#define MY_CLASS_H

#include <QObject>
#include <QWidget>
#include <QCalendarWidget>
#include <QGridLayout>
#include <QDebug>
#include <QListWidget>
#include <QLabel>
#include <QTextCharFormat>
#include <QWheelEvent>


struct work_shift{
    int work=2;
    int free=2;
};

class my_class : public QWidget
{
    Q_OBJECT
public:
    explicit my_class(QWidget *parent = 0);
    void chooseDate(work_shift shift, QCalendarWidget *calendar);
    void drowCalendar(int);
    void paint_calendar();
    void clear_widget();
    void orient_album();
    void orient_port();
    work_shift shift;
    int free_1=0, work_1=0, free=0, work=0, orient=0;
    void save();
    int backgr=0;
private:
    bool flag;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QList<QCalendarWidget*> *list;
    QList<QLabel*> *list_lable;
    QLabel *label_year;
    void wheelEvent(QWheelEvent *event);
signals:

public slots:
};




#endif // MY_CLASS_H
