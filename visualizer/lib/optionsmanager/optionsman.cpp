#include <string>
#include "optionsman.h"
#include "scanner.h"

namespace visualizer
{
  OptionsMan::OptionsMan( const std::string& fileName )
  {
    std::ifstream inFile( fileName.c_str() );

    OptionsScanner* scanner = new OptionsScanner( &inFile );
    OptionsParser* parser = new OptionsParser( *this );

    parser->parse( );

    delete parser;
    delete scanner;

  }

}
