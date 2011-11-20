#include "optionsman.h"

using namespace OptionsMan;

int main( int argc, char* argv[] )
{

  OptionsMan* options;
  options = new OptionsMan( argv[ 1 ] );

  delete options;

}

