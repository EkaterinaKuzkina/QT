#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTranslator>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
explicit MainWindow(QWidget *parent = 0);
~MainWindow();

private slots:
void start();
void GenerateNextLetter();
void updateTimer();
void stop();
void secondRem30();
void secondRem20();
void secondRem15();
void getMas();
void updateFile();
void retranslator();

protected:
void keyPressEvent(QKeyEvent *event);

private:
Ui::MainWindow *ui;
QFile Recfile;
QChar currentLetter;
QTimer *timer;
int points, mean0, mean1, mean2;
int secondsRemaining, Time_mean;
QFile file;
QString Mas[3];
QTranslator translator;
QString curLang="en";
};

#endif // MAINWINDOW_H
