#include "AI.h"
#include "util.h"

#include <iostream>
using namespace std;
AI::AI(Connection* conn) : BaseAI(conn) {}

const char* AI::username()
{
  return "Shell AI";
}

const char* AI::password()
{
  return "password";
}

//This function is run once, before your first turn.
void AI::init()
{
  srand(time(NULL));
  cout<<"Initialization called"<<endl;
  land = vector<vector<bool> > (mapSize(),vector<bool>(mapSize(),false));
  port = vector<vector<int> > (mapSize(),vector<int>(mapSize(),-1));
  map = vector<vector<bool> > (mapSize(),vector<bool>(mapSize(),false));


  for(size_t i=0;i<tiles.size();i++)
  {
    land[tiles[i].x()][tiles[i].y()]= tiles[i].type()==0;
  }
  for(size_t i=0;i<ports.size();i++)
  {
    port[ports[i].x()][ports[i].y()]=ports[i].owner();
  }
  vector<Tile*> p = getPath(ports[0].x(), ports[0].y(), ports[1].x(), ports[1].y(), 1);
  for(int i = 0; i < p.size(); i++)
  {
    int x = p[i]->x();
    int y = p[i]->y();
    map[x][y] = true;
  }
  for(size_t i=0;i<land.size();i++)
  {
    for(size_t j=0;j<land[i].size();j++)
    {
      if(port[i][j] != -1)
        cout << port[i][j] << " ";
      else if(map[i][j])
        cout << "- ";
      else
        cout<<(land[i][j]?"X":".")<<" ";
    }
    cout<<endl;
  }
}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  cout<<"Starting turn: "<<turnNumber()<<endl;
  
  return true;
}

//This function is run once, after your last turn.
void AI::end()
{
  cout<<"End Called"<<endl;
}
