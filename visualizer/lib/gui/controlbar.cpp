#include "controlbar.h"
#include "../timemanager/timeManager.h"
#include <QHBoxLayout>

namespace visualizer
{

  ControlBar::ControlBar( QWidget *parent ) : QWidget( parent)
  {
    setContentsMargins( 0, 0, 0, 0 );
    QHBoxLayout *layout = new QHBoxLayout;
    layout -> setContentsMargins(0,0,0,0);

    rewindButton = new QPushButton("<", this);
    playButton = new QPushButton("||", this);
    fastForwardButton = new QPushButton("->", this);

    turnLabel = new QLabel("", this);
    turnLabel->setMinimumWidth(30);
    turnLabel->setMaximumWidth(30);
    turnLabel->clear();

    m_slider = new QSlider( Qt::Horizontal, this );
    m_slider->setMinimum( 0 );
    //maximum set by TimeManager
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
    originalTimeManagerSpeed = 0;

    connect( m_slider, SIGNAL(sliderPressed()), this, SLOT(sliderDrag()) );
    connect( m_slider, SIGNAL(sliderReleased()), this, SLOT(sliderRelease()) );
    connect( m_slider, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged(int)) );

    connect( rewindButton, SIGNAL(clicked()), this, SLOT( rewind()) );
    connect( playButton, SIGNAL(clicked()), this, SLOT( play()) );
    connect( fastForwardButton, SIGNAL(clicked()), this, SLOT( fastForward()) );

    layout->addWidget( turnLabel );
    layout->addWidget( m_slider );
    layout->addWidget( rewindButton );
    layout->addWidget( playButton );
    layout->addWidget( fastForwardButton );

    setLayout( layout );

    TimeManager->requestUpdate( this );

    update();
  }


  void ControlBar::sliderDrag()
  {
    originalTimeManagerSpeed = TimeManager->getSpeed();
    TimeManager->pause();
  }


  void ControlBar::sliderRelease()
  {
    TimeManager->setSpeed( originalTimeManagerSpeed );
  }


  void ControlBar::sliderChanged( int value )
  {
    TimeManager->setTurn(value);
  }


  void ControlBar::update()
  {
    m_slider->setSliderPosition( TimeManager->getTurn() );
    m_slider->setMaximum( TimeManager->getNumTurns()-1 );
    turnLabel->setText( QString::number( TimeManager->getTurn() ) );
  }


  void ControlBar::rewind()
  {
    TimeManager->rewind();
    playButton->setText( "||" );
  }


  void ControlBar::play()
  {
    if( TimeManager->getSpeed() != 0 )
    {
      TimeManager->pause();
      playButton->setText( ">" );
    }
    else
    {
      TimeManager->play();
      playButton->setText( "||" );
    }

  }


  void ControlBar::fastForward()
  {
    TimeManager->fastForward();
    playButton->setText( "||" );
  }

} // visualizer
