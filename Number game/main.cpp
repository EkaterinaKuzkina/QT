#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QTextCodec>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QTranslator transApp;
    transApp.load("translateapp_" + QLocale::system().name());
    a.installTranslator(&transApp);

    return a.exec();
}
