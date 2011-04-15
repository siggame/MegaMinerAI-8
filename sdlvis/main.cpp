#include "parser.h"
#include "structures.h"

#include <vector>
#include <iostream>
#include <limits>

#include "gui.h"

using namespace std;

int main(int argc, char** argv)
{
  Game g;
  if(argc > 1)
    parseFile(g, argv[1]);
  else
    parseFile(g, "test.gamelog");
    
  cout << g.states.size() << endl;
  
  initGUI();
  
  mainLoop(g);
  
  return 0;
}
