#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <moveitem.h>
#include <QFileDialog>
#include <QGraphicsSceneMouseEvent>

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
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    QList <MoveItem*> m_list;
    void drow(MoveItem *,const QPoint &);
    void drow_from_f();
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    bool flag;
    figCont f;
    char param;
    double x, y;
};

#endif // WIDGET_H
