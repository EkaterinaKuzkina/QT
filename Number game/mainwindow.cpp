
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QString>
#include <QKeyEvent>
#include <QTimer>
#include <QtGui>
#include <QTextCodec>
#include <QTextStream>
#include <QApplication>
#include <QFile>
#include <QByteArray>
#include <QTranslator>
#include <QLocale>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setStyleSheet("background-color:#ffebee");

    connect(ui->startButton, SIGNAL(clicked(bool)), this, SLOT(start()));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    connect(ui->thirtyButton, SIGNAL(clicked(bool)), this, SLOT(secondRem30()));
    connect(ui->twentyButton, SIGNAL(clicked(bool)), this, SLOT(secondRem20()));
    connect(ui->fifteenButton, SIGNAL(clicked(bool)), this, SLOT(secondRem15()));
    connect(ui->stopButton, SIGNAL(clicked(bool)), this, SLOT(stop()));
    connect(ui->LanguageButton, SIGNAL(clicked(bool)), this, SLOT(retranslator()));

    ui->stopButton->setEnabled(false);
    ui->charLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    ui->charLabel->setStyleSheet("QLabel{background-color:#ffffff}");
    ui->pointsLabel->setFrameStyle(QFrame::Panel| QFrame::Sunken);
    ui->pointsLabel->setStyleSheet("QLabel{background-color:#ffffff}");
    ui->timeLabel->setFrameStyle(QFrame::Panel| QFrame::Sunken);
    ui->timeLabel->setStyleSheet("QLabel{background-color:#ffffff}");
    ui->startButton->setStyleSheet("QPushButton{background-color:#ccb9bc}");
    ui->stopButton->setStyleSheet("QPushButton{background-color:#ccb9bc}");
    ui->thirtyButton->setStyleSheet("QPushButton{background-color:#9ea7aa}");
    ui->twentyButton->setStyleSheet("QPushButton{background-color:#9ea7aa}");
    ui->fifteenButton->setStyleSheet("QPushButton{background-color:#9ea7aa}");
    ui->LanguageButton->setStyleSheet("QPushButton{background-color:#cfd8dc}");
    getMas();
    secondsRemaining=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::secondRem20()
{
    secondsRemaining=20;
    ui->timeLabel->setText("20");
    Time_mean=secondsRemaining;
}

void MainWindow::secondRem30()
{
    secondsRemaining=30;
    ui->timeLabel->setText("30");
    Time_mean=secondsRemaining;
}

void MainWindow::secondRem15()
{
    secondsRemaining=15;
    ui->timeLabel->setText("15");
    Time_mean=secondsRemaining;
}

void MainWindow::start()
{
    if (secondsRemaining!=0)
    {
        GenerateNextLetter();
        timer->start(1000);
        ui->startButton->setEnabled(false);
        ui->stopButton->setEnabled(true);
        points=0;
    }
}

void MainWindow::GenerateNextLetter()
{
    int l = qrand() % 3;
    switch (l)
    {
        case 0:
            currentLetter = QChar('a'+ qrand() % 26);
            break;
        case 1:
            currentLetter = QChar('A'+qrand()%26);
            break;
        default:
            currentLetter = QChar('0'+qrand() % 10);
    }
    ui->charLabel->setText(currentLetter);
}

void MainWindow::updateTimer()
{
    secondsRemaining--;
    ui->timeLabel->setText(QString::number(secondsRemaining));
    if (secondsRemaining == 0)
    {
        stop();
    }
}

void MainWindow::updateFile()
{
    Mas[0].setNum(mean0);
    Mas[1].setNum(mean1);
    Mas[2].setNum(mean2);

     QFile file("/Users/ekaterinakuzkina/game_letters/my_file.txt");
     if (!file.open(QFile::WriteOnly|QFile::Truncate))
         ui->label_3->setText("error");
     QTextStream out(&file);

     out<<Mas[0]<<"\n";
     out<<Mas[1]<<"\n";
     out<<Mas[2];

     file.close();
     points=0;

     ui->pointsLabel->setText( QString::number(points));
     ui->label->setText(Mas[0]);
     ui->label_2->setText(Mas[1]);
     ui->label_3->setText(Mas[2]);
}

void MainWindow::getMas()
{
    QFile file("/Users/ekaterinakuzkina/untitled/my_file.txt");

     if (!file.exists())
     {
         ui->label_3->setText(QString("error"));
     }
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         ui->label_3->setText(QString("error"));

    QTextStream in(&file);
    int i=0;
    while (!in.atEnd())
    {
        Mas[i]=in.readLine();
        i++;
    }

    ui->label->setText(Mas[0]);
    ui->label_2->setText(Mas[1]);
    ui->label_3->setText(Mas[2]);

    file.close();
    mean0=Mas[0].toInt();
    mean1=Mas[1].toInt();
    mean2=Mas[2].toInt();

}



void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!timer->isActive())
    {
        return;
    }
    QString text=event->text();
    if (text.length()==1)
    {
        if (text == currentLetter) {
            points++;
            GenerateNextLetter();
        }
        else
        {
            if(points>0)
            points--;
        }
    }

    ui->pointsLabel->setText(QString::number(points));
}

void MainWindow::stop()
{
    timer->stop();
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);

    if (Time_mean==15)
    {
        if (points>mean0)
        {
            mean0=points;
        }
    }
    if (Time_mean==20)
    {
        if (points>mean1)
        {
            mean1=points;
        }
    }
    if (Time_mean==30)
    {
        if (points>mean2)
        {
            mean2=points;
        }
    }
    updateFile();
}

void MainWindow::retranslator()
{
    if (curLang == "en")
    {
       translator.load("/Users/ekaterinakuzkina/untitled/translateapp_ru_RU.qm");
        QApplication::instance()->installTranslator(&translator);
        ui->retranslateUi(this);
        curLang = "ru";
        ui->LanguageButton->setText("Русский");
    }
    else
    {
        translator.load("/Users/ekaterinakuzkina/untitled/translateapp_en_EN.qm");
        QApplication::instance()->installTranslator(&translator);
        ui->retranslateUi(this);
        ui->LanguageButton->setText("English");
        curLang = "en";
    }
    getMas();

}
