#include "granolabar.h"
#include <QPalette>

   
GranolaBar::GranolaBar( QWidget *parent ) 
  : QWidget( parent )
{

  m_parent = parent;

  setFixedHeight( m_parent->height() );
  setContentsMargins( 0, 0, 0, 0 );
  QColor whitish( 255, 255, 255, 0 );

  m_sliderControl = new GranolaButton( this );
  QPalette bp( m_sliderControl->palette() );
  bp.setColor( QPalette::Button, whitish );
  bp.setColor( QPalette::Window, whitish );
  m_sliderControl->setPalette( bp );
  m_sliderControl->setAutoFillBackground( true );
  m_sliderControl->resize( 50, height()-7 );

  m_sliderControl->setText( "50/500" );
  m_sliderControl->setContentsMargins( 0, 0, 0, 0 );

  m_borderStyle = new QColor( 130, 130, 130 );
  // Need to make this MOAR dynamic
  QLinearGradient grad( 0, 0, 0, 10 ); 
  grad.setColorAt( 1, QColor( 187, 187, 187) );
  grad.setColorAt( 0, QColor( 227, 227, 227)  );

  m_grooveStyle = new QBrush( grad );

  grad.setColorAt( 0, QColor( 0, 50, 0, 255 ) );
  grad.setColorAt( 1, QColor( 0, 127, 0, 255 ) );

  m_bookmarkStyle = new QBrush( grad );

  grad.setColorAt( 0, QColor( 255, 0, 0, 255 ) );
  grad.setColorAt( 1, QColor( 150, 0, 0, 255 ) );

  m_debugPointStyle = new QBrush( grad );


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
  static int x = 15;
  int tWidth = width()-20;
  float factor = ((float)tWidth-m_sliderControl->width()/2)/m_maxFrame;
  QString output;
  output = QString::number( x ) + " | " + QString::number( m_maxFrame );
  m_sliderControl->setText( output );
  int xPos = x*factor;
  int yOffset;
  int barHeight;


  factor = ((float)tWidth)/m_maxFrame;

  // It appears the y origin is at -2..... 
  m_sliderControl->move( xPos, 1 );
  int divisor =  m_maxFrame;
  
 // m_sliderControl->setFixedWidth( 4*width()/m_maxFrame );

  // Probably want to draw this once, save it, and then redraw that every time as long as we don't resize
  QPainter painter( this );
  painter.setRenderHint( QPainter::Antialiasing );
  painter.setPen( *m_borderStyle );
  painter.setBrush( *m_grooveStyle );

  yOffset = 0;
  barHeight = height()-5;
  painter.drawRoundedRect( 10, yOffset, width()-20, barHeight, 1, 1 );

  int hang = 10;

  painter.setBrush( *m_bookmarkStyle );
  painter.setPen( Qt::NoPen );
  int frameWidth = width()/m_maxFrame > 0 ? width()/m_maxFrame : 1;
  for( list<frame_t16>::iterator i = m_bookmarkFrames.begin(); i != m_bookmarkFrames.end(); i++ )
  {
    painter.drawRect( *i * factor+10, yOffset-1, frameWidth, barHeight/2+1 );
  }
 
  painter.setBrush( *m_debugPointStyle );
  for( list<frame_t16>::iterator i = m_debugPointFrames.begin(); i != m_debugPointFrames.end(); i++ )
  {
    painter.drawRect( *i * factor+10, barHeight/2+1, frameWidth, barHeight/2 );
  }
   
  painter.setBrush( QColor( 0, 0, 0, 50 ) );
  painter.drawRect( 0, barHeight/2, width(), 1 );

  //painter.drawLine( 0, barHeight/2+1, width(), barHeight/2+1 );


}

