#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include "qlabel.h"
#include <QAbstractButton>
#include <QMainWindow>
#include <QObject>
#include <QLayout>

class CustomButton : public QAbstractButton
{
    Q_OBJECT
public:
    static CustomButton* createButton(QIcon icon, QWidget *parent);

    CustomButton();
    ~CustomButton();
    void setText(QString);
    void setIcon(QIcon);
    void setOrientation(Qt::Orientation);

    protected :
    CustomButton(QWidget *parent);
    private :
    QLayout*  m_ButtonLayout;
    QLabel*      m_IconLabel;
    QIcon        m_Icon;
    QLabel*      m_TextLabel;
};

#endif // CUSTOMBUTTON_H
