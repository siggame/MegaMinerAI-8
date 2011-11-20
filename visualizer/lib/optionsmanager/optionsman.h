#ifndef OPTIONSMAN_H
#define OPTIONSMAN_H

#include <fstream>
#include "scanner.h"

namespace visualizer
{

  class OptionsMan
  {
    public:
      inline explicit OptionsMan( const char* const fileName );
      

    private:
    
  };

  OptionsMan::OptionsMan( const char* const fileName )
  {
    std::ifstream inFile( fileName );

    OptionsScanner scanner( &inFile );
    OptionsParser parser();

    parser.parse( &this );

  }

}

#endif // OPTIONSMAN_H
