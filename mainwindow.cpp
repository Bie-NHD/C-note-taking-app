#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
QPlainTextEdit* MainWindow::getTitle()
{
    return ui->plainTextEdit;
}
MainWindow::~MainWindow()
{
    delete ui;
}

