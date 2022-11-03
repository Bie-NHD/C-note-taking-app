#include "custombutton.h"


CustomButton::CustomButton()
{
        m_ButtonLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
        m_ButtonLayout->setAlignment(Qt::AlignCenter);
        m_ButtonLayout->setContentsMargins(0, 0, 0, 0);
        m_ButtonLayout->setSpacing(1);

        m_IconLabel = new QLabel(this);
        m_IconLabel->setAlignment(Qt::AlignCenter);
        m_ButtonLayout->addWidget(m_IconLabel);

        m_TextLabel = new QLabel(this);
        m_TextLabel->setAlignment(Qt::AlignCenter);
        m_ButtonLayout->addWidget(m_TextLabel);
        //m_TextLabel->hide();
}
CustomButton* CustomButton::createButton(QIcon icon, QWidget *parent)
{
    CustomButton* pButton = new CustomButton(parent);
    pButton->setIcon(icon);

    return pButton;
}

void CustomButton::setText(QString text)
{
    m_TextLabel->setVisible(!text.isEmpty());
    m_TextLabel->setText(text);
    QAbstractButton::setText(text);
}

void CustomButton::setIcon(QIcon icon)
{
    m_Icon = icon;
    m_IconLabel->setVisible(true);
}

void CustomButton::setOrientation(Qt::Orientation orientation)
{
    if (orientation == Qt::Horizontal)
        m_ButtonLayout->setDirection(QBoxLayout::LeftToRight);
    else
        m_ButtonLayout->setDirection(QBoxLayout::TopToBottom);
}
