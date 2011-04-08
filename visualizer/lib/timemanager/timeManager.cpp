#include "timeManager.h" 
#include "../renderer/renderer.h"

#include <ctime>

const int& TimeManager::getTurn()
{
  if( !isInit() )
    throw 0;
  get()->updateFrames();
  return get()->m_turn;
}

const int& TimeManager::getFrame() 
{
  if( !isInit() )
    throw 0;
  get()->updateFrames();
  return get()->m_frame;
}

void TimeManager::setTurn( const int& turn )
{
  if( !isInit() )
    throw 0;
  get()->m_turn = turn;
  get()->m_frame = 0;
}

const int& TimeManager::getSpeed()
{
  if( !isInit() )
    throw 0;
  return get()->m_speed;
}

void TimeManager::setSpeed( const int& speed )
{
  if( !isInit() )
    throw 0;
  get()->m_speed = speed;
}

const int& TimeManager::getNumTurns()
{
  if( !isInit() )
    throw 0;
  return get()->m_numTurns;
}

void TimeManager::setNumTurns( const int& numTurns )
{
  if( !isInit() )
    throw 0;
  get()->m_numTurns = numTurns;
}


void TimeManager::create()
{
  if( !isInit() )
  {
    if( !Singleton<TimeManager>::create() )
      throw 0;
  }
  get()->setup();
}

void TimeManager::setup()
{
  m_lastTime = clock();
  m_framesPerTurn = 10000;
  m_turn = 0;
  m_frame = 0;

  timer = new QTimer( this );
  connect( timer, SIGNAL(timeout()), this, SLOT(timerUpdate()) );
  timer->start( 10 );
}

#include <iostream>
using namespace std;

void TimeManager::updateFrames()
{
  m_turn += m_frame / m_framesPerTurn;
  m_frame %= m_framesPerTurn;

  if (m_turn < 0)
  {
    m_turn = 0;
    m_frame = 0;
  }

  if (m_turn >= m_numTurns)
  {
    m_turn = m_numTurns-1;
    m_frame = m_framesPerTurn-1;
  }
}

void TimeManager::timerUpdate()
{
  int milliseconds = ((clock() - m_lastTime) / CLOCKS_PER_SEC) * 1000;
  m_frame += milliseconds * m_speed;
  updateFrames();
  Renderer::refresh();
}

