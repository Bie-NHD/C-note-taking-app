#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QFileInfo>
#include <QMessageBox>
#include <QPushButton>
#include<QLineEdit>
#include<QPlainTextEdit>
#include<QTimer>
#include<QComboBox>
#include<QGroupBox>
#include<QGridLayout>
#include<QCalendarWidget>
#include<QLabel>
#include<QCheckBox>

#include <setpassword.h>
#include <getpassword.h>
#include <paintwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void onnameclicked();
public:
    static int x;
    static QString pro_user;
    QSqlDatabase mydb;
    void connClose(){

        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen(){
        mydb=QSqlDatabase::addDatabase("QSQLITE");
       mydb.setDatabaseName("C:/Users/tminh/OneDrive/Máy tính/Db/mydb.sqlite");

       if(!mydb.open()){
           qDebug()<<("File not opened");
                      return false;
       }else {
           qDebug()<<("File opened");
                     return true;
       }
    }


public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_btnTextColor_clicked();

    void on_btnUndo_clicked();

    void on_btnRedo_clicked();

    void on_toolButton_bold_clicked();

    void on_toolButton_italic_clicked();

    void on_toolButton_underline_clicked();

    void on_toolButton_plus_clicked();


//    void myfunction();

//    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);
    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    setpassword *Setpassword;
    getpassword *Getpassword;
    PaintWindow *paintwindow;

};
#endif // MAINWINDOW_H
