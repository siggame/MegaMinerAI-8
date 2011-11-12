#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "viruses.h"
#include "irenderer.h"
#include "igame.h"
#include "easing_equations.h"


namespace visualizer
{

  class StartAnim: public Anim
  {
    public:
      StartAnim() {}
      void animate( const float& t, AnimData *d );

      float controlDuration() const
      { return 0; }
      float totalDuration() const
      { return 0; }

  }; // StartAnim

  class Appear: public Anim
  {
    public:
      void animate( const float& t, AnimData *d );

      float controlDuration() const
      {
        return 0;
      }
      float totalDuration() const
      {
        return 1;
      }
  };

  class PushBoard: public Anim
  {
    public:
      PushBoard( moveBoard* mb )
      {
        m_mb = mb;
      }

      void animate( const float& t, AnimData *d );

      float controlDuration() const
      { return 0; }
      float totalDuration() const
      { return 0; }
    private:
      moveBoard *m_mb;

  };

  class StartVirus: public Anim
  {
    public:
      StartVirus( virus* v )
      {
        m_virus = v;
      }

      void animate( const float& t, AnimData *d )
      {
        VirusData* v = (VirusData*)d;
        v->x = m_virus->x;
        v->y = m_virus->y;
      }

      float controlDuration() const
      { return 0; }
      float totalDuration() const
      { return 0; }

    private:
      virus* m_virus;
  };

  inline float dampen( const float& d )
  {
    if( d > 12 )
      return 0;

    return easeOutCubic( d-1, 1, -1, 11 );
  }

  class CrashLeft: public Anim
  {
    public:
      CrashLeft( const float& d )
      {
        m_dampner = dampen(d);
      }

      void animate( const float& t, AnimData *d );

      float controlDuration() const
      { return 1; }
      float totalDuration() const
      { return 1; }

    private:
      float m_dampner;

  }; // CrashLeft

  class CrashRight: public Anim
  {
    public:
      CrashRight( const float& d )
      {
        m_dampner = dampen(d);
      }

      void animate( const float& t, AnimData *d );

      float controlDuration() const
      { return 1; }
      float totalDuration() const
      { return 1; }
    private:
      float m_dampner;

  }; // CrashRight

  class CrashUp: public Anim
  {
    public:
      CrashUp( const float& d )
      {
        m_dampner = dampen(d);
      }
      void animate( const float& t, AnimData *d );

      float controlDuration() const
      { return 1; }
      float totalDuration() const
      { return 1; }

    private:
      float m_dampner;

  }; // CrashUp

  class CrashDown: public Anim
  {
    public:
      CrashDown( const float& d )
      {
        m_dampner = dampen(d);
      }
      void animate( const float& t, AnimData *d );

      float controlDuration() const
      { return 1; }
      float totalDuration() const
      { return 1; }
    private:
      float m_dampner;

  }; // CrashDown

  class LeftAnim: public Anim
  {
    public:
      void animate( const float& t, AnimData *d );

      float controlDuration() const
      { return 1; }
      float totalDuration() const
      { return 1; }

  }; // LeftAnim

  class RightAnim: public Anim
  {
    public:
      void animate( const float& t, AnimData *d );

      float controlDuration() const
      { return 1; }
      float totalDuration() const
      { return 1; }

  }; // RightAnim

  class UpAnim: public Anim
  {
    public:
    void animate( const float& t, AnimData *d );

    float controlDuration() const
    { return 1; }
    float totalDuration() const
    { return 1; }

  }; // UpAnim

  class DownAnim: public Anim
  {
    public:
    void animate( const float& t, AnimData *d );

    float controlDuration() const
    { return 1; }
    float totalDuration() const
    { return 1; }
  }; // DownAnim

  class DrawTalk: public Anim
  {
    public:
      DrawTalk( talker* t )
      {
        m_talker = t;
      }

      void animate( const float& t, AnimData* d );

      float controlDuration() const
      { return 0; }

      float totalDuration() const
      { return 0; }

    private:
      talker* m_talker;

  };

  class DrawVirus: public Anim
  {
    public:
      DrawVirus( virus* v )
      {
        m_virus = v;
      } // DrawVirus()
      
