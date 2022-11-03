#include "mainwindowtextedit.h"
#include "ui_mainwindowtextedit.h"

MainWindowTextEdit::MainWindowTextEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindowTextEdit)
{
    ui->setupUi(this);
}

MainWindowTextEdit::~MainWindowTextEdit()
{
    delete ui;
}
