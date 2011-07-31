#ifndef PIRACY_H
#define PIRACY_H

#include "igame.h"
#include "parser/parser.h"
#include "parser/structures.h"
#include "piracyStack.h"
#include "stacks.h"

#include <QThread>
#include <vector>

namespace visualizer 
{
  class MoveList
  {
  public:
    enum _Move
    {
      Left,
      Right,
      Up,
      Down
    };

  private: 
    vector<_Move> m_moves;
    float m_x; 
    float m_y;

  public:
    MoveList( const float& x, const float& y, const vector<_Move>& moves );
    MoveList( const float& x, const float& y );

    bool operator < ( const MoveList& moveList ) const;
    bool operator == ( const MoveList& moveList ) const;
    bool operator != ( const MoveList& moveList ) const;

  };

  class Piracy: public QThread, public visualizer::IGame
  {
    Q_OBJECT;
    Q_INTERFACES( visualizer::IGame );
    public:
      Piracy();
      ~Piracy();
      LogRegex logFileInfo();
      void loadGamelog( std::string gamelog );
      void registerInterfaces( Interfaces intf );

      void run();

    private:
      Game *m_game;
      std::vector<std::list<Stack> > m_stackFrames;
      Interfaces m_intf;

      MoveList animationsToMoves( const int& x, const int& y, const std::vector<Animation *>& anims );
      MoveList getMoves( const Mappable& unit, const std::vector<GameState>::iterator& state );
      void updateAnimations
        ( 
        const Mappable& unit, 
        const std::vector<GameState>::iterator& state, 
        Stack& s
        );
  };

} // visualizer

#endif
