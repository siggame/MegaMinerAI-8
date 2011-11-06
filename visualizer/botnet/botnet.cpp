#include "frame.h"
#include "viruses.h"
#include "botnet.h"
#include "animations.h"
#include "virus-builder.h" // for jacob fischer's random virus building
#include <sstream>

namespace visualizer
{

  Log errorLog( "botnetLog.log" );

  BotNet::BotNet()
  {
    m_game = 0;
    m_timeline = 0;
  } // BotNet::BotNet()

  BotNet::~BotNet()
  {
    terminate();
    wait();
    animationEngine->registerFrameContainer( 0 );
    delete m_timeline;
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

    // Make sure we're not still loading a previous gamelog
    terminate();
    wait();

    // Reset the animation engine.  
    animationEngine->registerFrameContainer( 0 );
    
    // Clean up any old games.
    delete m_game;
    delete m_timeline;

    m_game = new Game;
    m_timeline = new AnimSequence;

    if( !parseString( *m_game, gamelog.c_str() ) )
    {
      delete m_game;
      delete m_timeline;
      m_game = 0;
      m_timeline = 0;
      errorLog << gamelog;
      THROW
        (
        GameException,
        "Cannot load gamelog", 
        gamelog.c_str()
        );
    }

    float w = m_game->states[ 0 ].width;
    float h = m_game->states[ 0 ].height + 1.5f;

    renderer->setCamera( 0, 0, w, h );
    renderer->setUnitSize( w, h );

    resourceManager->loadResourceFile( "./plugins/botnet/textures.r" );
    
    // build the two player viruses
    for(int playerid = 0; playerid < 2; playerid++)
    {
      stringstream displayListId;
      displayListId << "PlayerVirus-" << playerid;
      
      renderer->beginList(displayListId.str());
      
      bool **pixels = buildVirus(m_game->states[0].players[playerid].playerName);
      
      for(int x = 0; x < 16; x++)
        for(int y = 0; y < 16; y++)
          if(pixels[x][y])
          {
            // set the pixel's color to the team's color
            renderer->setColor( ( playerid == 0 ? Color( 0.6f + (0.0125f * (double)(x + y)), 0, 0) : Color(0, 0, 0.6f + 0.125f * (double)(x + y) ) ) );
            
            //draw the main block of the pixel
            renderer->drawQuad( (x * 0.0625), (y * 0.0625), 0.0625, 0.0625);
            
            // the border's color
            renderer->setColor( Color(1,1,1, 0.35) );
            
            //check to see if we need a border
            if(x - 1 < 0 || !pixels[x - 1][y])  // left
              renderer->drawLine
              (
                (  x   * 0.0625),
                (  y   * 0.0625),
                (  x   * 0.0625),
                ((y+1) * 0.0625),
                1.0
              );
                
            if(x + 1 == 16 || !pixels[x + 1][y])  // right
              renderer->drawLine
              (
                ((x+1) * 0.0625),
                (  y   * 0.0625),
                ((x+1) * 0.0625),
                ((y+1) * 0.0625),
                1.0
              );
                
            if(y - 1 < 0 || !pixels[x][y - 1])  // up
              renderer->drawLine
              (
                (  x   * 0.0625),
                (  y   * 0.0625),
                ((x+1) * 0.0625),
                (  y   * 0.0625),
                1.0
              );
                
            if(y + 1 == 16 || !pixels[x][y + 1])  // down
              renderer->drawLine
              (
                (  x   * 0.0625),
                ((y+1) * 0.0625),
                ((x+1) * 0.0625),
                ((y+1) * 0.0625),
                1.0
              );
          }
    
      renderer->setColor( ( playerid == 0 ? Color( 0.6f, 0, 0) : Color(0, 0, 0.6f ) ) );
      renderer->endList(displayListId.str());
    }
    
    start();

  }

  void BotNet::run()
  {

#ifdef __DEBUG__
    cout << "Loading Gamelog..." << endl;
#endif

    size_t frameNum = 0;

    SmartPointer<background> b = new background( renderer );
    SmartPointer<grid> g = new grid( renderer );
    SmartPointer<moveBoard> mb = new moveBoard( renderer );
    
    // offset for the score to be rendered at the top
    mb->offst = 2.5f;
    mb->addKeyFrame( new PushBoard( mb ) );
    
    if (m_game->states[0].height > 0 && m_game->states[0].width > 0)
    {
      b->mapHeight = m_game->states[0].height;
      b->mapWidth  = m_game->states[0].width;
      
      g->mapHeight = m_game->states[0].height;
      g->mapWidth  = m_game->states[0].width;
      
      g->pixelWidth  = renderer->width();
      g->pixelHeight = (renderer->width() * m_game->states[0].height)/m_game->states[0].width;
    }
    else
    {
      THROW(Exception, "Game's height and width not set!");
    }
    
    b->addKeyFrame( new DrawBackground( b ) );
    g->addKeyFrame( new DrawGrid( g ) );
 
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
      
      turn.addAnimatable( mb );
      turn.addAnimatable( b );
      
      
      
      // BEGIN: Draw Tiles
      int numNeutralTiles = 0;
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
          p1.addNode( t->x, t->y, t );
        else if( t->owner == 1 )
          p2.addNode( t->x, t->y, t );
        else if( t->owner == 2 )
          numNeutralTiles++;

        t->addKeyFrame( new Appear );
        t->addKeyFrame( new DrawTile( t ) );

        turn.addAnimatable( t );
      }
      // END: Draw Tiles
      
      
      
