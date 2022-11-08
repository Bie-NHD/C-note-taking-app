#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setpassword.h"
#include "btntextcolor.h"
#include "scribblearea.h"

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QGridLayout>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QFrame>
#include <QSqlRecord>
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QColor>
#include <QColorDialog>
#include<QFontDialog>
#include<QFont>
#include<QToolButton>
#include<QDateTime>
#include<QDateTimeEdit>
#include<QPushButton>
#include<QToolButton>

//Ứng dụng ghi chú được hỗ trợ bởi trình tạo giao diện Qt xài ngôn ngữ Qmake với thiên hướng giống ngôn ngữ C++ và sự hỗ trợ của database Sqlite3 ( và 1 số hình ảnh, fonts khác )
//Mỗi một form thiết kế của Qt sẽ cung cấp 3 loại file ( .h, .cpp, .ui ) được liên kết. Trong đó file .ui có format theo XML có thiên hướng giống html, css.. sẽ bao gồm những thành
// phần được đặt tên theo từng nút, khung đặc biệt ( 1 số chưa được đổi tên còn để ở dạng mặc định như "pushbutton", nhưng có chú thích ở phía trên )

QString MainWindow:: pro_user;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Mở database

    connOpen();

    //Tạo modal...
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQueryModel *modal1 = new QSqlQueryModel();
    QSqlQueryModel *modal2 = new QSqlQueryModel();

    //Tạo query...
    QSqlQuery *qry = new QSqlQuery(mydb);
    QSqlQuery *qry1 = new QSqlQuery(mydb);
    QSqlQuery *qry2 = new QSqlQuery(mydb);

    //Chọn data gắn vào...
    qry->prepare("select id from note1");
    qry1->prepare("select title from note1");
    qry2->prepare("select content from note1");

    //Thực hiện query...
    qry->exec();
    qry1->exec();
    qry2->exec();

    //Gắn query với modal...
    modal->setQuery(*qry);
    modal1->setQuery(*qry1);
    modal2->setQuery(*qry2);

    //Tạo khung danh sách note...
    QGridLayout *lay = new QGridLayout(this);
    QPushButton *content[2000];
    //Thêm các thành phần vào khu vực kéo chuột (scrollArea)
    for(int j=0; j<=modal1->rowCount()-1; j++)
    {
    QString id=modal->record(j).value(0).toString();//(id)
    QString title=modal1->record(j).value(0).toString();//(title)
    QString contentString=modal2->record(j).value(0).toString();//(content)

    //Biến string thành giao diện
    content[j] = new QPushButton(contentString);
    content[j]->setProperty("id",id);
    QLabel *lab = new QLabel("Content: "+contentString+".");
    lab->setStyleSheet("color:white");

    //Chia từng note trong danh sách ra bằng đường kẻ trắng
    QFrame *line;
    line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("background:white");

    //Nổi hiệu ứng khi rê chuột tới cho nút title
    content[j]->setObjectName("btnName_1");
    content[j]->setStyleSheet(
    "   QPushButton#btnName_1 {"
    "     background:transparent; Text-align:left;font-family:century gothic;font-size:18px; color:orange;"
    " }"
    " QPushButton#btnName_1:hover {"
    "     color: yellow;font-size:25px;"
    " }");

    //Gắn giao diện với từng layout đã tạo
    lab->setStyleSheet("background:transparent; Text-align:left;font-family:century gothic;font-size:18px; color:white");
    lay->addWidget(content[j]);
    lay->addWidget(lab);
    lay->addWidget(line);

     //Nhấn title sẽ thực hiện hàm onnameclicked
     connect(content[j],SIGNAL(clicked()),this,SLOT(onnameclicked()));
     //Bỏ layout vào khu vực kéo (scrollArea)
     ui->scrollContents->setLayout(lay);
    }
    connClose();
    //Tắt mở các khung xung quanh
    ui->frame_2->hide();
    ui->frame_3->show();
}
//Hàm hủy
MainWindow::~MainWindow()
{
    delete ui;
}

QString contentText;
//Gắn x bên header = 0
int MainWindow::x=0;
QPushButton *pButton[50];
QString currentID;


