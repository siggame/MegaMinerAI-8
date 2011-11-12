///////////////////////////////////////////////////////////////////////////////
/// @file timemanager.h
/// @brief Contains the class definitions for the time manager.
///////////////////////////////////////////////////////////////////////////////
#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <QTimer>
#include <QTime>
#include <time.h>
#include <list>

#include "../../interfaces/itimemanager.h"

namespace visualizer
{

  ///////////////////////////////////////////////////////////////////////////////
  /// @class _TimeManager
  /// @brief This class is the module in the visualizer for controlling time
  /// and keeping track of what turn we're on.
  ///
  /// In the future we may abstract a '_TurnManager' module from '_TimeManager'
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  /// @fn _TimeManager::nextTurn()
  /// @brief Tells the time manager to pause the visualizer and go to the next 
  /// turn.
  /// @return const int& representing the turn it was changed to.
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  /// @fn _TimeManager::prevTurn()
  /// @brief Tells the time manager to pause the visualizer and go back one turn.
  /// @return const int& representing the turn it was changed to
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  /// @fn _TimeManager::play()
  /// @brief Tells the time manager to start playing at normal speed.
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  /// @fn _TimeManager::pause()
  /// @brief Tells the time menager to pause play 
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  /// @fn _TimeManager::fastForward()
  /// @brief Tells the time manager to start playing and increase the speed by
  /// 25%
  ///////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////////
  /// @fn _TimeManager::rewind()
  /// @brief Tells the time manager to start playing in reverse and increase
  /// the speed by 25%
  ///////////////////////////////////////////////////////////////////////////////

  class _TimeManager : public QObject, public ITimeManager
  {
    Q_OBJECT
    Q_INTERFACES( visualizer::ITimeManager );
    public:
      static void setup();
      static void destroy();
      void _setup();

      void updateProgress( float progress );

      const float& getSpeed();
      /// @TODO This should change the default speed or a new 
      /// function should be made to do it.
      void setSpeed( const float& speed );

      void timerStart();
      void start();

      void requestUpdate( UpdateNeeded* requester );
      void removeRequest( UpdateNeeded* requester );

      // @NOTE These five will probably have their names changed
      void setTurn( const int& turn );
      const int& getTurn();

      void setTurnPercent( const float& perc );
      const float& getTurnPercent();

      const int& nextTurn();
      const int& prevTurn();

      void play();
      void pause();

      void abloop_on(const int& a, const int&b);
      void abloop_off();
	  
      void fastForward();
      void rewind();

      const int& getNumTurns() const;
      void setNumTurns( const int& numTurns );
      void setMaxTurns( const size_t& maxTurns );

      char readyForGamelog();

    private slots:
      void timerUpdate();

    private:
      void updateChildren();

      QTimer *m_timer;
      QTime m_time;
      float m_speed;
      float m_progress;
      bool loop_on;
      int loop_start;
      int loop_end;

      bool m_breakout;
      /// @TODO Rename this variable.  It's not a good name at all

      /// This is the amount of the current turn that has been 
      /// achieved.
      /// If we're halfway through turn 30
      /// m_turn == 30
      /// m_turnCompletion == .5
      float m_turnCompletion;

      int m_turn;
      int m_numTurns;
      size_t m_maxTurns;
      std::list< UpdateNeeded* > m_updateRequesters;
  }; // _TimeManager

  extern _TimeManager *TimeManager;

} // visualizer

#endif
