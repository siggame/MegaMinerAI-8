#include "coolslider.h"
#include <QPalette>

   
GranolaBar::GranolaBar( QWidget *parent ) 
  : QWidget( parent )
{

  m_parent = parent;

  setFixedHeight( m_parent->height() );
  setContentsMargins( 0, 0, 0, 0 );
  QColor whitish( 255, 255, 255, 200 );

  m_sliderControl = new QPushButton( this );
  QPalette bp( m_sliderControl->palette() );
  bp.setColor( QPalette::Button, whitish );
  bp.setColor( QPalette::Window, whitish );
  m_sliderControl->setPalette( bp );
  m_sliderControl->setAutoFillBackground( true );
  m_sliderControl->resize( 50, height()-5 );

  m_sliderControl->setStyleSheet( "\
      QPushButton { \
        border: none; \
        font-size: 10px; \
        font-weight: normal; \
        }" );

  m_sliderControl->setText( "50/500" );
  m_sliderControl->setContentsMargins( 0, 0, 0, 0 );

  m_borderStyle = new QColor( 130, 130, 130 );
  // Need to make this MOAR dynamic
  QLinearGradient grad( 0, 0, 0, 10 ); 
  grad.setColorAt( 0, QColor( 127, 127, 127) );
  grad.setColorAt( 1, Qt::white );

  m_grooveStyle = new QBrush( grad );

  m_maxFrame = 500;

}

void GranolaBar::setNumSubframes( frame_t16 frameNum, frame_t16 subframeCnt )
{
}

void GranolaBar::addDebugPoint( frame_t16 frame, frame_t16 subframe )
{
  m_debugPointFrames.push_back( frame );
}

void GranolaBar::addBookmark( frame_t16 frame, frame_t16 subframe )
{

  m_bookmarkFrames.push_back( frame );

}

void GranolaBar::setMaxFrame( frame_t16 frameNum )
{
  m_maxFrame = frameNum;
}

void GranolaBar::paintEvent( QPaintEvent * )
{
  // DON'T PUT ANY MOVE COMMANDS IN HERE
  // WILL CAUSE RECURSIVE PAINT CALLS
  static int x = 0;
  int tWidth = width()-20;
  float factor = ((float)tWidth-m_sliderControl->width()/2)/m_maxFrame;
  QString output;
  output = QString::number( x ) + "/" + QString::number( m_maxFrame );
  m_sliderControl->setText( output );
  int xPos = x*factor;


  factor = ((float)tWidth)/m_maxFrame;

  // It appears the y origin is at -2..... 
  m_sliderControl->move( xPos, 1 );

  // Probably want to draw this once, save it, and then redraw that every time as long as we don't resize
  QPainter painter( this );
  painter.setRenderHint( QPainter::Antialiasing );
  painter.setPen( *m_borderStyle );
  painter.setBrush( *m_grooveStyle );
  painter.drawRoundedRect( 10, height()/2-5-2, width()-20, 10, 1, 1 );

  int hang = 10;

  painter.setPen( QColor( 0, 100, 0 ) );
  for( list<frame_t16>::iterator i = m_bookmarkFrames.begin(); i != m_bookmarkFrames.end(); i++ )
  {
    painter.drawLine( *i * factor+10, height()/2-5-1 - hang, *i * factor + 10, height()/2 -1 );
  }
 
  painter.setPen( QColor( 100, 0, 0 ) );
  for( list<frame_t16>::iterator i = m_debugPointFrames.begin(); i != m_debugPointFrames.end(); i++ )
  {
    painter.drawLine( *i * factor + 10, height()/2-1, *i * factor + 10, height()/2 + 3 + hang );
  }
   

}

