#include "mainwindow.h"

#include <QLabel>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLabel *label = new QLabel("Xiao World 2");
    MainWindow w;
    w.show();
    label->show();
    return app.exec();
}