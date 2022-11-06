#ifndef COLORPALETTE_H
#define COLORPALETTE_H

#include <QLabel>
#include <QMouseEvent>

class ColorPalette: public QLabel
{
    Q_OBJECT

public:

    ColorPalette( const QString & path, QWidget * parent = 0 );

    ColorPalette( QWidget * parent = 0 );

public slots:

    void setImage( const QString & path );

protected:
    void mousePressEvent( QMouseEvent * event );

signals:

    void selectedColor( QColor color );
};

#endif // COLORPALETTE_H
