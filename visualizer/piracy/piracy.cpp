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

    m_intf.renderer->registerFrameContainer( this );

    start();
  } /* Piracy::loadGamelog() */

  Piracy::Piracy()
  {
    m_game = 0;
  }

  Piracy::~Piracy()
  {
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

    IAnimator& animator = s.getAnimationSequence( m_intf.animationEngine );

    if( !animator.numKeyFrames() )
    {
      newAnim = true;
      animator.addKeyFrame( new StartAnim( &s ) );
    }

    // @TODO: Typedef stuff like this.  This is rediculous
    std::map< int, std::vector<Animation*> >::iterator a = state->animations.find( unit.id );

    int x = s.m_x;
    int y = s.m_y;

    // No aminations.
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
            if( newAnim )
            {
              Move* m = ((Move*)(*i));
              if( m->x > x )
              {
                animator.addKeyFrame( new RightAnim() );
                x++;
              }
              else if( m->x < x )
              {
                animator.addKeyFrame( new LeftAnim() );
                x--;
              }
              else if( m->y > y )
              {
                animator.addKeyFrame( new DownAnim() );
                y++;
              }
              else
              {
                animator.addKeyFrame( new UpAnim() );
                y--;
              }
            }
            keyFrame++;
            break;
          case TALK:
            {
              Talk* t = ((Talk*)(*i));
              animator.addSubFrame( keyFrame, new TalkAnim( t->message ) );
            } break;
          case ATTACK:
            {
              Attack* t = ((Attack*)(*i));
              animator.addSubFrame
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
        s.m_x         = i->second.x;
        s.m_y         = i->second.y;
        s.m_pirateIds.push_back( i->first );

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
        s.m_x         = i->second.x;
        s.m_y         = i->second.y;
        s.m_shipIds.push_back( i->first );

        updateAnimations( i->second, state, s );
      } 

      foreach( Port, ports, i )
      {
        // Ports don't animate.  Don't need to run getMoves on this one
        Stack &s = so.getStack( MoveList( i->second.x, i->second.y ) );
        s.m_ports++;
        s.m_owner = i->second.owner;
        s.m_x     = i->second.x;
        s.m_y     = i->second.y;
        s.m_portIds.push_back( i->first );

        updateAnimations( i->second, state, s );
      }

      foreach( Treasure, treasures, i )
      {
        // Treasure doesn't animate.  Don't need to run getMoves on this one
        Stack &s  = so.getStack( MoveList( i->second.x, i->second.y ) );
        s.m_gold  += i->second.gold;
        s.m_x     = i->second.x;
        s.m_y     = i->second.y;
        s.m_goldIds.push_back( i->first );

        updateAnimations( i->second, state, s );
      }

      // @TODO: Add animators for the score, team names, etc. 
      m_intf.animationEngine->buildAnimations( so.returnStackList() );
      addFrame( so.returnStackList() );
      frameNum++;
      m_intf.timeManager->updateProgress( (float)frameNum/m_game->states.size() );

    }

    THROW
      (
      Exception,
      "Time Elapsed: %i", 
      time.elapsed()
      );

  } /* Piracy::run() */

  MoveList::MoveList( const float& x, const float& y, const vector<_Move>& moves )
  {
    m_x = x;
    m_y = y;

    m_moves = moves;
  } /* MoveList::MoveList() */

  MoveList::MoveList( const float& x, const float& y )
  {
    m_x = x;
    m_y = y;
  } /* MoveList::MoveList() */

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
    } else
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

