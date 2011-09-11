#include "bloom.h"
// Include the animations we just made
#include "animations.h"   

#include "plant.h"
// We're also going to include frame.h because 
// We have to store all of our animatables in an animation frame
#include "frame.h"


namespace visualizer
{
  Bloom::Bloom() // Constructor
  {
    m_game = 0;  // Don't setup the game yet.
  } // Bloom::Bloom()

  Bloom::~Bloom() // Deconstructor
  {
    delete m_game; // Cleanup once we're done
  } // Bloom::~Bloom()

  LogRegex Bloom::logFileInfo() 
      // Function tells the visualizer core what gamelogs we are responsible for
  {
    LogRegex lr; // Structure which holds regex to determine gamelog 
    // ownership
    lr.regex = "Plant"; // We'll just assume this is a bloom gamelog
    lr.startSize = 500; // How many characters to read before giving up.

    return lr;
  } // Bloom::logFileInfo()

  void Bloom::loadGamelog( std::string gamelog )
  {
    // This will be invoked auotmatically by the core visualizer when
    // it determines this plugin IS the one responsible for the the 
    // gamelog it just received. 

    // We'll just use this to prove that it's loading bloom when it
    // should
    cout << "Load Bloom Gamelog" << endl;

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
    } // Bloom::loadGamelog()

    // We need to keep track of all of the frames that are in this game
    size_t frameNum = 0;

    // So the next thing we need to do is translate all the parsed
    // units into our animatables.   

    // We do this by looping through all the states in the game.
    for
      (
      std::vector<GameState>::iterator state = m_game->states.begin();
      state != m_game->states.end();
      state++
      )
    {
      // First thing we need to do is make a new Frame and we'll just 
      // call it turn
      Frame turn;
      // For each game state, we have to loop through all the plants
      // and add them to the stack. 
      for
        (
        std::vector<Plant>::iterator i = state->plants.begin();
        i != state->plants.end();
        i++
        )
      {
        // We'll create a new plant animatable
        plant *p = new plant( renderer );

        // We want to add the StartAnim to the plant  first
        p->addKeyFrame( new StartAnim );

        // We just want to copy all the attributes we need from the parser
        p->ownerID = i->ownerID;
        p->x = i->x;
        p->y = i->y;
        p->root = i->root;
        p->leaf = i->leaf;
        p->flower = i->flower;
        p->health = i->health;

        // Then we want to add the draw animation to the plant
        p->addKeyFrame( new DrawPlant( p ) );

        // Once we're done with the animatable, we have to add it to 
        // the frame.
        turn.addAnimatable( p );

      }

      // At this point all the animatables have been put into the frame, 
      // so we're done with the frame.  We can add the frame to the 
      // master timeline.
      addFrame( turn );
      // Since this frame is added, we'll increment the frame count:
      frameNum++;

    }

    // To let our timeline in the main visualizer know how many frames
    // we've processed, we have to give them the frame count:
    timeManager->setNumTurns( frameNum );

    // Everything's ready to be played at this point, so we want to 
    // let the animation engine we're ready to go
    animationEngine->registerFrameContainer( this );

    // Now let's just go ahead and start playing
    timeManager->play();

  } // Bloom::loadGamelog()

} // visualizer

Q_EXPORT_PLUGIN2( bloom, visualizer::Bloom );