void MainWindow::onnameclicked()
{
    //Hiện khung note
    ui->frame_2->show();

    //Khởi tạo nút đã tạo
    pButton[x] = new QPushButton;

    //Nhận tên của nút và gán nó vào pButton[x]
    pButton[x] = qobject_cast<QPushButton*>(sender());

    //Mỗi lần nhấn nút khác thì nút vừa nhấn trước đó sẽ quay về stylesheet mặc định như bên dưới
    if(x>0)
    {

        pButton[x-1]->setObjectName("btnName_1");
        pButton[x-1]->setStyleSheet("   QPushButton#btnName_1 {"
                                    "     background:transparent; Text-align:left;font-family:century gothic;font-size:18px; color:orange;"
                                    " }"
                                    " QPushButton#btnName_1:hover {"
                                    "     color: yellow;font-size:25px;"
                                    " }");
    }


    //stylesheet cho nút để nhấn
    pButton[x]->setStyleSheet("color: yellow;font-size:25px;Text-align:left;font-family:century gothic");
    //Nhận giá trị id đồng thời
    QString idText = pButton[x]->property("id").value<QString>();
    currentID = idText;
    connOpen();
    QSqlQuery qry;
    //Gọi dữ liệu nội dung note
    qry.prepare("select content from note1 where id='"+idText+"'");

    if(!qry.exec()) return ;
    qry.next();
    QString contentText = qry.value(0).toString();
    ui->content->setText(contentText);
    ui->content->setStyleSheet("font-family:century gothic;background:transparent;font-size:20px;color:orange;Text-align:center");
    ui->title->setStyleSheet("font-family:century gothic;background:transparent;font-size:20px;color:orange;Text-align:center");

    //Gọi dữ liệu tiêu đề note
    qry.prepare("select title from note1 where id='"+idText+"'");
    if(!qry.exec()) return ;
    qry.next();
    QString titleText = qry.value(0).toString();
    ui->title->setPlainText(titleText);

    x++;
    connClose();
}

