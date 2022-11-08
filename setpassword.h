#ifndef SETPASSWORD_H
#define SETPASSWORD_H

#include <QGroupBox>
#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>

namespace Ui {
class setpassword;
}

class setpassword : public QGroupBox
{
    Q_OBJECT

public:
    explicit setpassword(QWidget *parent = nullptr);
    ~setpassword();

    QSqlDatabase mydb;

    void connClose(){
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen(){
       mydb=QSqlDatabase::addDatabase("QSQLITE");
       // Đường dẫn là cục bộ
       mydb.setDatabaseName("D:/Study/Qt/db/mydb_2.sqlite");

       if(!mydb.open()){
           qDebug()<<("File not opened");
                      return false;
       }else {
           qDebug()<<("File opened");
                     return true;
       }
    }

private slots:
    void on_submitButton_clicked();

private:
    Ui::setpassword *ui;
};

#endif // SETPASSWORD_H
