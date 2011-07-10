#include "timeManager.h"
#include "../optionsmanager/optionsman.h"

#include <ctime>

_TimeManager *TimeManager = 0;

const int& _TimeManager::getTurn()
{
  return m_turn;
}


const int& _TimeManager::getFrame()
{
  return m_frame;
}


void _TimeManager::setTurn( const int& turn )
{
  m_turn = turn;
  m_frame = 0;

  updateChildren();
}


float _TimeManager::getSpeed()
{
  float multi = OptionsMan->getFloat( "speed" );
  return m_speed * multi;
}


void _TimeManager::setSpeed( const float& speed )
{
  float multi = OptionsMan->getFloat( "speed" );
  m_speed = speed/multi;
}


int _TimeManager::timeHash()
{
  return m_hash;
}


_TimeManager::mode _TimeManager::getMode()
{
  return m_mode;
}


const int& _TimeManager::getNumTurns()
{
  return m_numTurns;
}


void _TimeManager::setNumTurns( const int& numTurns )
{
  m_numTurns = numTurns;

  // FIXME: Must update control bar
  updateChildren();
}


void _TimeManager::setup()
{
  if( !TimeManager )
  {
    TimeManager = new _TimeManager;
    TimeManager->_setup();
  } else
  {
    throw "Time Manager already initialized";
  }
}


void _TimeManager::destroy()
{
  delete TimeManager;
  TimeManager = 0;
}


void _TimeManager::_setup()
{
  m_lastTime = clock();
  m_framesPerTurn = 100;
  m_turn = 0;
  m_frame = 0;

}


void _TimeManager::start()
{
  timer = new QTimer( this );
  connect( timer, SIGNAL(timeout()), this, SLOT(timerUpdate()) );
  timer->start( 35 );

}


void _TimeManager::timerStart()
{
  start();
}


void _TimeManager::updateFrames()
{
  if( m_framesPerTurn )
  {
    m_turn += m_frame / m_framesPerTurn;
    m_frame %= m_framesPerTurn;
  }
  else
  {
    m_turn = 0;
    m_frame = 0;
  }

  // FIXME: Fix this so that we check the time manager to see if we're ready to close
  // instead of having the time manager tell us

  updateChildren();

  #if 0
  //If in arena mode, show winner for a few secs at end
  if (OptionsMan->getBool("arenaMode") && m_turn == m_numTurns-1 && m_numTurns > 5)
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


void _TimeManager::requestUpdate( UpdateNeeded* requester )
{
  Singleton< _TimeManager >::instance()->m_updateRequesters.push_back( requester );
}


void _TimeManager::timerUpdate()
{
  m_time = ((clock() - m_lastTime) / CLOCKS_PER_SEC) * 1000;
  m_hash++;
  m_frame += m_time * m_speed;

  updateFrames();

  updateChildren();
}


#include <iostream>
using namespace std;

void _TimeManager::updateChildren()
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
