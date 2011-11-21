#include "optionsman.h"

using namespace visualizer;

int main( int argc, char* argv[] )
{

  OptionsMan* options;
  options = new OptionsMan( argv[ 1 ] );

  delete options;

}

