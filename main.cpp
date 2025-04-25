#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // QTranslator qtTranslator;
    // if (qtTranslator.load("qt_ru", QLibraryInfo::path(QLibraryInfo::TranslationsPath))) {
    //     a.installTranslator(&qtTranslator);
    // }

    MainWindow w;
    w.show();
    return a.exec();
}
