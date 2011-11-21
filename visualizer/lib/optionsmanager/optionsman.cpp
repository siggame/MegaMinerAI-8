#include <string>
#include "optionsman.h"
#include "scanner.h"

namespace visualizer
{
  OptionsMan::OptionsMan( const std::string& fileName )
  {
    std::ifstream inFile( fileName.c_str() );

    OptionsScanner* scanner = new OptionsScanner( &inFile );
#if 0
    OptionsParser* parser = new OptionsParser( *scanner, *this );

    parser->parse();

    delete parser;
    delete scanner;
#endif

  }

  Option& OptionsMan::operator [] ( const std::string& key )
  {
    return m_options[ key ];

  }

  void OptionsMan::addComment( const string& comment )
  {

  }

  void OptionsMan::addOption( const string& option )
  {

  }

}
