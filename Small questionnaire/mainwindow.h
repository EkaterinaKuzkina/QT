#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QKeyEvent>
#include <QLabel>
#include <QTimer>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<QString> lst;
    QList<int> qst;
    QDateTime start, finish;
    int k, secs;
    void out_file();
    void input_file();
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
