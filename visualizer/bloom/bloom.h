#ifndef BLOOM_H
#define BLOOM_H

#include <QObject>
#include "parser/parser.h"      // We need this to talk to the parser
#include "parser/structures.h"  // This as well for the structures we'll use
#include "igame.h"              // This header file contains a base class
                                // we'll use to make a common interface
                                // between the core visualizer and bloom
#include "animsequence.h"       // This holds AnimSequence which is a 
                                // sort of timeline the visualizer uses.

namespace visualizer            // For name safety (preventing the duplication of names)
{                               // we're going to use this namespace.  Anything outside
                                // of this namespace will not conflict with anything
                                // inside of it.
   
  class Bloom: public QObject, public AnimSequence, public visualizer::IGame
               // We're calling our main class, 'Bloom'.
               // "public AnimSequence" tells us that 'Bloom' will contain our timeline
               // "public visualizer::IGame" is the common basis which helps the core
               // find bloom.
  {
    Q_OBJECT;  // Needed
    Q_INTERFACES( visualizer::IGame ); 
        //  ^^ Tells the compiler that this is the main in the plugin
    public:
      Bloom();   // Constructor
      ~Bloom();  // Deconstructor

      // These three methods are required by IGame for this plugin to exist and link
      // to the core. We'll talk about them more in bloom.cpp
      LogRegex logFileInfo();                     
      void loadGamelog( std::string gamelog );
    private:
      Game *m_game;       // Variable which holds the turns.
  }; // Bloom

} // visualizer

#endif


