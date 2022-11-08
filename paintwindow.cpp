#include <QtWidgets>
#include "mainwindow.h"
#include "scribblearea.h"
#include <paintwindow.h>

//Đây là file chính gồm các tính năng của khung vẽ được sử dụng thêm bên scribblearea

PaintWindow::PaintWindow(QWidget *parent) : QMainWindow(parent)

{
    scribbleArea = new ScribbleArea;
    setCentralWidget(scribbleArea);
    createActions();
    createMenus();
    setWindowTitle(tr("Khung vẽ"));
    resize(800, 500);
}

void PaintWindow::closeEvent(QCloseEvent *event){
    if(maybeSave()){
        event->accept();
    }else{
        event->ignore();
    }
}

void PaintWindow::open(){
    if(maybeSave()){
        QString fileName = QFileDialog::getOpenFileName(this, tr("Mở file"), QDir::currentPath());
        if(!fileName.isEmpty()){
            scribbleArea->openImage(fileName);
        }
    }
}

void PaintWindow::save(){
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void PaintWindow::penColor(){
    QColor newColor = QColorDialog::getColor(scribbleArea->penColor());
    if(newColor.isValid()){
        scribbleArea->setPenColor(newColor);
    }
}

void PaintWindow::penWidth(){
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Ứng dụng vẽ"), tr("Chọn độ rộng cây bút: "), scribbleArea->penWidth(), 1, 50, 1, &ok);

    if(ok){
        scribbleArea->setPenWidth(newWidth);
    }
}

void PaintWindow::about(){
    QMessageBox::about(this, tr("Thông tin về ứng dụng"), tr("<p>Ứng dụng được làm bởi nhóm 10, mọi thắc mắc xin liên hệ 4 đứa tụi mình</p>"));
}

void PaintWindow::createActions(){
    openAct = new QAction(tr("&Mở"), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
    foreach (QByteArray format, QImageWriter::supportedImageFormats()){
        QString text = tr("%1...").arg(QString(format).toUpper());
        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActs.append(action);
    }
    exitAct = new QAction(tr("&Thoát"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    penColorAct = new QAction(tr("&Đổi màu bút..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));
    penWidthAct = new QAction(tr("&Độ rộng bút..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    clearScreenAct = new QAction(tr("&Xóa màn hình..."), this);
    clearScreenAct->setShortcut(tr("Ctrl + L"));
    connect(clearScreenAct, SIGNAL(triggered()), scribbleArea, SLOT(clearImage()));

    aboutAct = new QAction(tr("&Thông tin về..."), this);
    connect(aboutAct, SIGNAL(triggered()), SLOT(about()));

    aboutQtAct = new QAction(tr("Thông tin về Qt..."), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void PaintWindow::createMenus(){
    saveAsMenu = new QMenu(tr("&Lưu dưới dạng"), this);
    foreach(QAction *action, saveAsActs)
        saveAsMenu->addAction(action);
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    optionMenu = new QMenu(tr("&Các tùy chọn"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);

    helpMenu = new QMenu(tr("&Trợ giúp"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);
}

bool PaintWindow::maybeSave(){
    if(scribbleArea->isModified()){
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Ứng dụng vẽ"), tr("Hình đã được thay đổi.\n" "Bạn có muốn lưu lại những thay đổi không?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(ret == QMessageBox::Save){
            return saveFile("png");
        }else if(ret == QMessageBox::Cancel){
            return false;
        }
    }
    return true;
}

bool PaintWindow::saveFile(const QByteArray &fileFormat){
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), initialPath, tr("%1 Files (*.%2);; All Files(*)").arg(QString::fromLatin1(fileFormat.toUpper())).arg(QString::fromLatin1(fileFormat)));
    if(fileName.isEmpty()){
        return false;
    }else{
        return scribbleArea->saveImage(fileName, fileFormat.constData());
    }
}
