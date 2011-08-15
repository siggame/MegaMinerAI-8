#include "timeManager.h"
#include "../optionsmanager/optionsman.h"

#include <ctime>

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
    m_turn = 0;

  } // _TimeManager::_setup()

  void _TimeManager::updateProgress( float progress )
  {
    m_progress = progress;

  } // _TimeManager::updateProgress()

  void _TimeManager::setSpeed( const float& speed )
  {
    float multi = OptionsMan->getFloat( "speed" );
    m_speed = speed/multi;

  } // _TimeManager::setSpeed()

  void _TimeManager::timerStart()
  {
    start();

  } // _TimeManager::timerStart()

  void _TimeManager::start()
  {
    m_timer = new QTimer( this );
    connect( m_timer, SIGNAL(timeout()), this, SLOT(timerUpdate()) );
    m_timer->start( 35 );

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

  const int& _TimeManager::getTurn()
  {
    return m_turn;

  } // _TimeManager::getTurn()

  void _TimeManager::setTurn( const int& turn )
  {
    m_turn = turn;

    updateChildren();

  } // _TimeManager::setTurn()

  const int& _TimeManager::getNumTurns()
  {
    return m_numTurns;

  } // _TimeManager::getNumTurns()

  void _TimeManager::setNumTurns( const int& numTurns )
  {
    m_numTurns = numTurns;

    // @FIXME Must update control bar
    updateChildren();

  } // _TimeManager::setNumTurns()

  float _TimeManager::getSpeed()
  {
    float multi = OptionsMan->getFloat( "speed" );
    return m_speed * multi;

  } // _TimeManager::getSpeed()

  void _TimeManager::timerUpdate()
  {
    // m_time.restart() returns the number of milliseconds
    // since it was last called.

    /// @FIXME Need to check if we're actually playing or not
    m_turn += m_time.restart() * m_speed;

    updateChildren();

  } // _TimeManager::timerUpdate()


} // visualizer

