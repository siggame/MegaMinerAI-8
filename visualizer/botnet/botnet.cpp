#include "frame.h"
#include "viruses.h"
#include "botnet.h"
#include "animations.h"

namespace visualizer
{
  BotNet::BotNet()
  {
    m_game = 0;
  } // BotNet::BotNet()

  BotNet::~BotNet()
  {
    delete m_game;
  } // BotNet::~BotNet()

  LogRegex BotNet::logFileInfo()
  {
    LogRegex lr;
    lr.regex = "Base";
    lr.startSize = 1000;

    return lr;
  } // BotNet::logFileInfo()

  void BotNet::loadGamelog( std::string gamelog )
  {
    cout << "Load BotNet Gamelog" << endl;
    
    delete m_game;
    m_game = new Game;

    if( !parseFile( *m_game, gamelog.c_str() ) )
    {
      delete m_game;
      THROW
        (
        GameException,
        "Cannot load gamelog: %s", 
        gamelog.c_str()
        );
    }

    size_t frameNum = 0;

    for
      (
      size_t state = 0; 
      state < m_game->states.size();
      state++
      )
    {
      Frame turn;

      for
        (
        std::map<int, Tile>::iterator i = m_game->states[ state ].tiles.begin();
        i != m_game->states[ state ].tiles.end();
        i++ 
        )
      {
        tile* t = new tile( renderer );
        t->addKeyFrame( new StartAnim );
        t->id = i->second.id;
        t->x = i->second.x;
        t->y = i->second.y;
        t->owner = i->second.owner;

        t->addKeyFrame( new DrawTile( t ) );

        turn.addAnimatable( t );

      }
        
      for
        (
        std::map<int, Virus>::iterator i = m_game->states[ state ].viruses.begin();
        i != m_game->states[ state ].viruses.end();
        i++ 
        )
      {
        virus* v = new virus( renderer );

        v->addKeyFrame( new StartVirus( v ) );
        v->id = i->second.id;
        v->owner = i->second.owner;
        v->x = i->second.x;
        v->y = i->second.y;

        switch( checkForMovement( m_game, state, i->second.id ) )
        {
          case 0: // Left
            v->addKeyFrame( new LeftAnim );
            v->x++;
          break;
          case 1: // Right
            v->addKeyFrame( new RightAnim );
            v->x--;
          break;
          case 2: // Up
            v->addKeyFrame( new UpAnim );
            v->y--;
          break;
          case 3: // Down
            v->addKeyFrame( new DownAnim );
            v->y++;
          break;
        }

        v->level = i->second.level;
        v->movesLeft = i->second.movesLeft;
        v->addKeyFrame( new DrawVirus( v ) );

        turn.addAnimatable( v );

      }

      animationEngine->buildAnimations( turn );

      addFrame( turn );
      
      frameNum++;

    }

    timeManager->setNumTurns( frameNum );

    animationEngine->registerFrameContainer( this );

    timeManager->play();

  } // BotNet::loadGamelog() 

  size_t BotNet::checkForMovement( Game* g, const size_t& state, const int& id )
  {
    if( state > 0 )
    {
      std::map<int,Virus>::iterator k = g->states[ state - 1 ].viruses.find( id );
      if( k != g->states[ state - 1 ].viruses.end() )
      {
        // He exists. 
        Virus* prev = &k->second;
        Virus* cur = &g->states[ state ].viruses[ id ];

        if( cur->x > prev->x )
        {
          return 1;
        } 
        else if( cur->x < prev->x )
        {
          return 0;
        }
        else if( cur->y > prev->y )
        {
          return 2;
        }
        else if( cur->y < prev->y )
        {
          return 3;
        }

      }
    }

    // No anim
    return -1;

  } // BotNet::checkForMovement()

} // visualizer

Q_EXPORT_PLUGIN2( botnet, visualizer::BotNet );
