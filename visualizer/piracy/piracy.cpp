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

  MoveList Piracy::getMoves( const Mappable& unit, const std::vector<GameState>::iterator& state )
  {
    std::map< int, std::vector<Animation*> >::iterator a = state->animations.find( unit.id );
    if( a != state->animations.end() )
    {
      return animationsToMoves( unit.x, unit.y, a->second );
    }
    else
    {
      return MoveList( unit.x, unit.y );
    }
  }

  void Piracy::run()
  {

// Undefine qt foreach macros
#undef foreach
// Special locally defined macros for iterating
// through our stl::maps
#define foreach( type, var, it ) \
  for \
    ( \
    std::map<int, type>::iterator it = state->var.begin(); \
    it != state->var.end(); \
    it++ \
    )

    QTime time;
    time.start();


    StackOrganizer<MoveList, Stack> so;

    if( m_game->states.size() >= 1 )
    {
      for
        ( 
        // Get the first tile in the first state
        std::map<int, Tile>::iterator i = m_game->states.begin()->tiles.begin(); 
        i != m_game->states.begin()->tiles.end();
        i++
        )
        {
        }
    }

    for
      (
      std::vector<GameState>::iterator state = m_game->states.begin();
      state != m_game->states.end();
      state++
      )
    {

      foreach( Pirate, pirates, i ) 
      {
        Stack &s = so.getStack( getMoves( i->second, state ) );
      }

      foreach( Ship, ships, i )
      {
        Stack &s = so.getStack( getMoves( i->second, state ) );
      } 

      foreach( Port, ports, i )
      {
        // Ports don't animate.  Don't need to run getMoves on this one

      }

      foreach( Treasure, treasures, i )
      {
        // Treasure doesn't animate.  Don't need to run getMoves on this one
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

