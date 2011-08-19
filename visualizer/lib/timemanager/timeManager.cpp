#include "timeManager.h"
#include "../optionsmanager/optionsman.h"

#include <ctime>
#include <cmath>

namespace visualizer
{

  _TimeManager *TimeManager = 0;

  void _TimeManager::setup()
  {
    if( !TimeManager )
    {
      TimeManager = new _TimeManager;
      TimeManager->_setup();
    } else
    {
      THROW( Exception, "Time Manager already initialized" );
    }

  } // _TimeManager::setup()

  void _TimeManager::destroy()
  {
    delete TimeManager;
    TimeManager = 0;

  } // _TimeManager::destroy()

  void _TimeManager::_setup()
  {
    /// @FIXME There's really no reason this shouldn't all be in a constructor
    m_turn = 0;
    m_progress = 0;
    m_speed = 0;
    m_turnCompletion = 0;
    m_numTurns = 500;

  } // _TimeManager::_setup()

  void _TimeManager::updateProgress( float progress )
  {
    m_progress = progress;

  } // _TimeManager::updateProgress()

  void _TimeManager::setSpeed( const float& speed )
  {
    /// Speed will be measured in turns / time (s).
    /// Setting the speed to 1 would mean 1 turn / second
    /// .5 would mean 1 turn / 2 seconds
    /// 1.5 would mean 3 turns / 2 seconds
    /// etc. etc.
    
    OptionsMan->setFloat( "speed", speed );

  } // _TimeManager::setSpeed()

  void _TimeManager::timerStart()
  {
    start();

  } // _TimeManager::timerStart()

  void _TimeManager::start()
  {
    m_timer = new QTimer( this );
    connect( m_timer, SIGNAL(timeout()), this, SLOT(timerUpdate()) );
    int maxFPS = 60;
    // Determines the refresh rate based off of the max number of frames/sec.
    m_timer->start( (float)1000/maxFPS );
    m_time.start();

  } // _TimeManager::start()

  void _TimeManager::requestUpdate( UpdateNeeded* requester )
  {
    m_updateRequesters.push_back( requester );

  } // _TimeManager::requestUpdate()

  void _TimeManager::updateChildren()
  {
    for(
      std::list< UpdateNeeded* >::iterator i = m_updateRequesters.begin();
      i != m_updateRequesters.end();
      i++
      )
    {
      (*i)->update();
    }

  } // _TimeManager::updateChildren()

  const int& _TimeManager::getTurn() const
  {
    return m_turn;

  } // _TimeManager::getTurn()

  const float& _TimeManager::getTurnPercent() const
  {
    return m_turnCompletion;

  } // _TimeManager::getTurnPercent()

  void _TimeManager::setTurn( const int& turn )
  {
    m_turn = turn;

    updateChildren();

  } // _TimeManager::setTurn()

  const int& _TimeManager::nextTurn()
  {
    pause();
    m_turnCompletion = 0;
    m_turn++;
    return getTurn();

  } // _TimeManager::nextTurn()

  const int& _TimeManager::prevTurn()
  {
    pause();
    m_turnCompletion = 0;
    m_turn--;
    return getTurn();

  } // _TimeManager::prevTurn()

  void _TimeManager::play()
  {
    m_speed = OptionsMan->getFloat( "speed" );

  } // _TimeManager::play()

  void _TimeManager::pause()
  {
    m_speed = 0;

  } // _TimeManager::pause()

  void _TimeManager::fastForward()
  {
    IMPLEMENT_ME;

  } // _TimeManager::fastForward()

  void _TimeManager::rewind()
  {
    if( m_speed >= 0 )
    {
      m_speed = -OptionsMan->getFloat( "speed" );
    }
    else
    {
      IMPLEMENT_ME;
    }

  } // _TimeManager::rewind()

  const int& _TimeManager::getNumTurns() const
  {
    return m_numTurns;

  } // _TimeManager::getNumTurns()

  void _TimeManager::setNumTurns( const int& numTurns )
  {
    m_numTurns = numTurns;

    // @FIXME Must update control bar
    // @FIXME 
    //updateChildren();

  } // _TimeManager::setNumTurns()

  const float& _TimeManager::getSpeed()
  {
    return m_speed;

  } // _TimeManager::getSpeed()

  void _TimeManager::timerUpdate()
  {
    // m_time.restart() returns the number of milliseconds
    // since it was last called.

    float secElapsed = (float)m_time.restart()/1000;
    m_turnCompletion += getSpeed() * secElapsed;

    if( m_turnCompletion > 1 )
    {
      m_turn += floor( m_turnCompletion );
      m_turnCompletion -= floor( m_turnCompletion );

      if( m_turn >= m_numTurns )
      {
        m_turn = m_numTurns-1;
        m_turnCompletion = 0;
        pause();
      }

    }
    else if( m_turnCompletion < -1 )
    {
      m_turn -= ceil( m_turnCompletion );
      m_turnCompletion += ceil( m_turnCompletion );

      if( m_turn <= 0 )
      {
        m_turn = 0;
        m_turnCompletion = 0;
        pause();
      }

    }
    updateChildren();

  } // _TimeManager::timerUpdate()


} // visualizer