      // BEGIN: Draw Bases
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
      // END: Draw Bases

     
      p1.generateConnectivity();
      p2.generateConnectivity();
      
      

      // BEGIN: Draw Scoreboard
      scoreboard* score1 = new scoreboard( renderer );
      scoreboard* score2 = new scoreboard( renderer );

      score1->score = m_game->states[ state ].players[ 0 ].byteDollars;
      score1->cycles = m_game->states[ state ].players[ 0 ].cycles;
      score1->connectedTiles = p1.numConnectedNodes;
      score1->unconnectedTiles = p1.numUnconnectedNodes;
      score1->player = 0;
      score1->x = 1.0f;
      score1->y = 0.2f;
      score1->teamName = m_game->states[ state ].players[ 0 ].playerName;
      score1->mapWidth  = m_game->states[0].width;
      score1->enemyScore = m_game->states[ state ].players[ 1 ].byteDollars;
      score1->neutralTiles = numNeutralTiles;
      
      score2->score = m_game->states[ state ].players[ 1 ].byteDollars;
      score2->cycles = m_game->states[ state ].players[ 1 ].cycles;
      score2->connectedTiles = p2.numConnectedNodes;
      score2->unconnectedTiles = p2.numUnconnectedNodes;
      score2->player = 1;
      score2->y = 0.2f;
      score2->x = m_game->states[ 0 ].width-1;
      score2->teamName = m_game->states[ state ].players[ 1 ].playerName;
      score2->mapWidth  = m_game->states[0].width;
      score2->enemyScore = m_game->states[ state ].players[ 0 ].byteDollars;
      if(state > 0)
        score2->addKeyFrame
        (
            new ScoreAnim
            (
                m_game->states[ state - 1 ].players[ 0 ].byteDollars, 
                m_game->states[ state - 1 ].players[ 1 ].byteDollars,
                m_game->states[ state ].players[ 0 ].byteDollars,
                m_game->states[ state ].players[ 1 ].byteDollars
            )
        );
        
      score1->addKeyFrame( new DrawScore( score1 ) );
      score2->addKeyFrame( new DrawScore( score2 ) );

      turn.addAnimatable( score1 );
      turn.addAnimatable( score2 );
      // END: Draw Scoreboard


      
      // Draw Grid
      turn.addAnimatable( g );

      for
        ( 
        std::map<int, vector<Animation*> >::iterator i = m_game->states[ state ].animations.begin();
        i != m_game->states[ state ].animations.end();
        i++ 
        )
      {
        for
          (
          std::vector<Animation*>::iterator j = i->second.begin();
          j != i->second.end();
          j++
          )
        {
          switch( (*j)->type )
          {
            case COMBINE:
            {
              Animation& a = (Animation&)*(*j);
              Combine &c = (Combine&)*(*j);
              virus* v = new virus( renderer );
              v->addKeyFrame( new StartVirus( v ) );
              Coord prevCoord( m_game->states[ state - 1 ].viruses[ c.moving ].x, m_game->states[ state - 1 ].viruses[ c.moving ].y );
              Coord curCoord( m_game->states[ state - 1 ].viruses[ c.stationary ].x, m_game->states[ state - 1 ].viruses[ c.stationary ].y );
              v->id = c.moving;

              v->x = prevCoord.x;
              v->y = prevCoord.y;
              v->level = m_game->states[ state - 1 ].viruses[ c.moving ].level;
              v->owner = m_game->states[ state - 1 ].viruses[ c.moving ].owner;
              if( curCoord.x > prevCoord.x )
                v->addKeyFrame( new RightAnim );
              else if( curCoord.x < prevCoord.x )
                v->addKeyFrame( new LeftAnim );
              else if( curCoord.y > prevCoord.y )
                v->addKeyFrame( new UpAnim );
              else
                v->addKeyFrame( new DownAnim );
              v->addKeyFrame( new DrawVirus( v ) );
              turn.addAnimatable( v );
 
            } break;
          }
        }
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

        for
          (
          std::vector<Animation*>::iterator j = m_game->states[ state ].animations[ v->id ].begin();
          j != m_game->states[ state ].animations[ v->id ].end();
          j++
          )
        {
          //cout << "ANIMATION" << endl;
#if 1
          switch( (*j)->type )
          {
            case COMBAT:
              //cout << "Combat" << endl;
            break;
            case CRASH:
             // Crash* thing = &(*j);
             // v.
             // cout << "Crash" << endl;
            break;
            case CREATE:
              //cout << "Create" << endl;
            break;
            case PLAYERTALK:
              //cout << "Playertalk" << endl;
            break;
            case RECYCLE:
              //cout << "Recycle" << endl;
            break;
            case VIRUSTALK:
              //cout << "Virus Talk" << endl;
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
      
      timeManager->setMaxTurns( frameNum );

      if( frameNum <= 1 )
      {
        timeManager->setTurn( 0 );
        animationEngine->registerFrameContainer( m_timeline );
        timeManager->play();
        timeManager->setNumTurns( m_game->states.size() );
      }

    }

#ifdef __DEBUG__
    cout << "Done Loading That Gamelog..." << endl;
#endif

  } // BotNet::run() 

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
