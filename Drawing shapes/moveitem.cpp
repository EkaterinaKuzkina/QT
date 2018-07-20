#include "moveitem.h"

MoveItem::MoveItem(QObject *parent) :
    QObject(parent), QGraphicsItem(){
}

MoveItem::~MoveItem(){
}

QRectF MoveItem::boundingRect() const
{
    return QRectF (-30,-30,60,60);
}

QPainterPath MoveItem::shape() const {
    QPainterPath path;
    if (this->name=='C'){
        path.addEllipse(-30, -30, 60, 60);
    }
    if (this->name=='S'){
        path.addRect(-30, -30, 60, 60);
    }
    if (this->name=='T'){
        QPolygon polygon;   // Используем класс полигона, чтобы отрисовать треугольник
        polygon << QPoint(-30 ,-30) << QPoint(30,-30) << QPoint(30,30);
        path.addPolygon(polygon);
    }
    return path;
}

void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(param=='S'){
        painter->setPen(my_pen);
        painter->setBrush(Qt::green);
        prepareGeometryChange();
        painter->drawRect(-30,-30,60,60);
        this->setFlag(ItemIsSelectable, true);
        this->name='S';
    }
    if(param=='C'){
        painter->setPen(my_pen);
        painter->setBrush(Qt::blue);
        prepareGeometryChange();
        painter->drawEllipse(-30,-30,60,60);
        this->setFlag(ItemIsSelectable, true);
        this->name='C';
    }
    if(param=='T'){
        QPolygon polygon;   // Используем класс полигона, чтобы отрисовать треугольник
        polygon << QPoint(-30 ,-30) << QPoint(30,-30) << QPoint(30,30);
        painter->setPen(my_pen);
        painter->setBrush(Qt::red);     // Устанавливаем кисть, которой будем отрисовывать объект
        prepareGeometryChange();
        painter->drawPolygon(polygon);
        this->setFlag(ItemIsSelectable, true);
        this->name='T';
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
    this->setPos(mapToScene(event->pos()));
}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{  
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    prepareGeometryChange();
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}
void MoveItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    if (isSelected()){
        prepareGeometryChange();
        this->setSelected(false);
        my_pen.setColor(Qt::black);
        my_pen.setWidth(1);
        slct=false;

    }
    else  {
        prepareGeometryChange();
        my_pen.setColor(Qt::cyan);
        my_pen.setWidth(3);
        this->setSelected(true);
        slct=true;
    }
    Q_UNUSED(event);
}

