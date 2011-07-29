#include "piracy.h"
#include "common.h"
#include "renderer/renderer.h"
#include "resourcemanager/texture.h"
#include "selectionrender/selectionrender.h"
#include "scoreboard.h"

#include "stacks.h"

#include <iostream>
#include <time.h>

typedef int idtype;

namespace visualizer
{

  LogRegex Piracy::logFileInfo()
  {
    LogRegex lr;
    lr.regex = "\(\"ident\"";
    lr.startSize = 9;
    
    return lr;
  } /* Piracy::logFileInfo() */

  void Piracy::registerInterfaces( Interfaces intf ) 
  {
    m_intf = intf;
  } /* Piracy::registerInterfaces() */

  void Piracy::loadGamelog( std::string gamelog )
  {
    m_game = new Game;
    if( !parseFile( *m_game, gamelog.c_str() ) )
    {
      delete m_game;
      THROW( GameException, "Cannot Load The Gamelog" );
    }

    start();

#if 0
    GameObject *go = new GameObject( 1 );
#if 0
    PirateMap *pm = new PirateMap();
#endif

    go = new GameObject( 2 );
    go->setGOC( SelectionRender );
    SelectionRender->setOwner( go );

    go = new GameObject( 3 );
    Scoreboard *sb = new Scoreboard();
    ResTexture res;
    res.load( "./textures/font1.png" );
    sb->loadFont( res.getTexture(), "./textures/font1.dat" );
    sb->parseScores( game );

    sb->setOwner( go );
    go->setGOC( sb );

    Renderer->registerConstantObj( 3, go );

    unsigned int numTurns = game.states.size();
    unsigned int numFrames = OptionsMan->getInt( "numFrames" );

    ObjectManager->setSize( numTurns, numFrames );

    TimeManager->setTurn( 0 );
    TimeManager->setNumTurns( numTurns );

    std::map<idtype, LookupSet<GameObject*, idtype> > looksets;
    unsigned int id;
#endif

#if 0
    Timeline t;
    Turn b;
#endif

#if 0
    for
      (
      std::vector<GameState>::iterator i = game.states.begin();
      i != game.states.end(); 
      i++ 
      )
    {

    }
#endif

  } /* Piracy::loadGamelog() */

  MoveList Piracy::animationsToMoves( const int& x, const int& y, const std::vector<Animation *>& anims )
  {
    std::vector<MoveList::_Move> moves;
    int mx = x;
    int my = y;
    for( std::vector<Animation*>::const_iterator i = anims.begin(); i != anims.end(); i++ )
    {
      if( (*i)->type == MOVE )
      {
        Move* m = ((Move*)*i);
        // Assuming only cardinal directions
        if( m->x > mx )
        {
          // RIGHT
          moves.push_back( MoveList::Right );
          mx++;
        } 
        else if( m->x < mx )
        {
          // LEFT
          moves.push_back( MoveList::Left );
          mx--;
        } 
        else if( m->y > my )
        {
          // DOWN 
          moves.push_back( MoveList::Down );
          my++;

        }
        else
        {
          // UP
          moves.push_back( MoveList::Up );
          my--;
        }
      }
    }

    return MoveList( x, y, moves );
  }

  void Piracy::run()
  {
    QTime time;
    time.start();

    StackOrganizer<MoveList, Stack> so;

    for
      (
      std::vector<GameState>::iterator state = m_game->states.begin();
      state != m_game->states.end();
      state++
      )
    {
      for
        (
        std::map<int,Pirate>::iterator j = state->pirates.begin();
        j != state->pirates.end();
        j++
        )
      {
        Stack *s;
        std::map< int, std::vector<Animation*> >::iterator a = state->animations.find( j->second.id );
        if( a != state->animations.end() )
        {
          MoveList ml = animationsToMoves( j->second.x, j->second.y, a->second );

          s = &so.getStack( ml );
        }

      }

      for
        (
        std::map<int,Ship>::iterator j = state->ships.begin();
        j != state->ships.end();
        j++ 
        )
      {
      }
    }

    delete m_game;
    THROW
      (
      Exception,
      "Time Elapsed: %i", 
      time.elapsed()
      );

  } /* Piracy::run() */

} // visualizer

Q_EXPORT_PLUGIN2( piracy, visualizer::Piracy );

