#include "timeManager.h" 
#include "../renderer/renderer.h"

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
  m_lastTime = 0;
  m_framesPerTurn = 100;
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
  int t = 0;
  int frames;
  if( t > m_lastTime+m_speed )
  {
    frames = (t-m_lastTime)%m_speed;
    m_lastTime = t;
    m_frame += frames;
  }

  while( m_frame > m_framesPerTurn )
  {
    m_turn++;
    m_frame -= m_framesPerTurn;
  }
  //cout << m_turn << endl;
}

void TimeManager::timerUpdate()
{
  m_lastTime -= 100;
  updateFrames();
  Renderer::refresh();
}

