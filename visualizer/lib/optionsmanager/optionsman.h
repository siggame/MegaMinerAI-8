#ifndef OPTIONSMAN_H
#define OPTIONSMAN_H

#include <iostream>
#include <fstream>
#include <map>
#include "option.h"
using namespace std;

namespace visualizer
{

  class OptionsMan
  {
    public:
      OptionsMan( const string& fileName );

      void addComment( const string& comment );
      void addOption( const string& option );

      Option& operator [] ( const string& key );

    private:
      map< string, Option > m_options;
      

    
  };

}

#endif // OPTIONSMAN_H
