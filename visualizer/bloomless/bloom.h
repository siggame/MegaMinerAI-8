#ifndef BLOOM_H
#define BLOOM_H

#include "parser/parser.h"
#include "parser/structures.h"
#include "igame.h"
#include "animsequence.h"

namespace visualizer
{
  class Bloom: public AnimSequence, public visualizer::IGame
  {
    Q_OBJECT;
    Q_INTERFACES( visualizer::IGame );
    public:
      Bloom();
      ~Bloom();

      LogRegex logFileInfo();
      void loadGamelog( std::string gamelog );
    private:
      Game *m_game;

  }; // Bloom

} // visualizer

#endif
