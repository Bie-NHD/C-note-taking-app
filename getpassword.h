#ifndef GETPASSWORD_H
#define GETPASSWORD_H

#include <QGroupBox>
#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>

namespace Ui {
class getpassword;
}

class getpassword : public QGroupBox
{
    Q_OBJECT

public:
    explicit getpassword(QWidget *parent = nullptr);
    ~getpassword();
    QSqlDatabase mydb;

    void connClose(){
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen(){
       mydb = QSqlDatabase::addDatabase("QSQLITE");
       // Đường dẫn là cục bộ
       mydb.setDatabaseName("D:/Study/Qt/db/mydb_2.sqlite");

       if(!mydb.open()){
           qDebug()<<("File không được mở");
                      return false;
       }else {
           qDebug()<<("File đã được mở");
                     return true;
       }
    }

    void accept();

    void reject();

private slots:
    void on_submitButton_2_clicked();

private:
    Ui::getpassword *ui;
    int iTries;
};

#endif // GETPASSWORD_H
