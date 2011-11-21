#ifndef OPTIONSMAN_H
#define OPTIONSMAN_H

#include <fstream>
using namespace std;

namespace visualizer
{

  class OptionsMan
  {
    public:
      OptionsMan( const std::string& fileName );
      void addComment( const std::string& comment );
      void addOption( const std::string& option );

      int& operator [] ( const std::string& str );

    private:

    
  };

}

#endif // OPTIONSMAN_H
