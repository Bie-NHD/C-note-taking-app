#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QSql>
#include <QtSql>
#include <QSqlDatabase>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //Create a database
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("127.0.0.1");
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("note");
    //Received data
    if(database.open()) {

        QString password = ui->password->text();


    //Query

    QSqlQuery qry;
    qry.prepare("INSERT INTO password (password)"
                "VALUES (:password)");

    qry.bindValue(":password", password);

    if(qry.exec()) {

        QMessageBox::information(this, "Inserted", "Data inserted successfully");

    } else {

        QMessageBox::information(this, "Not Inserted", "Data inserted unsuccessfully");

    }

    } else {

        QMessageBox::information(this, "Not Connected", "Data is not connected");

    }

}

