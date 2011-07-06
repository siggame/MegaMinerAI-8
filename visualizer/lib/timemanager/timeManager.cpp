#include "timeManager.h"
#include "../optionsmanager/optionsman.h"

#include <ctime>

const int& TimeManager::getTurn()
{
#if 0
  if( !isInit() )
    // FIXME: This is bad.  Returns a reference to an integer which will be immediately destroyed
    return 0;
#endif
  return instance()->m_turn;
}

const int& TimeManager::getFrame()
{
#if 0
  if( !isInit() )
    // FIXME: Returning ref to temporary.
    return 0;
#endif
  return instance()->m_frame;
}

void TimeManager::setTurn( const int& turn )
{
#if 0
  if( !isInit() )
    throw 0;
#endif

  instance()->m_turn = turn;
  instance()->m_frame = 0;

  Singleton<TimeManager>::instance()->updateChildren();

}

const float& TimeManager::getSpeed()
{
#if 0
  if( !isInit() )
    return 0;
#endif

  float multi = OptionsMan::getFloat( "speed" );
  return TimeManager::instance()->m_speed * multi;
}

void TimeManager::setSpeed( const float& speed )
{
#if 0
  if( !isInit() )
    throw 0;
#endif

  float multi = OptionsMan::getFloat( "speed" );
  instance()->m_speed = speed/multi;
}

int TimeManager::timeHash()
{
#if 0
  if (!isInit())
    return 0;
#endif

  return instance()->m_hash;
}

TimeManager::mode TimeManager::getMode()
{
#if 0
  if( !isInit() )
    return mode();
#endif
  return instance()->m_mode;
}

const int& TimeManager::getNumTurns()
{
#if 0
  if( !isInit() )
    return 0;
#endif

  return instance()->m_numTurns;
}

void TimeManager::setNumTurns( const int& numTurns )
{
#if 0
  if( !isInit() )
    throw 0;
#endif
  instance()->m_numTurns = numTurns;

  // FIXME: Must update control bar
  Singleton<TimeManager>::instance()->updateChildren();
}


bool TimeManager::create()
{
#if 0
  if( !Singleton<TimeManager>::create() )
    return false;
#endif

  Singleton<TimeManager>::instance()->setup();
   return true;
}

void TimeManager::setup()
{
  m_lastTime = clock();
  m_framesPerTurn = 100;
  m_turn = 0;
  m_frame = 0;

}

void TimeManager::start()
{
    instance()->timer = new QTimer( this );
    connect( instance()->timer, SIGNAL(timeout()), this, SLOT(timerUpdate()) );
    instance()->timer->start( 35 );

}

void TimeManager::timerStart()
{
    instance()->start();
}

void TimeManager::updateFrames()
{
  m_turn += m_frame / m_framesPerTurn;
  m_frame %= m_framesPerTurn;

  // FIXME: Fix this so that we check the time manager to see if we're ready to close
  // instead of having the time manager tell us
  
  Singleton< TimeManager >::instance()->updateChildren();

#if 0
  //If in arena mode, show winner for a few secs at end
  if (OptionsMan::getBool("arenaMode") && m_turn == m_numTurns-1 && m_numTurns > 5)
  {
    if( m_sleepTime == -1 )
      m_sleepTime = clock();
    else
    {
      if( clock() - m_sleepTime > 1000000 )
      {
        GUI::closeGUI();
      }
    }
  } 

  if(GUI::isSetup())
  {

    GUI::getControlBar()->m_slider->setValue ( m_turn );
  }
#endif
}

void TimeManager::requestUpdate( UpdateNeeded* requester )
{
  Singleton< TimeManager >::instance()->m_updateRequesters.push_back( requester );
}

void TimeManager::timerUpdate()
{
  m_time = ((clock() - m_lastTime) / CLOCKS_PER_SEC) * 1000;
  m_hash++;
  m_frame += m_time * m_speed;

  updateFrames();

  updateChildren();
}

#include <iostream>
using namespace std;

void TimeManager::updateChildren()
{
  int count =1;
  for( 
      std::list< UpdateNeeded* >::iterator i = m_updateRequesters.begin();
      i != m_updateRequesters.end();
      i++
     )
  {
    cout << "Update " << count++ << endl;
    (*i)->update();
  }
}

