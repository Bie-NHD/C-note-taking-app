#include "mainwindow.h"
#include <btntextcolor.h>
//Đây là file thực thi cửa sổ chính
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QFont font( ":/Font/Poppins-Regular.ttf", 20 );

    w.show();
    return a.exec();
}
