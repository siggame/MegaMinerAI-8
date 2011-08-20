#include "piracy.h"
#include "common.h"
#include "renderer/renderer.h"
#include "resourcemanager/texture.h"
#include "selectionrender/selectionrender.h"
#include "animations.h"
#include "scoreboard.h"

#include "stacks.h"

#include <iostream>
#include <time.h>

#define PIRATE_HEALTH 3
#define SHIP_HEALTH 12

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
    delete m_game;
    m_game = new Game;
    if( !parseFile( *m_game, gamelog.c_str() ) )
    {
      delete m_game;
      THROW( GameException, "Cannot Load The Gamelog" );
    }

    m_intf.resourceManager->loadResourceFile( "./plugins/piracy/textures.r" );

    /// @TODO We really need a good way of cleaning this up
    /// after a gamelog is done
    m_intf.animationEngine->registerFrameContainer( this );

    m_intf.timeManager->play();
    start();
  } /* Piracy::loadGamelog() */

  Piracy::Piracy()
  {
    cout << "Piracy is here" << endl;
    m_game = 0;
  }

  Piracy::~Piracy()
  {
    cout << "Piracy is done" << endl;
    delete m_game;
  }

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
  } /* Piracy::getMoves() */

  void Piracy::updateAnimations
    (
    const Mappable& unit,
    const std::vector<GameState>::iterator& state,
    Stack& s
    )
  {
    bool newAnim = false;
    int keyFrame = 0;

    if( !s.numKeyFrames() )
    {
      newAnim = true;
      s.addKeyFrame( new StartAnim( &s ) );
      s.a_x = s.m_x;
      s.a_y = s.m_y;
    }

    // @TODO: Typedef stuff like this.  This is rediculous
    std::map< int, std::vector<Animation*> >::iterator a = state->animations.find( unit.id );

    int x = s.a_x;
    int y = s.a_y;

    if( a != state->animations.end() )
    {
      for
        (
        std::vector<Animation*>::iterator i = a->second.begin();
        i != a->second.end();
        i++
        )
      {
        switch( (*i)->type )
        {
          case MOVE:
            keyFrame++;
            break;
          case TALK:
            {
              Talk* t = ((Talk*)(*i));
              s.addSubFrame( keyFrame, new TalkAnim( t->message ) );
            } break;
          case PIRATEATTACK:
          case SHIPATTACK:
            {
              Pirateattack* t = ((Pirateattack*)(*i));
              s.addSubFrame
                ( 
                keyFrame, 
                new AttackAnim
                  ( 
                  state->mappables[ t->victim ].x, 
                  state->mappables[ t->victim ].y 
                  ) 
                );
            } break;
          default:
            THROW( Exception, "Unknown Animation Used: %d", (*i)->type );
            break;
        }
      }
    }

    if( state->turnNumber > 0 )
    {
      if( newAnim )
      {
        if( (state-1)->pirates.find( unit.id ) != (state-1)->pirates.end() )
        {
          // Unit existed in last frame.  
          // Let's see if it moved
          x = (state-1)->pirates[ unit.id ].x;
          y = (state-1)->pirates[ unit.id ].y;

        }
        else if( (state-1)->ships.find( unit.id ) != (state-1)->ships.end() )
        {
          x = (state-1)->ships[ unit.id ].x;
          y = (state-1)->ships[ unit.id ].y;
        }
        else
        {
          x = unit.x;
          y = unit.y;
        }

        while( x != unit.x || y != unit.y )
        {
          if( unit.x > x )
          {
            x++;
            s.a_x--;
            s.addKeyFrame( new RightAnim() );
          }
          else if( unit.x < x )
          {
            x--;
            s.a_x++;
            s.addKeyFrame( new LeftAnim() );
          }
          else if( unit.y > y )
          {
            y++;
            s.a_y--;
            s.addKeyFrame( new DownAnim() );
          }
          else if( unit.y < y )
          {
            y--;
            s.a_y++;
            s.addKeyFrame( new UpAnim() );
          }
        }
      } 
    }

    if( newAnim )
    {
      s.addKeyFrame( new DrawStack( &s ) );
    }

  } // Piracy::updateAnimations()

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
    size_t frameNum = 0;

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
          // Load the background map
        }
    }

    for
      (
      std::vector<GameState>::iterator state = m_game->states.begin();
      state != m_game->states.end();
      state++
      )
    {
      StackOrganizer<MoveList, Stack> so;

      foreach( Pirate, pirates, i ) 
      {
        Stack &s = so.getStack( getMoves( i->second, state ) );
        s.m_pirates++;
        s.m_owner     =   i->second.owner;
        s.m_health    +=  i->second.health;
        s.m_maxHealth +=  PIRATE_HEALTH;
        s.m_gold      +=  i->second.gold;
        s.m_strength  +=  i->second.strength;
        s.m_x = i->second.x;
        s.m_y = i->second.y;
        s.m_pirateIds.push_back( i->first );
        s.Renderer    = m_intf.renderer;

        updateAnimations( i->second, state, s );
      }

      foreach( Ship, ships, i )
      {
        Stack &s = so.getStack( getMoves( i->second, state ) );
        s.m_ships++;
        s.m_owner     =   i->second.owner;
        s.m_health    +=  i->second.health;
        s.m_maxHealth +=  SHIP_HEALTH;
        s.m_gold      +=  i->second.gold;
        s.m_strength  +=  i->second.strength;
        s.m_x = i->second.x;
        s.m_y = i->second.y;
        s.m_shipIds.push_back( i->first );
        s.Renderer    = m_intf.renderer;

        updateAnimations( i->second, state, s );
      } 

      foreach( Port, ports, i )
      {
        // Ports don't animate.  Don't need to run getMoves on this one
        Stack &s = so.getStack( MoveList( i->second.x, i->second.y ) );
        s.m_ports++;
        s.m_owner     = i->second.owner;
        s.m_x = i->second.x;
        s.m_y = i->second.y;
        s.m_portIds.push_back( i->first );
        s.Renderer    = m_intf.renderer;

        updateAnimations( i->second, state, s );
      }

      foreach( Treasure, treasures, i )
      {
        // Treasure doesn't animate.  Don't need to run getMoves on this one
        Stack &s      = so.getStack( MoveList( i->second.x, i->second.y ) );
        s.m_gold      += i->second.gold;
        s.m_x = i->second.x;
        s.m_y = i->second.y;
        s.m_goldIds.push_back( i->first );
        s.Renderer    = m_intf.renderer;

        updateAnimations( i->second, state, s );
      }

      // @TODO: Add animators for the score, team names, etc. 
      m_intf.animationEngine->buildAnimations( so.returnStackList() );
      addFrame( so.returnStackList() );
      frameNum++;
      m_intf.timeManager->setNumTurns( frameNum );
      m_intf.timeManager->updateProgress( (float)frameNum/m_game->states.size() );

    }

    m_intf.timeManager->play();

