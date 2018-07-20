#include "figures.h"
#include <QDebug>
#include <qmath.h>
#include <QFile>


class triangle:public figure{
public:
    triangle(){}
    triangle(QList<double> param){
        a=param[0];
        b=param[1];
        x=param[2];
        y=param[3];
        rot=param[4];
        c=sqrt(a*a+b*b);
    }
     void info() {
        qDebug()<<"triangle";
        qDebug()<<a<<" "<<b<<" "<<c<<" "<<x<<" "<<y;}
    void setXY(int a, int b){
        x+=a;
        y+=b;
    }
    QList<QString> getInfo(){
      QList<QString> list {"Tri", QString::number(a), QString::number(b), QString::number(x), QString::number(y), QString::number(rot)};
      return  list;
    }
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
    int getR(){
        return a;
    }
    figure_ID getID(){
        return Tri;
    }
    int getRot(){
        return rot;
    }
    void setRot(int rt){
        rot=rt;
    }
private:
    triangle operator=(triangle&);
    friend class figure;
    int a=0, b=0,c=0, x=0,y=0, rot;
};


class circle : public figure{
public:
    circle(){}
    circle(QList<double> param){
        r=param[0];
        x=param[1];
        y=param[2];
        rot=param[3];
    }
     void info() {
        qDebug()<<"Ckl";
        qDebug()<<r<<" "<<x<<" "<<y;
    }
    QList<QString> getInfo(){
      QList<QString> list {"Ckl", QString::number(r), QString::number(x), QString::number(y), QString::number(rot)};
      return  list;
    }
    void setXY(int a, int b){
        x+=a;
        y+=b;
    }
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
    int getR(){
        return r;
    }
    figure_ID  getID(){
        return Ckl;
    }
    int getRot(){
        return rot;
    }
    void setRot(int rt){
        rot=rt;
    }

private:
    circle operator=(circle&);
    friend class figure;
    int r, x, y, rot;
};

class square : public figure{
public:
    square(){}
    square(QList<double> param){
            a=param[0];
            x=param[1];
            y=param[2];
            rot=param[3];
        }
     void info() {
        qDebug()<<"square";
        qDebug()<<a<<" "<<x<<" "<<y;}
    void setXY(int a, int b){
        x=x+a;
        y=y+b;
    }
    QList<QString> getInfo(){
      QList<QString> list {"Sqr", QString::number(a), QString::number(x), QString::number(y), QString::number(rot)};
      return  list;
    }
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
    figure_ID  getID(){
        return Sqr;
    }
    int getR(){
        return a;
    }
    int getRot(){
        return rot;
    }
    void setRot(int rt){
        rot=rt;
    }
private:
    square operator=(square&);
    friend class figure;
    int a, x, y, rot=0;
};

figure* figCont::Create_Fig(figure_ID id, QList<double> param){
    if (id == Tri) return new triangle(param);
    else if (id == Sqr) return new square(param);
    else if (id == Ckl) return new circle(param);
    return 0;
}

void figCont:: addFig(figure_ID id, QList<double> param){
    figure * f = Create_Fig(id, param);
    flist.append(f);
}

void figCont:: clear(){
    flist.clear();
}

void figCont::delFig(int i){
    flist.removeAt(i);
    delete flist[i];
}

void figCont::moveFig(int xx, int yy, int i){
    flist[i]->setXY(xx,yy);
}

void figCont:: output(QString fileName){
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly|QFile::Truncate))
        qDebug()<<"error%";
     else{
        QTextStream out(&file);
        for (int i=0; i<flist.size(); i++)
        {
            QList<QString> Slist=flist[i]->getInfo() ;
            for(int j = 0; j<Slist.size(); j++){
                out<<Slist[j]<<" ";
            }
            out<<endl;
        }
        file.close();
    }
}

void figCont::input(QString fileName){
    QFile file(fileName);
    if (!file.exists())
        qDebug()<<"error%";
    else if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug()<<"error%";
    else{
        QTextStream in(&file);
        QString line;
        QList<QString> lst;
        while (!in.atEnd())
        {
            line = in.readLine();
            lst = line.split(" ");
            QList<double> param;
            for (int i=1; i<lst.size()-1; i++){
                param.append(lst[i].toDouble());
            }
            if (lst[0]=="Ckl")
                addFig(Ckl, param);
            else if (lst[0]=="Tri")
                addFig(Tri, param);
            else if (lst[0]=="Sqr")
                addFig(Sqr, param);
            param.clear();
        }
    file.close();
    }
}

int figCont::size(){
    return flist.size();
}

int figCont::get_X(int i){
    return flist[i]->getX();
}
int figCont::get_Y(int i){
    return flist[i]->getY();
}
int figCont::get_R(int i){
    return flist[i]->getR();
}
figure_ID figCont::get_Id(int i){
    return flist[i]->getID();
}
int figCont::get_rot(int i){
    return flist[i]->getRot();
}
void figCont::set_rot(int i, int rot){
    return flist[i]->setRot(rot);
}

bool figCont::isEmpty(){
    return flist.empty();
}

figCont::~figCont(){
    for (int i =0; i< flist.size(); i++){
        delete flist[i];
    }
    flist.clear();
}

