#ifndef VIRUSES_H
#define VIRUSES_H

#include "animatable.h"
#include "irenderer.h"
#include "connectivity.h"
#include "igame.h"

namespace visualizer
{ 

  struct GeneralAnim: public AnimData
  {
    float alpha;
  };

  struct VirusData: public GeneralAnim
  {
    float x;
    float y;
  };
  
  struct ScoreData: public GeneralAnim
  {
    double drawnOffset;
    double blueOffset;
  };
  
  struct ArenaWinnerData: public GeneralAnim
  {
    float **fadeInBoard;
  };

  struct moveBoard: public Animatable
  {
    moveBoard( IRenderer *renderer ) : Animatable( renderer )
    {}

    float offst;

    AnimData* getData()
    {
      return 0;
    }
  };

  struct virus: public Animatable
  {
    virus( IRenderer *renderer ) : Animatable( renderer )
    { owner = level = movesLeft = id = x = y = 0; pixels = NULL; }

    int id;
    int owner;
    int level;
    int movesLeft;
    float x;
    float y;
    bool **pixels;

    AnimData* getData()
    {
      return &m_virusData;
    }

    VirusData m_virusData;
    
    
  }; // Virus

  struct talker: public Animatable
  {
    talker( IRenderer *renderer ) : Animatable( renderer )
    { player = 0; }

    AnimData* getData()
    { return 0; }

    char player;
    string message;

  };

  struct base: public Animatable
  {
    base( IRenderer *renderer ) : Animatable( renderer )
    { owner = id = x = y = 0; }

    int id;
    int owner;
    float x;
    float y;

    AnimData* getData()
    {
      return &g;
    }

    GeneralAnim g;

  }; // base

  struct tile: public Animatable
  {
    tile( IRenderer *renderer ) : Animatable( renderer )
    { owner = id = x = y = numConnectedTiles = 0; connectedTo = NULL; mainBlob = false; }

    int id;
    int owner;
    float x;
    float y;
    bool mainBlob;
    
    tile *connectedTo;
    int numConnectedTiles;

    AnimData* getData()
    {
      return &g;
    }

    GeneralAnim g;

  }; // tile
  
  struct background: public Animatable
  {
    background( IRenderer *renderer ) : Animatable( renderer )
    { }
    
    int mapWidth;
    int mapHeight;
    
    AnimData* getData()
    {
      return NULL;
    }
  }; // background
  
  struct grid: public Animatable
  {
    grid( IRenderer *renderer ) : Animatable( renderer )
    { }
    
    int mapWidth;
    int mapHeight;
    
    int pixelHeight;
    int pixelWidth;
    
    AnimData* getData()
    {
      return NULL;
    }
  }; // grid

  struct scoreboard: public Animatable
  {
    scoreboard( IRenderer* renderer ) : Animatable( renderer )
    { }

    float x, y;
    
    int mapWidth;
    bool **virusPixels;
    
    int player;
    int score;
    int cycles;
    int connectedTiles;
    int unconnectedTiles;
    int neutralTiles;
    int enemyConnectedTiles;
    int enemyUnconnectedTiles;
    int enemyScore;
    
    string teamName;

    
    AnimData* getData()
    {
      return &m_scoreData;
    }

    ScoreData m_scoreData;

  };
  
  struct ArenaWinner: public Animatable
  {
    ArenaWinner( IRenderer* renderer, ITimeManager *tm, int num, string winner, string reason, int w, int h, bool wooly ) : Animatable( renderer )
    {
      m_tm = tm;
      winnersName = winner;
      winningReason = reason;
      winnersIndex = num;
      mapWidth = w;
      mapHeight = h;
      woolyTime = wooly;
    }
    
    string winnersName;
    string winningReason;
    int winnersIndex, mapHeight, mapWidth;
    bool woolyTime;
    
    AnimData* getData()
    {
      return &m_arenaWinnerData;
    }
    
    ITimeManager* timeManager() { return m_tm; }

    ArenaWinnerData m_arenaWinnerData;
    ITimeManager *m_tm;

  };

} // visualizer

#endif // VIRUSES_H
