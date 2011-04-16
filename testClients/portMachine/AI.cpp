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

int xoff [] = {0, 1, 0, -1};
int yoff [] = {1, 0,-1, 0};

//This function is run once, before your first turn.
void AI::init()
{
  land.resize(mapSize(), vector<bool>(mapSize(), false));
  portable.resize(mapSize(), vector<bool>(mapSize(), false));
  for(size_t i=0;i<tiles.size();i++)
  {
    land[tiles[i].x()][tiles[i].y()] = (tiles[i].type()==0);
  }
  for(int x=0;x<mapSize();x++)for(int y=0;y<mapSize();y++)
  {
    if(land[x][y])
    {
      for(int i=0;i<4;i++)
      {
        int dx = x+xoff[i];
        int dy = y+yoff[i];
        if(dx>=0 && dx< mapSize() && dy >=0 && dy < mapSize())
        {
          if(!land[dx][dy])
          {
            portable[x][y]=true;
          }
        }
      }
    }
  }
  /*
  for(int x=0;x<mapSize();x++)
  {
    for(int y=0;y<mapSize();y++)
    {
      if(land[x][y])
      {
        cout<<"X";
      }
      else
      {
        cout<<".";
      }
      cout<<" ";
    }
    cout<<endl;
  }
  */
  cout<<endl;
  for(int x=0;x<mapSize();x++)
  {
    for(int y=0;y<mapSize();y++)
    {
      if(portable[x][y])
      {
        cout<<"O";
      }
      else if(land[x][y])
      {
        cout<<"X";
      }
      else
      {
        cout<<".";
      }
      cout<<" ";
    }
    cout<<endl;
  }
  //*/
}

void AI::turnOffPort(vector<vector<bool> > & poratble, int atX, int atY)
{
  for(int x=-2;x<3;x++)
  {
    for(int y=-2;y<3;y++)
    {
      int dx = atX+x;
      int dy = atY+y;
      if(abs(x)+abs(y) < 3 && dx>=0 && dx< mapSize() && dy >=0 && dy < mapSize())
      {
        portable[dx][dy] = false;
      }
    }
  }
}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  cout<<"Turn Number: "<<turnNumber()<<endl;
  portable = vector<vector<bool> >(mapSize(), vector<bool>(mapSize(), false));
  for(int x=0;x<mapSize();x++)for(int y=0;y<mapSize();y++)
  {
    if(land[x][y])
    {
      for(int i=0;i<4;i++)
      {
        int dx = x+xoff[i];
        int dy = y+yoff[i];
        if(dx>=0 && dx< mapSize() && dy >=0 && dy < mapSize())
        {
          if(!land[dx][dy])
          {
            portable[x][y]=true;
          }
        }
      }
    }
  }
  for(size_t i=0;i<ports.size();i++)
  {
    for(int x=-2;x<3;x++)
    {
      for(int y=-2;y<3;y++)
      {
        int dx = ports[i].x()+x;
        int dy = ports[i].y()+y;
        if(abs(x)+abs(y) < 3 && dx>=0 && dx< mapSize() && dy >=0 && dy < mapSize())
        {
          portable[dx][dy] = false;
        }
      }
    }
  }
  for(size_t i=0;i<pirates.size();i++)
  {
    if(pirates[i].owner() != playerID())
    {
      portable[pirates[i].x()][pirates[i].y()] = false;
    }
  }

  for(size_t i=0;i<pirates.size();i++)
  {
    if(pirates[i].owner()==playerID())
    {
      int x,y;
      vector<Tile*> path;
      do
      {
      //  cout<<"Starting outer loop"<<endl;
        do
        {
    //      cout<<"\tStarting Inner Loop"<<endl;
          x=rand()%mapSize();
          y=rand()%mapSize();
        }while(!portable[x][y]);
        path = getPath(pirates[i].x(),pirates[i].y(),x,y,0);
      }while(path.size()==0);
      pirates[i].move(path[0]->x(),path[0]->y());
      if(portable[pirates[i].x()][pirates[i].y()] && portCost() <= players[playerID()].gold())
      {
        cout<<"BUILD PORT!"<<endl;
        pirates[i].buildPort();
        turnOffPort(portable, pirates[i].x(),pirates[i].y());
      }
    }
  }