//Tìm kiếm
void MainWindow::on_pushButton_clicked()
{
    connOpen();
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQueryModel *modal1 = new QSqlQueryModel();
    QSqlQueryModel *modal2 = new QSqlQueryModel();

    QSqlQuery *qry = new QSqlQuery(mydb);
    QSqlQuery *qry1 = new QSqlQuery(mydb);
    QSqlQuery *qry2 = new QSqlQuery(mydb);

    qry->prepare("select id from note1");
    qry1->prepare("select title from note1");
    qry2->prepare("select content from note1");

    qry->exec();
    qry1->exec();
    qry2->exec();

    modal->setQuery(*qry);
    modal1->setQuery(*qry1);
    modal2->setQuery(*qry2);

    QVBoxLayout *lay  = new QVBoxLayout(this);
    QString s = ui->lineEdit->text();
    QPushButton *label;
    QGridLayout *lay1 = new QGridLayout(this);
    QPushButton *content[2000];
    for(int j=0; j<=modal1->rowCount(); j++)
    {
        QString id = modal->record(j).value(0).toString();
        QString title = modal1->record(j).value(0).toString();
        QString contentText = modal2->record(j).value(0).toString();


            //Kiểm tra xem note có đang trống hay ko
            if(QString(s).isEmpty() ){
            content[j] = new QPushButton(contentText);
            content[j]->setProperty("id",id);
            QLabel *lab = new QLabel("Content: "+contentText+".");
            lab->setStyleSheet("color:white");

            //Chia từng note trong danh sách bằng đường kẻ trắng
            QFrame *line;
            line = new QFrame();
            line->setFrameShape(QFrame::HLine);
            line->setFrameShadow(QFrame::Sunken);
            line->setStyleSheet("background:white");

            //Nổi hiệu ứng khi rê chuột tới cho nút title
            content[j]->setObjectName("btnName_1");
            content[j]->setStyleSheet(
            "   QPushButton#btnName_1 {"
            "     background:transparent; Text-align:left;font-family:century gothic;font-size:18px; color:orange;"
            " }"
            " QPushButton#btnName_1:hover {"
            "     color: yellow;font-size:25px;"
            " }");

            //Gắn giao diện với từng layout đã tạo
            lab->setStyleSheet("background:transparent; Text-align:left;font-family:century gothic;font-size:18px; color:white");
            lay1->addWidget(content[j]);
            lay1->addWidget(lab);
            lay1->addWidget(line);
             //Nhấn title sẽ thực hiện hàm onnameclicked ( tạo kết nối signals & slots trong Qt )
             connect(content[j],SIGNAL(clicked()),this,SLOT(onnameclicked()));
             //Bỏ layout vào khu vực kéo (scrollArea)
             ui->scrollContents->setLayout(lay1);
            }

        int x = QString::compare(s, title, Qt::CaseInsensitive);
        //Khớp kết quả
        if(x == 0)
        {
            //clearing previous layout
            if ( ui->scrollContents->layout() != NULL )
            {
                QLayoutItem *item;
                while ( ( item = ui->scrollContents->layout()->takeAt( 0 ) ) != NULL )
                {
                    delete item->widget();
                    delete item;
                }
                delete ui->scrollContents->layout();
            }

            //Tạo layout mới cho danh sách note
            ui->frame_2->hide();

            label = new QPushButton(title);
            label->setObjectName(title);

            QLabel *lab = new QLabel("Content: "+contentText+".");
            lab->setStyleSheet("color:white");
            QFrame *line = new QFrame;
            line->setFrameShape(QFrame::HLine);
            line->setFrameShadow(QFrame::Sunken);
            line->setStyleSheet("background:white");

            label->setStyleSheet(
                        "   QPushButton {"
                        "     background:transparent; Text-align:left;font-family:century gothic;font-size:18px; color:orange;"
                        " }"
                        " QPushButton:hover {"
                        "     color: rgb(224, 255, 0);font-size:25px;"
                        " }");
            lay->addWidget(label);
            lay->addWidget(lab);
            lay->addWidget(line);
            connect(label,SIGNAL(clicked()),this,SLOT(onnameclicked()));

        }
    }

    ui->scrollContents->setLayout(lay);
    ui->scrollContents->setStyleSheet("background: transparent;border-color: rgb(62, 62, 62);padding-left:20px;padding-top:20px");
    ui->scrollContents->setVisible(true);
    ui->scrollContents->show();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Hiển thị khung đặt mật khẩu để khóa note mình muốn
void MainWindow::on_pushButton_2_clicked()
{
    Setpassword = new setpassword(this);
    Setpassword->setGeometry(500,250,341,191);
    Setpassword->show();
}

//Hiển thị khung mở khóa note
void MainWindow::on_pushButton_5_clicked()
{
    Getpassword = new getpassword(this);
    Getpassword->setGeometry(500,250,341,191);
    Getpassword->show();
}

//Thêm note trống mới
void MainWindow::on_pushButton_3_clicked()
{

   QString title = ui->title->toPlainText();
   QString content = ui->content->toPlainText();
   if(!QString(title).isEmpty() || !QString(content).isEmpty())
   {
       ui->frame_2->hide();
       ui->title->clear();
       ui->content->clear();
       ui->frame_2->show();

   } else ui->frame_2->show();
}

//Lưu note vào database
void MainWindow::on_pushButton_4_clicked()
{
    QString title = ui->title->toPlainText();
    QString content = ui->content->toPlainText();


     if(!QString(title).isEmpty())
     {
        connOpen();
        QSqlQuery qry;
        qry.prepare("update note1 set title ='"+title+"'where id='"+currentID+"'");
        if(qry.exec())
        {
            connClose();

         }

            if(!QString(content).isEmpty())
            {
                connOpen();
                QSqlQuery qry;
                qry.prepare("update note1 set content ='"+content+"'where id='"+currentID+"'");
                if(qry.exec()){

                     qDebug()<<("update dc content");

                }

                qry.prepare("select * from note1 where id='"+currentID+"'");
                if(qry.exec())
             {       while(qry.next())
                    {
                        QSqlQueryModel *modal = new QSqlQueryModel();
                        QSqlQueryModel *modal1 = new QSqlQueryModel();
                        QSqlQueryModel *modal2 = new QSqlQueryModel();
                        //Tạo query...
                        QSqlQuery *qry = new QSqlQuery(mydb);
                        QSqlQuery *qry1 = new QSqlQuery(mydb);
                        QSqlQuery *qry2 = new QSqlQuery(mydb);
                        //Chọn data gắn vào...
                        qry->prepare("select id from note1");
                        qry1->prepare("select title from note1");
                        qry2->prepare("select content from note1");
                        //Thực hiện query...
                        qry->exec();
                        qry1->exec();
                        qry2->exec();

                        //Gắn query với modal...
                        modal->setQuery(*qry);
                        modal1->setQuery(*qry1);
                        modal2->setQuery(*qry2);

                        if ( ui->scrollContents->layout() != NULL )
                        {
                            QLayoutItem* item;
                            while ( ( item = ui->scrollContents->layout()->takeAt( 0 ) ) != NULL )
                            {
                                delete item->widget();
                                delete item;
                            }
                            delete ui->scrollContents->layout();
                        }
                        //Tạo khung mới
                        QGridLayout *lay = new QGridLayout(this);
                        QPushButton *content[2000];

                        for(int j=0; j<=modal->rowCount()-1; j++)
                        {
                        QString id = modal->record(j).value(0).toString();//id
                        QString title = modal1->record(j).value(0).toString();//(title)
                        QString contentText = modal2->record(j).value(0).toString();//(content)



                        //Biến string thành giao diện

                        content[j] = new QPushButton(contentText);
                        content[j]->setProperty("id",id);
                        QLabel *lab = new QLabel("Content: "+contentText+".");
                        lab->setStyleSheet("color:white");

                        //Chia từng mini note ra bằng đường kẻ trắng
                        QFrame *line;
                        line = new QFrame();
                        line->setFrameShape(QFrame::HLine);
                        line->setFrameShadow(QFrame::Sunken);
                        line->setStyleSheet("background:white");

                        //Nổi hiệu ứng khi rê chuột tới cho nút title
                        content[j]->setObjectName("btnName_1");
                        content[j]->setStyleSheet(
                        "   QPushButton#btnName_1 {"
                        "     background:transparent; Text-align:left;font-family:century gothic;font-size:18px; color:orange;"
                        " }"
                        " QPushButton#btnName_1:hover {"
                        "     color: yellow;font-size:25px;"
                        " }");

                        //Gắn giao diện với từng layout đã tạo
                        lab->setStyleSheet("background:transparent; Text-align:left;font-family:century gothic;font-size:18px; color:white");
                        lay->addWidget(content[j]);
                        lay->addWidget(lab);
                        lay->addWidget(line);
                         //Nhấn title sẽ thực hiện hàm onnameclicked
                         connect(content[j],SIGNAL(clicked()),this,SLOT(onnameclicked()));
                         //Bỏ layout vào khu vực kéo (scrollArea)
                         ui->scrollContents->setLayout(lay);
                        }
                        connClose();
                    }

                }
    } else {

            connOpen();
            QSqlQuery qry;
            qry.prepare("INSERT INTO note1 (title, content)" "VALUES (:title, :content)");
            qry.bindValue(":title", title);
            qry.bindValue(":content", content);

            if(qry.exec()){
                // Xet dieu kien cho du lieu duoc nhap vao
                    QMessageBox::information(this, "Đã được thêm vào", "Dữ liệu được thêm vào thành công");
                } else {
                    QMessageBox::information(this, "Không được thêm vào", "Dữ liệu không được thêm vào");
                }
            }

     }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Tạo màu cho chữ
void MainWindow::on_btnTextColor_clicked()
{
    QColor color = QColorDialog :: getColor(Qt::black,this);

        if (color.isValid())
        {
            ui->content->setTextColor(color);
        }
}
//Quay lại hành động
void MainWindow::on_btnUndo_clicked()
{
     ui->content->undo();
}
//Tiến tới hành động
void MainWindow::on_btnRedo_clicked()
{
    ui->content->redo();
}
//In đậm
void MainWindow::on_toolButton_bold_clicked()
{
    QFont font;
       font.setWeight(QFont::ExtraBold); // set font weight with enum QFont::Weight
       //font.setPixelSize(13); // this for setting font size
       ui->title->setFont(font);
       ui->content->setFont(font);
}
//In nghiêng
void MainWindow::on_toolButton_italic_clicked()
{
    QFont font;
       font.setItalic(QFont::StyleItalic); // set font weight with enum QFont::Weight
       //font.setPixelSize(13); // this for setting font size
       ui->title->setFont(font);
       ui->content->setFont(font);
}

//Gạch dưới
void MainWindow::on_toolButton_underline_clicked()
{
    QFont font;
        font.setUnderline(QFont::UnderlineResolved); // set font weight with enum QFont::Weight
        //font.setPixelSize(13); // this for setting font size
        ui->title->setFont(font);
        ui->content->setFont(font);
}

//Tạo bullets
void MainWindow::on_toolButton_plus_clicked()
{
    QTextDocument* document = ui->content->document();
           QTextCursor* cursor = new QTextCursor(document);

           QTextListFormat listFormat;
           listFormat.setStyle(QTextListFormat::ListDisc);
           cursor->insertList(listFormat);

           cursor->insertText("");
}

// Tạo khung vẽ
void MainWindow::on_pushButton_6_clicked()
{
    paintwindow = new PaintWindow(this);
    paintwindow->show();
}


