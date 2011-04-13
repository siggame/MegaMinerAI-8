#include "AI.h"
#include "util.h"

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
  land = vector<vector<bool> >(mapSize(),vector<bool>(mapSize(),false));
  for(size_t i=0;i<tiles.size();i++)
  {
    land[tiles[i].x()][tiles[i].y()] = (tiles[i].type()==0);
  }
}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  cout<<"Turn Number: "<<turnNumber()<<endl;
  int myPort=0;
  while(ports[myPort].owner() != playerID())myPort++;
  list<Pirate*> atPort;
  
  for(size_t i=0;i<pirates.size();i++)
  {
    if(samePos(ports[myPort],pirates[i]))
    {
      atPort.push_back(&pirates[i]);
    }
  }
  if(atPort.size() >0 && turnNumber() < 400 && players[playerID()].gold()>0)
  {
    // divide it among the guys at port
    int amount = players[playerID()].gold() / atPort.size();
    for(list<Pirate*>::iterator it = atPort.begin();it!=atPort.end();it++)
    {
      (*it)->pickupTreasure(amount);
    }
  }
  // for each pirate at port
  vector<vector<size_t> > gold(mapSize(),vector<size_t>(mapSize(),0));
  
  map<int, size_t> hasTreasure;
  for(size_t t=0;t<treasures.size();t++)
  {
    if(treasures[t].pirateID()==0)
    {
      gold[treasures[t].x()][treasures[t].y()]+= treasures[t].amount();
    }
    else
    {
      hasTreasure[treasures[t].pirateID()] = treasures[t].amount();
    }
  }
  list<target> empty, growing;
  for(size_t x=0;x<mapSize();x++)
  {
    for(size_t y=0;y<mapSize();y++)
    {
      if(land[x][x])
      {
        if(gold[x][y]>0)
        {
          growing.push_back(target(x,y,gold[x][y]));  
        }
        else
        {
          empty.push_back(target(x,y,0));
        }
      }
    }
  }
  for(size_t i=0;i<pirates.size();i++)
  {
    if(pirates[i].owner() == playerID())
    {
      // if he has treasure
      if(hasTreasure.find(pirates[i].id())!= hasTreasure.end() && turnNumber()<400)
      {
//        cout<<"Spreading the seed"<<endl;
        sortNearest(pirates[i].x(), pirates[i].y(), empty, 0);
        if(empty.size()>0)
        {
          vector<Tile*> path = getPath(pirates[i].x(), pirates[i].y(), (*empty.begin()).x, (*empty.begin()).y,0);
          cout<<"Heading for: "<<endl;
          for(size_t p=0;p<path.size();p++){cout<<"\t"<<path[p]->x()<<","<<path[p]->y()<<endl;}
          pirates[i].move(path[0]->x(),path[0]->y());
          if(gold[path[0]->x()][path[0]->y()]==0)
          {
            cout<<"Dropping treasure!"<<endl;
            pirates[i].dropTreasure(1);
            gold[path[0]->x()][path[0]->y()]=1;
            empty.erase(empty.begin());  
          }
          
        }
      }
      // needs treasure
      else
      {
      
      }
    }
  }
  return true;
}

//This function is run once, after your last turn.
void AI::end(){}
