#include "optionsman.h"
#include "scanner.h"

namespace visualizer
{
  OptionsMan::OptionsMan( const char* const fileName )
  {
    std::ifstream inFile( fileName );

    OptionsScanner* scanner = new OptionsScanner( &inFile );
    OptionsParser* parser = new OptionsParser();

    parser->parse( &this );

    delete parser;
    delete scanner;


  }
}
