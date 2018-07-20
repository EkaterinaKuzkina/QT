#ifndef FIGURES_H
#define FIGURES_H

#include "figures_global.h"
#include<QList>

/*class FIGURESSHARED_EXPORT Figures
{

public:
    Figures();
};*/
enum figure_ID { Tri, Sqr, Ckl};

class FIGURESSHARED_EXPORT figure{
    public:
public:
    figure() {}
    virtual void info()=0;
    virtual void set(QList<int>){}
    virtual void setXY(int, int){}
    virtual int getX()=0;
    virtual int getY()=0;
    virtual int getR()=0;
    virtual int getRot()=0;
    virtual void setRot(int){}
    virtual figure_ID getID()=0;
    virtual QList<QString> getInfo()=0;
    virtual ~figure() {}
    };

class FIGURESSHARED_EXPORT figCont{
    QList<figure*> flist;
public:
    void addFig(figure_ID id,  QList<double>);
    void delFig(int);
    void moveFig(int, int, int);
    void output(QString);
    void input(QString);
    int size();
    int get_X(int);
    int get_Y(int);
    int get_R(int);
    int get_rot(int);
    void set_rot(int, int);
    bool isEmpty();
    void clear();
    figure_ID get_Id(int);
    figure* Create_Fig(figure_ID, QList<double>);
    ~figCont();
};
#endif // FIGURES_H
