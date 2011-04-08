#include "controlbar.h"
#include "../timemanager/timeManager.h"
#include <QHBoxLayout>

ControlBar::ControlBar( QWidget *parent ) : QWidget( parent)
{
  setContentsMargins( 0, 0, 0, 0 );
  QHBoxLayout *layout = new QHBoxLayout;

  m_slider = new QSlider( Qt::Horizontal, this );
  m_slider->setMinimum( 0 );
  m_slider->setTickInterval( 50 ); 
  m_slider->setStyleSheet( "\
			QSlider::groove:horizontal {\
			height: 8px;\
			border: 1px solid #999999;\
			background: qlineargradient( x1: 0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\
			}\
			QSlider::handle:horizontal {\
			width: 50px;\
			height: 15px;\
			border: 1px solid #999999;\
			margin: -2px 0px; \
			border-radius: 3px;\
			background: qlineargradient(x1:0, y1:0, x2:1, y2:1,stop:0 #b4b4b4, stop:1 #909090);\
			}\
		  QSlider::sub-page:horizontal {\
			background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1, stop: 0 #F66E00, stop: 1 #CF5C00);\
			height: 10px;\
			border-radius: 4px;\
		  }	");

  m_slider->setTracking( true );

  connect( m_slider, SIGNAL(sliderPressed()), this, SLOT(sliderDrag()) );
  connect( m_slider, SIGNAL(sliderReleased()), this, SLOT(sliderRelease()) );
  connect( m_slider, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged(int)) );

  layout->addWidget( m_slider );

  setLayout( layout );

  update();

}

void ControlBar::sliderDrag()
{
  TimeManager::setSpeed(0);
}

void ControlBar::sliderRelease()
{
  TimeManager::setSpeed(1);
}

void ControlBar::sliderChanged( int value )
{
  TimeManager::setTurn(value);

}

void ControlBar::update()
{
  m_slider->setSliderPosition( TimeManager::getTurn() );
  m_slider->setMaximum( TimeManager::getNumTurns() );

}
