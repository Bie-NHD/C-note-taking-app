#ifndef MAINWINDOWTEXTEDIT_H
#define MAINWINDOWTEXTEDIT_H

#include <QWidget>

namespace Ui {
class MainWindowTextEdit;
}

class MainWindowTextEdit : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindowTextEdit(QWidget *parent = nullptr);
    ~MainWindowTextEdit();

private:
    Ui::MainWindowTextEdit *ui;
};

#endif // MAINWINDOWTEXTEDIT_H
