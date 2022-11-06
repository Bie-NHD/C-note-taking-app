#include "setpassword.h"
#include "ui_setpassword.h"
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
            if(QString(password).isEmpty() ){
                QMessageBox::information(this, "Không có mật khẩu", "Yêu cầu nhập vào mật khẩu");
            } else {
            // Tạo truy vấn
            QSqlQuery qry;
            qry.prepare("INSERT INTO pass (password)" "VALUES (:password)");
            qry.bindValue(":password", password);

            if(qry.exec()){
                // Xét điều kiện cho dữ liệu được nhập vào
                    QMessageBox::information(this, "Đã được thêm vào", "Dữ liệu được thêm vào thành công");
                } else {
                    QMessageBox::information(this, "Không được thêm vào", "Dữ liệu không được thêm vào");
                }
            }
            hide();
}

