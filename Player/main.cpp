#include "mainwindow.h"
#include <QApplication>
#include "soundplayer.h"
#include <QListWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    soundplayer soundPlayer;
    soundPlayer.resize(320,75);
    soundPlayer.show();

   // MainWindow w;
    //w.show();

    return a.exec();
}
