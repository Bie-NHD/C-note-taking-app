#include "mainwindow.h"

#include <QLabel>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLabel *label = new QLabel("Bonjour World");
    MainWindow w;
    w.show();
    label->show();
    return app.exec();
}
