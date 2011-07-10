#ifndef GAMES_H
#define GAMES_H

#include <QtGui>

#include "common.h"
#include "igame.h"


class _Games: public Module
{
  public:
  
    static void setup();
    void _setup();
    static void destroy();

  private:
    std::vector< IGame* > m_gameList;

};

extern _Games *Games;

#endif
