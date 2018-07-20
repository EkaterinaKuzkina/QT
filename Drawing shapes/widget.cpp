#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(640,640);
    this->setFixedSize(640,640);

    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    ui->graphicsView->resize(600,600);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    scene->setSceneRect(0,0,this->width(),this->height()); // Устанавлвиваем размер сцены
    ui->graphicsView->setScene(scene);
    scene->setFocus();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked(){
    param='S';
    flag=true;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    for (int i =0; i<m_list.size(); i++){
        if (m_list[i]->slct==true){
            qDebug()<<m_list.size();
            m_list[i]->setSelected(false);
            m_list[i]->my_pen.setColor(Qt::black);
            m_list[i]->my_pen.setWidth(1);
        }
    }
    if (flag==true){
        MoveItem *item = new MoveItem();
        if(param=='S') item->param='S';
        if(param=='C') item->param='C';
        if(param=='T') item->param='T';
        drow(item, event->pos());
    }
}

void Widget::drow(MoveItem *item, const QPoint & pos){
    item->setPos(pos.x(),pos.y());   // Устанавлвиваем случайную позицию элемента
    if (item->param=='C'){
        f.addFig(Ckl, {60,(double)pos.x(),(double)pos.y(),0});
        item->name='C';
        item->pos_x=pos.x();
        item->pos_y=pos.y();
    }
    if (item->param=='S'){
        f.addFig(Sqr, {60,(double)pos.x(),(double)pos.y(),0});
        item->name='S';
        item->pos_x=pos.x();
        item->pos_y=pos.y();
    }
    if (item->param=='T'){
        f.addFig(Tri, {25,60,(double)pos.x(),(double)pos.y(),0});
        item->name='T';
        item->pos_x=pos.x();
        item->pos_y=pos.y();
    }
    item->setFlag(QGraphicsItem::ItemIsSelectable, true);
    scene->addItem(item);
    m_list.push_back(item);

}

void Widget::on_pushButton_2_clicked(){
    param = 'C';
    flag=true;
}

void Widget::on_pushButton_3_clicked()
{
    flag=false;
    QString file = QFileDialog::getSaveFileName(this,"Save File");
    QList<QGraphicsItem*> list = scene->items();
    for (int i=0; i<list.length()-1; i++){
        f.set_rot(i, (double)list[i]->rotation());
        }
    f.output(file);
}

void Widget::drow_from_f(){
    for (int i = 0; i<f.size(); i++){
        MoveItem *item = new MoveItem();
        if (f.get_Id(i)==Sqr){
            item->param = 'S';
        }
        if (f.get_Id(i)==Ckl){
            item->param = 'C';
        }
        if (f.get_Id(i)==Tri){
            item->param = 'T';
        }
        item->setPos(f.get_X(i),f.get_Y(i));
        item->setRotation(f.get_rot(i));
        scene->addItem(item);
    }
}

void Widget::on_pushButton_4_clicked()
{
    if (f.isEmpty()==false){
        f.clear();
    }
    QString file = QFileDialog::getOpenFileName(this,"Open File");
    if (!file.isEmpty()){
        scene->clear();
        f.input(file);
        drow_from_f();
    }
}

void Widget::on_pushButton_5_clicked(){
    param = 'T';
    flag = true;
}

void Widget::keyPressEvent(QKeyEvent *event){
    QList<QGraphicsItem*> list = scene->selectedItems();
    if (list.size()!=0){
        if (event->key()==Qt::Key_D){
            for (int i=0; i<list.size(); i++){
                list[i]->setRotation((list[i]->rotation())+5);
            }
        }
        if(event->key()==Qt::Key_A){
            for (int i=0; i<list.size(); i++){
                list[i]->setRotation((list[i]->rotation())-5);
            }
        }
    }
}