      void animate( const float& t, AnimData* d );

      float controlDuration() const
      { return 0; }

      float totalDuration() const
      { return 0; }
    private:
      virus* m_virus;

  }; // DrawVirus

  class DrawBase: public Anim
  {
    public:
      DrawBase( base* b )
      {
        m_base = b;
      }

      void animate( const float& t, AnimData* d );

      float controlDuration() const
      { return 0; }

      float totalDuration() const
      { return 0; }

    private:
      base* m_base;
  }; // DrawBase

  class DrawScore: public Anim
  {
    public:
      DrawScore( scoreboard* sb )
      {
        m_sb = sb;
      }

      void animate( const float& t, AnimData* d );

      float controlDuration() const
      { return 0; }

      float totalDuration() const
      { return 0; }

    private:
      scoreboard* m_sb;

  }; // DrawScore
  
  class ScoreAnim: public Anim
  {
    public:
      ScoreAnim(int& oldRed, int& oldBlu, int& curRed, int& curBlu)
      {
        oldRedScore = oldRed;
        oldBluScore = oldBlu;
        
        currentRedScore = curRed;
        currentBluScore = curBlu;
      }
      
      void animate( const float& t, AnimData *d );
      
      double oldRedScore, oldBluScore, currentRedScore, currentBluScore;
      
      float controlDuration() const
      { return 1; }
      float totalDuration() const
      { return 1; }

  }; // ScoreAnim
  
  class ArenaWinnerAnim: public Anim
  {
    public:
      ArenaWinnerAnim(ITimeManager *t)
      {
        tm = t;
      }
      
      void animate( const float& t, AnimData *d );
      
      ITimeManager *tm;
      
      float controlDuration() const
      { return 1; }
      float totalDuration() const
      { return 1; }

  }; // ScoreAnim


  class DrawTile: public Anim
  {
    public: 
      DrawTile( tile* t )
      {
        m_tile = t;
      }

      void animate( const float& t, AnimData* d );

      float controlDuration() const
      { return 0; }

      float totalDuration() const
      { return 0; }

    private:
      tile* m_tile;
  }; // DrawTile
  
  class DrawBackground: public Anim
  {
    public: 
      DrawBackground( background* b)
      {
        m_background = b;
      }

      void animate( const float& t, AnimData* d );

      float controlDuration() const
      { return 0; }

      float totalDuration() const
      { return 0; }

    private:
      background* m_background;
  }; // DrawBackground
  
  class DrawGrid: public Anim
  {
    public: 
      DrawGrid( grid* g)
      {
        m_grid = g;
      }

      void animate( const float& t, AnimData* d );

      float controlDuration() const
      { return 0; }

      float totalDuration() const
      { return 0; }

    private:
      grid* m_grid;
  }; // DrawGrid
  
  class DrawArenaWinner: public Anim
  {
    public: 
      DrawArenaWinner( ArenaWinner* aw, const float& winSpeed )
      {
        m_aw = aw;
        firstRun = true;
        m_winSpeed = winSpeed;
      }

      void animate( const float& t, AnimData* d );

      float controlDuration() const
      { return 0; }

      float totalDuration() const
      { return 0; }

    private:
      ArenaWinner* m_aw;
      float m_winSpeed;
      bool firstRun;
  }; // DrawArenaWinner

  class UpCollide : public Anim
  {
    public: 
      void animate(const float& t, AnimData *d);
      
      float controlDuration() const
      {return 1;}
      float totalDuration() const
      {return 1;}
  }; //Collide
  
  
  class DownCollide : public Anim
  {
    public:
      void animate(const float& t, AnimData *d);
      
      float controlDuration() const
      {return 1;}
      float totalDuration() const                                      
      {return 1;}
  };

  class LeftCollide : public Anim
  {
    public:
      void animate(const float& t, AnimData *d);
      
      float ControlDuration() const
      {return 1;}
      float totatlDuration() const
      {return 1;}
  };

  class RightCollide : public Anim
  {
    public:
      void animate(const float& t, AnimData *d);
      
      float controlDuration() const
      {return 1;}
      float totalDuration() const
      {return 1;}
  };
}//visualizer

#endif // ANIMATIONS_H
