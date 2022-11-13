#include "setpassword.h"
#include "ui_setpassword.h"
#include <mainwindow.h>

//Đây là file tạo khóa note

setpassword::setpassword(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::setpassword)
{
    ui->setupUi(this);
    ui->password->setPlaceholderText("Nhập mật khẩu để khóa note của bạn");
}

setpassword::~setpassword()
{
    delete ui;
}


void setpassword::on_submitButton_clicked()
{
    QString password = ui->password->text();
    connOpen();
            if(!connOpen()){
                 QMessageBox::information(this, "Không mở được cơ sở dữ liệu", "Dữ liệu không được thêm vào");
            }
            if(QString(password).isEmpty()){
                QMessageBox::information(this, "Không có mật khẩu", "Yêu cầu nhập vào mật khẩu");
            }else{
                // Tạo truy vấn
                QSqlQuery qry;
                qry.prepare("INSERT INTO password (password)" "VALUES (:password)");
                qry.bindValue(":password", password);

                if(qry.exec()){
                    // Xét điều kiện cho dữ liệu được nhập vào
                    QMessageBox::information(this, "Đã thêm mật khẩu", "Mật khẩu được cài đặt thành công");
                    hide();
                }else{
                    QMessageBox::information(this, "Không thành công", "Mật khẩu được cài đặt vào không thành công");
                }
            }
}