/*
  cout<<"Turn Number: "<<turnNumber()<<endl;
  int myPort=0;
  while(ports[myPort].owner() != playerID())myPort++;

  for(size_t i=0;i<ships.size();i++)
  {
    if(ships[i].owner()==playerID())
    {
      // if its at port
      if(samePos(ships[i],ports[myPort]))
      {
        // buy pirates
        while(players[playerID()].gold()>pirateCost())
        {
          ports[myPort].createPirate();
        }
      }
    }
  }
  int other = 0;
  if(playerID()==0)
  {
    other = 1;
  }
  list<Ship*> opponents, mine, empty;
  list<Pirate*> enemyP, npcP, myP;
  for(size_t i=0;i<ships.size();i++)
  {
    if(ships[i].owner()==other)
    {
      opponents.push_back(&ships[i]);
    }
    else if(ships[i].owner() == playerID())
    {
      mine.push_back(&ships[i]);
    }
    else if(ships[i].owner() == -1)
    {
      empty.push_back(&ships[i]);
    }
  }
  for(size_t i=0;i<pirates.size();i++)
  {
    if(pirates[i].owner()==other)
    {
      enemyP.push_back(&pirates[i]);
    }
    else if(pirates[i].owner()!=playerID())
    {
      npcP.push_back(&pirates[i]);
    }
    else
    {
      myP.push_back(&pirates[i]);
    }
  }
  for(list<Ship*>::iterator it= mine.begin();it!= mine.end();it++)
  {
    int count=0;
    for(size_t i=0;i<pirates.size();i++)
    {
      if(samePos(pirates[i], **it))
      {
        count++;
      }
    }
    if(count< 5)
    {
      cout<<"To few pirates, rearm me"<<endl;
      vector<Tile*> path = getPath((*it)->x(), (*it)->y(), ports[myPort].x(), ports[myPort].y(),1);
      for(size_t i=0;i<path.size() && (*it)->movesLeft();i++)
      {
        (*it)->move(path[i]->x(),path[i]->y());
      }
      continue;
    }
    // consider pathing to port if too low on pirates
    vector<MoveHelper<Ship*> > sorted;  
    sortNearest((*it)->x(), (*it)->y(), opponents, sorted, 1);
    if(sorted.size()>0)
    {
      cout<<"Trying to move to nearest opponent"<<endl;
      // move the ship as close as possible
      for(size_t i=0;i<sorted[0].path.size()-1 && (*it)->movesLeft()>0;i++)
      {
        (*it)->move(sorted[0].path[i]->x(),sorted[0].path[i]->y());
      }
    }
  }
  
  for(list<Pirate*>::iterator it= myP.begin();it!= myP.end();it++)
  {
    // if there are abandonded ships
    if(empty.size()>0)
    {
      vector<MoveHelper<Ship*> > sorted;  
      sortNearest((*it)->x(), (*it)->y(), empty, sorted, 0);
      
      // boards empty ships
      if(sorted.size()>0)
      {
        cout<<"Boarding an empty ship"<<endl;
        // move onto it
        (*it)->move(sorted[0].path[0]->x(),sorted[0].path[0]->y());
        empty.erase(sorted[0].it);
      }
    }
    vector<MoveHelper<Pirate*> > sorted;  
    sortNearest( (*it)->x(), (*it)->y(), enemyP, sorted, 0);
    if(sorted.size()>0)
    {
    /*
      // move the ship as close as possible
      for(size_t i=0;i<sorted[0].path.size()-1 && (*it)->movesLeft()>0;i++)
      {
        (*it)->move(sorted[0].path[i]->x(),sorted[0].path[i]->y());
      }
    * /
      if(inRange(**it, **sorted[0].it))
      {
        (*it)->attack(**sorted[0].it);
      }
    }
  }
  */
  return true;
}

//This function is run once, after your last turn.
void AI::end(){}
