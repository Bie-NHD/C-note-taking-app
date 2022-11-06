#include "colorpalette.h"

#include <QPixmap>
#include <QBitmap>
#include <QWidget>
//Đây là file dãy màu được sử dụng trong nút tạo text color và khung vẽ
ColorPalette::ColorPalette( const QString & path, QWidget * parent )
    : QLabel( parent )
{
    setAutoFillBackground( true );
    setMouseTracking( true );

    setImage( path );
}
ColorPalette::ColorPalette( QWidget * parent )
    : QLabel( parent )
{
    setAutoFillBackground(true);
    setMouseTracking(true);
}

void ColorPalette::setImage( const QString & path )
{
    QPixmap pixmap( path );
    setMask( pixmap.mask() );

    QPalette palette;
    palette.setBrush( backgroundRole(), QBrush( pixmap ) );

    setPalette( palette );
    setFixedSize( pixmap.size() );
}


void ColorPalette::mousePressEvent( QMouseEvent * event )
{
    QRect onePixRect( event->pos(), QSize( 1, 1 ));
}

