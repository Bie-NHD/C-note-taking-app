#ifndef UCOLORBUTTON_H
#define UCOLORBUTTON_H

#include <QToolButton>
#include <QLabel>
#include <QBitmap>
#include <QMouseEvent>

#include "colorpalette.h"

class d_ColorButton;


class ColorButton: public QToolButton
{
    Q_OBJECT

public:
    ColorButton( QWidget *parent = 0 );
    ~ColorButton();

    QColor color();

private:
    void createGUI();

protected:
    d_ColorButton * d;

private slots:
    void defaultColor();
    void anotherColor();

public slots:

    void setColor( const QColor & color );


    void setDefaultColor( const QColor & color );

signals:

    void selectedColor( QColor );
};


class d_ColorButton
{
public:
    QToolButton * tButtonDefaultColor;
    QToolButton * tButtonSelectColor;
    ColorPalette * colorPalette;
    QColor color;
};

#endif
