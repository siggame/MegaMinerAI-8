#include "timeManager.h"
#include "../renderer/renderer.h"
#include "../gui/gui.h"
#include "../../piracy/dupObj.h"

#include <ctime>

const int& TimeManager::getTurn()
{
  if( !isInit() )
    return 0;
  get()->updateFrames();
  return get()->m_turn;
}

const int& TimeManager::getFrame()
{
  if( !isInit() )
    return 0;
  get()->updateFrames();
  return get()->m_frame;
}

void TimeManager::setTurn( const int& turn )
{
  if( !isInit() )
    throw 0;

  get()->m_turn = turn;
  get()->m_frame = 0;

  //update renderer
  Renderer<DupObj>::update(turn,0);

  GUI::getControlBar()->m_slider->update();
}

const int& TimeManager::getSpeed()
{
  if( !isInit() )
    return 0;
  return get()->m_speed;
}

void TimeManager::setSpeed( const int& speed )
{
  if( !isInit() )
    throw 0;
  get()->m_speed = speed;
}

int TimeManager::timeHash()
{
    if (!isInit())
	return 0;
  return get()->m_hash;
}

TimeManager::mode TimeManager::getMode()
{
  if( !isInit() )
    return mode();
  return get()->m_mode;
}

const int& TimeManager::getNumTurns()
{
  if( !isInit() )
    return 0;

  return get()->m_numTurns;
}

void TimeManager::setNumTurns( const int& numTurns )
{
  if( !isInit() )
    throw 0;
  get()->m_numTurns = numTurns;
  GUI::getControlBar()->m_slider->setMaximum ( numTurns );
  cout << "numTurns: " << numTurns<<endl;
}


bool TimeManager::create()
{

    if( !Singleton<TimeManager>::create() )
      return false;

    Singleton<TimeManager>::get()->setup();
   return true;
}

void TimeManager::setup()
{
  m_lastTime = clock();
  m_framesPerTurn = 10000;
  m_turn = 0;
  m_frame = 0;

  timer = new QTimer( this );
  connect( timer, SIGNAL(timeout()), this, SLOT(timerUpdate()) );
  timer->start( 35 );
}

#include <iostream>
using namespace std;

void TimeManager::updateFrames()
{
  m_turn += m_frame / m_framesPerTurn;
  m_frame %= m_framesPerTurn;

  //Idiot check low
  if (m_turn < 0)
  {
    m_turn = 0;
    m_frame = 0;
  }

  //Idiot check high
  if (m_turn >= m_numTurns)
  {
    m_turn = m_numTurns-1;
    m_frame = m_framesPerTurn-1;
  }

  //If in arena mode, show winner for a few secs at end
  if (optionsMan::getBool("arenaMode") && m_turn == m_numTurns-1)
  {
    if( m_sleepTime == -1 )
      m_sleepTime = ((clock() - m_lastTime) / CLOCKS_PER_SEC) * 1000;
    else
    {
      if( m_time - m_sleepTime > 3000 )
      {
        GUI::closeGUI();
      }

    }

  } 

  if(GUI::isSetup())
  {

    GUI::getControlBar()->m_slider->setValue ( m_turn );
  }
}

void TimeManager::timerUpdate()
{
  m_time = ((clock() - m_lastTime) / CLOCKS_PER_SEC) * 1000;
  m_hash++;
  m_frame += m_time * m_speed;
  updateFrames();
  Renderer<DupObj>::refresh();
  Renderer<DupObj>::update(m_turn,0);
}

