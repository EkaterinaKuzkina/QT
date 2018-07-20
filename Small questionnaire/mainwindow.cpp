#include "mainwindow.h"
#include "ui_mainwindow.h"

struct ans{
    QChar c;
    double time;
};
 QList<ans> answers;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("Здесь будут отображаться вопросы");
    ui->label_3->setText("Нет - A   |   Да - D");
    ui->label->setStyleSheet("QLabel { background-color : rgb(224, 224, 225); border-radius: 10px; padding: 6px }");
    ui->label_2->setStyleSheet("QLabel { background-color : rgb(224, 224, 225); border-radius: 10px; padding: 36px }");
    ui->label_3->setStyleSheet("QLabel { background-color : rgb(224, 224, 225); border-radius: 10px; padding: 26px }");
    ui->label_4->setStyleSheet("QLabel { background-color : blue}");
    input_file();
    ans a;
    a.c=' ';
    a.time=0;
    for (int i=0; i<lst.size(); i++){
        answers.push_back(a);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::out_file(){
    QFile file("/Users/ekaterinakuzkina/AI_4/out.txt");
    if (!file.open(QFile::WriteOnly))
        qDebug()<<"error";
    QTextStream out(&file);
    for (int i=0; i<answers.size(); i++){
        out<<i<<" "<< answers[i].c<<" "<< answers[i].time<<endl;
    }
    file.close();
}

void MainWindow::input_file(){
    QFile file_set("/Users/ekaterinakuzkina/AI_4/in.txt");
    if (!file_set.exists())
        qDebug()<<"error%";
    if (!file_set.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug()<<"error%%";
    QString temp;
    QTextStream in_set(&file_set);
    while (!in_set.atEnd()){
        temp = in_set.readLine();
        lst.push_back(temp);
        temp.clear();
    }
    file_set.close();
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if (event->key()==Qt::Key_Space){
        bool flag = true;
        if (qst.size()==lst.size()){
            ui->label->setText("THE END");
            out_file();   
        }
        else{
            while(flag == true){
                if (qst.empty()){
                    k = rand()%lst.size();
                    flag=false;
                }
                else{
                    k = rand()%lst.size();
                    flag=false;
                    for (int i=0; i<qst.size(); i++){
                        if (k==qst[i]){
                            flag=true;
                        }
                    }
                }
            }
            qst.push_back(k);
            ui->label->setText(lst[k]);
            start = QDateTime::currentDateTime();
        }
         ui->label_4->setStyleSheet("QLabel { background-color : blue}");
    }
    if (event->key()==Qt::Key_D){
        answers[k].c='Y';
        finish = QDateTime::currentDateTime();
        secs = start.msecsTo(finish);
        answers[k].time=secs;
        ui->label_4->setStyleSheet("QLabel { background-color : green}");
    }
    if(event->key()==Qt::Key_A){
         answers[k].c='N';
         finish = QDateTime::currentDateTime();
         secs = start.msecsTo(finish);
         answers[k].time=secs;
         ui->label_4->setStyleSheet("QLabel { background-color : green}");
    }
}
