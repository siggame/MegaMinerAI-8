#include "bloom.h"

namespace visualizer
{
  Bloom::Bloom() // Constructor
  {
    m_game = 0;  // Don't setup the game yet.
  }

  Bloom::~Bloom() // Deconstructor
  {
    delete m_game; // Cleanup once we're done
  }

  LogRegex Bloom::logFileInfo() 
      // Function tells the visualizer core what gamelogs we can handle
  {
    LogRegex lr; // Structure which holds regex to determine gamelog 
    // ownership
    lr.regex = "Plant"; // We'll just assume this is a bloom gamelog
    lr.startSize = 500; // How many characters to read before giving up.

    return lr;
  }

  void Bloom::loadGamelog( std::string gamelog )
  {
    // We'll just use this to prove that it's loading bloom when it
    // should
    cout << "Load Bloom Gamelog"
    // Let's just make sure that we don't have memory leaks.
    delete m_game; 
    // Allocates the memory we need for the new gamelog
    m_game = new Game;

    // So this is really important.  This loads the gamelog into 
    // memory when we call it.
    if( !parseFile( *m_game, (char*)gamelog.c_str() ) ) // Not safe
    {
      // It didn't load correctly.  Cleanup everything
      delete m_game;
      // This is special macros for throwing exceptions.  
      // It's good to use exceptions whenever you can so we know
      // exactly when and where our code is failing.  It will
      // immediately exit and print the error
      THROW
        (
          GameException, "Cannot Load The Gamelog."
        );
    }
    
    // So, now the gamelog is loaded into memory.  We'll just check to
    // make sure everything is working alright.
    // Does anyone have any questions before I move on?

  }
}
