#include "mainwindow.h"

#include <QLabel>
#include <QApplication>
#include <QFrame>
#include <QPlainTextEdit>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    QLabel *label;
    w.getTitle()->zoomIn(16);



    w.show();
    return app.exec();
}
