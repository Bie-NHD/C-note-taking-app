#include "getpassword.h"
#include "ui_getpassword.h"
#include <mainwindow.h>

//Đây là file mở khóa note

getpassword::getpassword(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::getpassword)
{
    ui->setupUi(this);
    ui->password_2->setPlaceholderText("Nhập mật khẩu để mở khóa note của bạn");
}

getpassword::~getpassword()
{
    delete ui;
}

void getpassword::on_submitButton_2_clicked()
{   
        connOpen();
        QString password = ui->password_2->text();

        // Tạo truy vấn
        QSqlQuery query(QSqlDatabase::database("My Connect"));
        query.prepare(QString("SELECT * FROM password WHERE password = :password"));

        // Gắn dữ liệu vào cột bên database
        query.bindValue(":password", password);
        query.exec();

        //Truy vấn
        if(query.next()){
        // Kiểm tra dữ liệu
            QMessageBox::information(this, "Thành công", "Đăng nhập thành công");
        }else{
            QMessageBox::information(this, "Thất bại", "Đăng nhập thất bại");
        }
        hide();
}

