#include "frame.h"
#include "viruses.h"
#include "botnet.h"
#include "animations.h"

namespace visualizer
{
  BotNet::BotNet()
  {
    m_game = 0;
    m_timeline = 0;
  } // BotNet::BotNet()

  BotNet::~BotNet()
  {
    delete m_game;
    delete m_timeline;
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
#if 1
    cout << "Load BotNet Gamelog" << endl;
    
    delete m_game;
    delete m_timeline;
    m_game = new Game;
    m_timeline = new AnimSequence;

    if( !parseFile( *m_game, gamelog.c_str() ) )
    {
      delete m_game;
      delete m_timeline;
      THROW
        (
        GameException,
        "Cannot load gamelog: %s", 
        gamelog.c_str()
        );
    }

    resourceManager->loadResourceFile( "./plugins/botnet/textures.r" );

    size_t frameNum = 0;

    for
      (
      size_t state = 0; 
      state < m_game->states.size();
      state++
      )
    {
      Frame turn;

      Connectivity p1;
      Connectivity p2;

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

        if( t->owner == 0 )
        {
          p1.addNode( t->x, t->y, t );
        } else if( t->owner == 1 )

        {
          p2.addNode( t->x, t->y, t );
        }

        t->addKeyFrame( new Appear );
        t->addKeyFrame( new DrawTile( t ) );

        turn.addAnimatable( t );

      }
 
      for
        (
        std::map<int, Base>::iterator i = m_game->states[ state ].bases.begin();
        i != m_game->states[ state ].bases.end();
        i++
        )
      {
        base* b = new base( renderer );
        if( i->second.owner == 0 )
        {
          p1.addBase( i->second.x, i->second.y );
        } else
        {
          p2.addBase( i->second.x, i->second.y );
        }
        b->addKeyFrame( new StartAnim );
        b->id = i->second.id;
        b->x = i->second.x;
        b->y = i->second.y;
        b->owner = i->second.owner;

        b->addKeyFrame( new DrawBase( b ) );

        turn.addAnimatable( b );
      }

     
      p1.generateConnectivity();
      p2.generateConnectivity();
        
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

#if 0
        cout << "Anim size: " << m_game->states[ state ].animations.size() << endl;
        cout << "Anim size: " << m_game->states[ state ].animations[ v->id ].size() << endl;

        cout << "============" << endl;
        cout << v->id << endl;

        for
          (
          std::map< int, std::vector<Animation*> >::iterator j = m_game->states[ state ].animations.begin();
          j != m_game->states[ state ].animations.end();
          j++
          )
        {
          cout << "ID: " << j->first << endl;
          cout << "S: " << j->second.size() << endl;
        }

          std::vector<Animation*>::iterator j = m_game->states[ state ].animations[ v->id ].begin();
          j != m_game->states[ state ].animations[ v->id ].end();
          j++
          )
        {

        }
#endif
 

        for
          (
          std::vector<Animation*>::iterator j = m_game->states[ state ].animations[ v->id ].begin();
          j != m_game->states[ state ].animations[ v->id ].end();
          j++
          )
        {
          //cout << "ANIMATION" << endl;
#if 0
          switch( (*j)->type )
          {
            case COMBAT:
              cout << "Combat" << endl;
            break;
            case COMBINE:
              cout << "Combine" << endl;
            break;
            case CRASH:
              cout << "Crash" << endl;
            break;
            case CREATE:
              cout << "Create" << endl;
            break;
            case PLAYERTALK:
              cout << "Playertalk" << endl;
            break;
            case RECYCLE:
              cout << "Recycle" << endl;
            break;
            case VIRUSTALK:
              cout << "Virus Talk" << endl;
            break;
          }
#endif
        }
        
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

      m_timeline->addFrame( turn );
      
      frameNum++;

    }

    timeManager->setNumTurns( frameNum );

    animationEngine->registerFrameContainer( m_timeline );

    timeManager->play();
#endif

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
