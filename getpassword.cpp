#include "getpassword.h"
#include "ui_getpassword.h"
#include <mainwindow.h>

// Đây là file mở khóa note

getpassword::getpassword(QWidget *parent) : QGroupBox(parent), ui(new Ui::getpassword)
{
    ui->setupUi(this);
    ui->password_2->setPlaceholderText("Nhập mật khẩu để mở khóa note của bạn");
    iTries = 1;
}

// Cho ra thông báo mở khóa thành công và đóng frame lại
void getpassword::accept(){
    QMessageBox::information(this, "Thành công", "Mở khóa thành công");
    hide();
}

// Nếu nhập sai thì thực thi hàm này
void getpassword::reject(){
    QMessageBox::information(this, "Thất bại", "Mở khóa thất bại");
    ui->label_3->setText(QString("Attempt %1 of 3").arg(QString::number(iTries)));
    ui->password_2->clear();
    iTries++;
    // Nhập sai quá 3 lần thì sẽ không cho nhập nữa và sẽ hide nút submit, tính toán thời gian cho lần nhập kế tiếp
    if(iTries > 3){
        QMessageBox::information(this, "Mở khóa failed", "Số lần nhập đã đạt tối đa");
        // Khối lệnh thực thi sẽ hide nút submit và không cho người dùng nhập nữa, phải đợi một khoảng thời gian mới đc nhập và submit lại
        QTimer *timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(update()));
            ui->submitButton_2->hide();
            // Sau 5000 miliseconds tương đương 5s thì nút submit sẽ xuất hiện trở lại
            QTimer::singleShot(5000, ui->submitButton_2, SLOT(show()));
    }
}

getpassword::~getpassword()
{
    delete ui;
}

void getpassword::on_submitButton_2_clicked()
{         
        connOpen();
        QString password = ui->password_2->text();

        //Tạo truy vấn
        QSqlQuery query(QSqlDatabase::database("My Connect"));
        query.prepare(QString("SELECT * FROM password WHERE password = :password"));

        // Gắn dữ liệu vào cột bên database
        query.bindValue(":password", password);
        query.exec();

        //Truy vấn
        if(query.next()){
            // Kiểm tra dữ liệu nếu đúng thì thực thi hàm accept()
            accept();
        }else{
            // Kiểm tra dữ liệu nếu sai thì thực thi hàm reject()
            reject();
        }
}