#if 0
    THROW
      (
      Exception,
      "Time Elapsed: %i", 
      time.elapsed()
      );
#endif

  } // Piracy::run() 

  MoveList::MoveList( const float& x, const float& y, const vector<_Move>& moves )
  {
    m_x = x;
    m_y = y;

    m_moves = moves;
  } // MoveList::MoveList() 

  MoveList::MoveList( const float& x, const float& y )
  {
    m_x = x;
    m_y = y;
  } // MoveList::MoveList() 

  bool MoveList::operator < ( const MoveList& moveList ) const
  {
    size_t s1 = m_moves.size();
    size_t s2 = moveList.m_moves.size();
    if( s1 == s2 )
    {
      if( moveList.m_x == m_x )
      {
        if( moveList.m_y == m_y )
        {
          for( size_t i = 0; i < s1; i++ )
          {
            if( m_moves[ i ] < moveList.m_moves[ i ] )
            {
              return true;
            }
          }
        }
        else
        {
          return m_y < moveList.m_y;
        }
      }
      else
      {
        return m_x < moveList.m_x;
      }
    } 
    else
    {
      return s1 < s2;
    }

    return false;
  }

  bool MoveList::operator == ( const MoveList& moveList ) const
  {
    size_t s1 = m_moves.size();
    size_t s2 = moveList.m_moves.size();
    if( s1 == s2 )
    {
      if( moveList.m_x == m_x )
      {
        if( moveList.m_y == m_y )
        {
          for( size_t i = 0; i < s1; i++ )
          {
            if( m_moves[ i ] != moveList.m_moves[ i ] )
            {
              return false;
            }
          }
          return true;
        }
      }
    }

    return false;
  }

  bool MoveList::operator != ( const MoveList& moveList ) const
  {
    return !(*this == moveList);
  }

} // visualizer

Q_EXPORT_PLUGIN2( piracy, visualizer::Piracy );

