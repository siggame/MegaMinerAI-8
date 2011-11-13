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
    m_suicide = false;
    setTerminationEnabled();
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
#ifdef __DEBUG__
    cout << "Load BotNet Gamelog" << endl;
#endif

    if( isRunning() )
    {
      m_suicideMutex.lock();
        m_suicide = true;
      m_suicideMutex.unlock();
      wait();
    }


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
    float h = m_game->states[ 0 ].height + 2.5f;

    renderer->setCamera( 0, 0, w, h );
    renderer->setUnitSize( w, h );

    resourceManager->loadResourceFile( "./plugins/botnet/textures.r" );

    renderer->beginList( "drawHeader" );
      for(int x = 0; x < m_game->states[ 0 ].width * 2; x++)
        for(int y = 0; y < 5; y++)
        {
            double num = (rand()%5)/40.0f;
            renderer->setColor( Color( num, num, num) );
            renderer->drawQuad( x/2.0, y/2.0, 0.5, 0.5);
        }
    renderer->endList( "drawHeader" );

    renderer->beginList( "backgroundDraw" );
      renderer->setColor( Color( 0.05f, 0.05f, 0.05f ) );
      renderer->drawQuad( 0, 0, m_game->states[ 0 ].width, m_game->states[ 0 ].height );

      renderer->setColor( Color( 1.0, 1.0, 1.0 ) );
      for ( int x = 0; x < m_game->states[ 0 ].width; x += 4 )
      {
        for ( int y = 0; y < m_game->states[ 0 ].height; y+= 4 )
        {
          renderer->drawTexturedQuad( x, y, 4, 4 , "nodeBackground" );

        }
      }
    renderer->endList( "backgroundDraw" );
    
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
      
      // free up memory from creatings the viruses pixels
      for(int i = 0; i < 16; i++)
        delete pixels[i];
      
      delete pixels;
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
    
    bool isArenaMode = true;
    bool willyTime = false;
    
    string talkStrings[] = {"", ""};
    
    // Go through the game and build everything to draw!
    for
      (
      size_t state = 0; 
      state < m_game->states.size() + isArenaMode && !m_suicide;
      state++
      )
    {
      bool drawArenaWinner = false;
      size_t originalState = state;
      
      if(state >= m_game->states.size())
      {
        state = m_game->states.size() - 1;
        drawArenaWinner = true;
      }
      
      Frame turn;

      turn.addAnimatable( mb );
      turn.addAnimatable( b );
      
      // BEGIN: Draw Tiles
      int tileCounts[] = { 0, 0, 0, 0 };
      
      tile ***tiles = new tile**[(int)m_game->states[0].width];
      for(int x = 0; x < m_game->states[0].width; x++)
        tiles[x] = new tile*[(int)m_game->states[0].height];
      
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
        
        tiles[(int)t->x][(int)t->y] = t;
        
        tileCounts[(int)t->owner]++;
          
        t->addKeyFrame( new Appear );
        t->addKeyFrame( new DrawTile( t ) );

        turn.addAnimatable( t );
      }

      
      vector<tile*> mainBlobs[2];
      for(int x = 0; x < m_game->states[0].width; x++)
      {
        for(int y = 0; y < m_game->states[0].height; y++)
        {
          if(tiles[x][y]->owner < 2 && tiles[x][y]->connectedTo == NULL && tiles[x][y]->numConnectedTiles == 0) // if the owner is player 1 or 2 and they havn't been connected to a blob we need to flood fill it to see how large that blob is
          {
            stack<tile*> currentBlob;
            vector<tile*> completeBlob;
            tile *parentTile = tiles[x][y];
              
            currentBlob.push(parentTile);
            
            int loopCount = 0;
            
            while(!currentBlob.empty() && loopCount < 10000)
            {
              loopCount++;
              // if the current tile we are looking at is ours it is connected to the blob, so add
              tile *currentTile = currentBlob.top();
              currentBlob.pop();
              
              // if the tile we are looking at is owned bu the parent's owner and is not connected to another blog is it part of the blob, so add it to the blob...
              if(currentTile->owner == parentTile->owner && currentTile->connectedTo == NULL)
              {
                parentTile->numConnectedTiles++;
                //if(*currentTile != *parentTile)
                currentTile->connectedTo = parentTile;
                completeBlob.push_back(currentTile);
                
                // ... and seed more positions (not off the map).
                if(currentTile->x + 1 < m_game->states[0].width)
                  currentBlob.push(tiles[(int)currentTile->x + 1][(int)currentTile->y]);
                if(currentTile->y + 1 < m_game->states[0].height)
                  currentBlob.push(tiles[(int)currentTile->x][(int)currentTile->y + 1]);
                if(currentTile->x - 1 >= 0)
                  currentBlob.push(tiles[(int)currentTile->x - 1][(int)currentTile->y]);
                if(currentTile->y - 1 >= 0)
                  currentBlob.push(tiles[(int)currentTile->x][(int)currentTile->y - 1]);
              }
            }
            
            if(completeBlob.size() > mainBlobs[parentTile->owner].size())
              mainBlobs[parentTile->owner] = completeBlob;
            
          }
        }
      }
      
      int connectedTiles[] = {0, 0};
      
      for(int owner = 0; owner < 2; owner++)
      {
        for (int i = 0; i < mainBlobs[owner].size(); i++)
        {
          if(!tiles[(int)mainBlobs[owner][i]->x][(int)mainBlobs[owner][i]->y]->mainBlob)
          {
            tiles[(int)mainBlobs[owner][i]->x][(int)mainBlobs[owner][i]->y]->mainBlob = true;
            connectedTiles[owner]++;
          }
        }
      }
      // END: Draw Tiles

      for(int x = 0; x < m_game->states[0].width; x++)
        delete [] tiles[x];
      delete [] tiles;
      
      // BEGIN: Draw Bases
      for
        (
        std::map<int, Base>::iterator i = m_game->states[ state ].bases.begin();
        i != m_game->states[ state ].bases.end();
        i++
        )
      {
        SmartPointer< base > b = new base( renderer );

        b->addKeyFrame( new StartAnim );
        b->id = i->second.id;
        b->x = i->second.x;
        b->y = i->second.y;
        b->owner = i->second.owner;

        b->addKeyFrame( new DrawBase( b ) );

        turn.addAnimatable( b );
      }
      // END: Draw Bases
      

      // BEGIN: Draw Scoreboard
      SmartPointer< scoreboard >  score1 = new scoreboard( renderer );
      SmartPointer< scoreboard > score2 = new scoreboard( renderer );

      score1->score = m_game->states[ state ].players[ 0 ].byteDollars;
      score1->cycles = m_game->states[ state ].players[ 0 ].cycles;
      score1->connectedTiles = connectedTiles[0];
      score1->unconnectedTiles = tileCounts[0] - connectedTiles[0];
      score1->enemyConnectedTiles = connectedTiles[1];
      score1->enemyUnconnectedTiles = tileCounts[1] - connectedTiles[1];
      score1->player = 0;
      score1->x = 1.0f;
      score1->y = 0.2f;
      score1->teamName = m_game->states[ state ].players[ 0 ].playerName;
      score1->mapWidth  = m_game->states[0].width;
      score1->enemyScore = m_game->states[ state ].players[ 1 ].byteDollars;
      score1->neutralTiles = tileCounts[2];
      
      score2->score = m_game->states[ state ].players[ 1 ].byteDollars;
      score2->cycles = m_game->states[ state ].players[ 1 ].cycles;
      score2->connectedTiles = connectedTiles[1];
      score2->unconnectedTiles = tileCounts[1] - connectedTiles[1];
      score2->enemyConnectedTiles = connectedTiles[0];
      score2->enemyUnconnectedTiles = tileCounts[0] - connectedTiles[0];
      score2->player = 1;
      score2->y = 0.2f;
      score2->x = m_game->states[ 0 ].width-1;
      score2->teamName = m_game->states[ state ].players[ 1 ].playerName;
      score2->mapWidth  = m_game->states[0].width;
      score2->enemyScore = m_game->states[ state ].players[ 0 ].byteDollars;
      score2->neutralTiles = tileCounts[2];
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
        std::map<int, vector< SmartPointer< Animation> > >::iterator i = m_game->states[ state ].animations.begin();
        i != m_game->states[ state ].animations.end();
        i++ 
        )
      {
        for
          (
          std::vector< SmartPointer< Animation > >::iterator j = i->second.begin();
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

              SmartPointer< virus > v = new virus( renderer );

              v->addKeyFrame( new StartVirus( v ) );

              Coord prevCoord( m_game->states[ state - 1 ].viruses[ c.moving ].x, m_game->states[ state - 1 ].viruses[ c.moving ].y );
              Coord curCoord( m_game->states[ state ].viruses[ c.stationary ].x, m_game->states[ state ].viruses[ c.stationary ].y );
              
              v->id = c.moving;

              v->x = prevCoord.x;
              v->y = prevCoord.y;
              v->level = m_game->states[ state - 1 ].viruses[ c.moving ].level + 1;
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


      for( size_t p = 0; p < 2; p++ )
      {
        
        //if( !m_game->states[ state ].animations[ p ].size() )
          //continue;
        
        if( m_game->states[ state ].animations[ p ].size() )
        {
          // BEGIN: Draw Talk
          PlayerTalk* t = (PlayerTalk*)&*m_game->states[ state ].animations[ p ][ 0 ]; 
          if( t->type == PLAYERTALK )
          {
            stringstream ssTalk;
            ssTalk << "(" << state << "): " << t->message;
            
            if(string(t->message).length() > 0)
              talkStrings[p] = ssTalk.str();
            
            if(string(t->message).find("Wooly Willy") != string::npos)
              willyTime = true;
          }
        }
        
        SmartPointer< talker > b = new talker( renderer );

        b->addKeyFrame( new StartAnim );
        b->player = p;
        b->message = talkStrings[p];
        b->addKeyFrame( new DrawTalk( b ) );

        turn.addAnimatable( b );
        // END: Draw TALK
      }

     
      for
        (
        std::map<int, Virus>::iterator i = m_game->states[ state ].viruses.begin();
        i != m_game->states[ state ].viruses.end();
        i++ 
        )
      {
        if( i->second.id == 0 )
          continue;
        SmartPointer< virus > v = new virus( renderer );

        v->addKeyFrame( new StartVirus( v ) );
        v->id = i->second.id;
        v->owner = i->second.owner;
        v->x = i->second.x;
        v->y = i->second.y;

        for
          (
          std::vector< SmartPointer< Animation > >::iterator j = m_game->states[ state ].animations[ v->id ].begin();
          j != m_game->states[ state ].animations[ v->id ].end();
          j++
          )
        {
#if 1
          switch( (*j)->type )
          {
            case COMBAT:
              //cout << "Combat" << endl;
            break;
            case CRASH:
            {
              Crash* c = (Crash*)&*(*j);
              if( c->dx-v->x > 0 )
              {
                v->addKeyFrame( new CrashRight( timeManager->getSpeed() ) );
              }
              else if( c->dx-v->x < 0 )
              {
                v->addKeyFrame( new CrashLeft( timeManager->getSpeed() ) );
              } 
              else if( c->dy-v->y > 0 )
              {
                v->addKeyFrame( new CrashDown( timeManager->getSpeed() ) );
              }
              else
              {
                v->addKeyFrame( new CrashUp( timeManager->getSpeed() ) );
              }

            } break;
            case CREATE:
              //cout << "Create" << endl;
            break;
            case PLAYERTALK:
            {
              PlayerTalk* t = (PlayerTalk*)&*(*j);
              cout << t->message << endl;

            } break;
            case RECYCLE:
              //cout << "Recycle" << endl;
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
      
      // BEGIN: Draw the Arena Winner
      if(drawArenaWinner)
      {
        ArenaWinner *aw = new ArenaWinner
        ( 
            renderer,
            timeManager,
            m_game->winner,
            m_game->states[0].players[ m_game->winner ].playerName,
            m_game->winReason,
            (int)m_game->states[0].width,
            (int)m_game->states[0].height,
            willyTime
        );
        
        aw->addKeyFrame( new StartAnim );
        aw->addKeyFrame( new ArenaWinnerAnim(timeManager) );
        aw->addKeyFrame( new DrawArenaWinner( aw, options->getFloat( "winSpeed" ) ) );
        turn.addAnimatable( aw );
        
        state = originalState;
      }
      // END: Draw the Arena Winner
      
      animationEngine->buildAnimations( turn );

      m_timeline->addFrame( turn );
      
      frameNum++;
      
      timeManager->setMaxTurns( frameNum );

      if( frameNum <= 1 )
      {
        timeManager->setTurn( 0 );
        animationEngine->registerFrameContainer( m_timeline );
        timeManager->play();
        timeManager->setNumTurns( m_game->states.size() + isArenaMode );
      }

    }

#ifdef __DEBUG__
    cout << "Done Loading That Gamelog..." << endl;
#endif

    m_suicideMutex.lock();
      m_suicide = false;
    m_suicideMutex.unlock();

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
