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
  land.resize(mapSize(), vector<bool>(mapSize(), false));

  for(size_t i=0;i<tiles.size();i++)
  {
    land[tiles[i].x()][tiles[i].y()] = (tiles[i].type()==0);
  }
}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  cout<<"Turn Number: "<<turnNumber()<<" My Gold: "<<players[playerID()].gold()<<endl;
  int turningPoint = 100;
  if(turnNumber() > turningPoint+50) return true;
 
  list<Port*> myPorts;
  gold = vector<vector<size_t> >(mapSize(), vector<size_t>(mapSize(),0));
  
  for(size_t i=0;i<ports.size();i++)
  {
    if(ports[i].owner()==playerID())
    {
      myPorts.push_back(&ports[i]);
    }
    land[tiles[i].x()][tiles[i].y()] = false;
  }
  for(size_t i=0;i<pirates.size();i++)
  {
    if(pirates[i].owner()!=playerID())
    {
      land[pirates[i].x()][pirates[i].y()] = false;
    }
  }
  int amount = players[playerID()].gold()/myPorts.size();
  for(list<Port*>::iterator it = myPorts.begin();it!=myPorts.end();it++)
  {
    vector<Pirate*> pickup;
    for(size_t i=0;i<pirates.size();i++)
    {
      if(samePos(pirates[i], **it))
      {
        pickup.push_back(&pirates[i]);
      }
    }
    if(pickup.size()==0)
    {
      /*
      while(pirateCost() < amount)
      {
        (*it)->createPirate();
        amount -= pirateCost();
      }
      */
    }
    else if(turnNumber()< turningPoint)
    {
      amount/=pickup.size();
      for(size_t i=0;i<pickup.size() && amount>0;i++)
      {
        pickup[i]->pickupTreasure(amount);
      }
    }
  }
  // save the amount of gold
  for(size_t i=0;i<treasures.size();i++)
  {
    gold[treasures[i].x()][treasures[i].y()]+=treasures[i].gold();
  }
  list<Tile*> empty, harvest;
  for(size_t i=0;i<tiles.size();i++)
  {
    if(land[tiles[i].x()][tiles[i].y()] && gold[tiles[i].x()][tiles[i].y()]==0)
    {
      empty.push_back(&tiles[i]);
    }
    else if(land[tiles[i].x()][tiles[i].y()])
    {
      harvest.push_back(&tiles[i]);
    }
  }
  for(size_t i=0;i<pirates.size();i++)
  {
    //
    if(pirates[i].owner()==playerID())
    {
      if(players[playerID()].gold()> portCost())
      {
      //  pirates[i].buildPort();
      }
      bool spread = turnNumber()< turningPoint;
      if(!spread)
      {
        vector<MoveHelper<Tile*> > sorted;  
        sortNearest(pirates[i].x(), pirates[i].y(), harvest, sorted, 0);
        if(sorted.size()>0)
        {
          cout<<"Harvesting"<<endl;
          pirates[i].move(sorted[0].path[0]->x(),sorted[0].path[0]->y());
          harvest.erase(sorted[0].it);
        }
        else
        {
          // move to the nearest port
          vector<MoveHelper<Port*> > sorted;
          sortNearest(pirates[i].x(), pirates[i].y(), myPorts, sorted, 0);
          if(sorted.size()>0)
          {
            pirates[i].move(sorted[0].path[0]->x(),sorted[0].path[0]->y());
          }
        }
      }
      if(spread)
      {
        vector<MoveHelper<Tile*> > sorted;  
        sortNearest(pirates[i].x(), pirates[i].y(), empty, sorted, 0);
        // move there
        if(sorted.size()>0)
        {
          pirates[i].move(sorted[0].path[0]->x(),sorted[0].path[0]->y());
          empty.erase(sorted[0].it);
        }
      }
      
      if(at(pirates[i],myPorts))
      {
        if(pirates[i].gold()>0)
        {
          pirates[i].dropTreasure(pirates[i].gold());
        }
      }
      else if(gold[pirates[i].x()][pirates[i].y()]==0 && pirates[i].gold()>0 && spread)
      {
        pirates[i].dropTreasure(1);
        gold[pirates[i].x()][pirates[i].y()]++;
      }
      else if(gold[pirates[i].x()][pirates[i].y()]>1)
      {
        int modifier = 1;
        if(!spread)
        {
          modifier = 0;
        }
        pirates[i].pickupTreasure(gold[pirates[i].x()][pirates[i].y()]-modifier);
        gold[pirates[i].x()][pirates[i].y()]=modifier;
      }
    }
  }
  
  return true;
}

//This function is run once, after your last turn.
void AI::end(){}
