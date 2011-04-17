#include "AI.h"
#include "util.h"


AI::AI(Connection* conn) : BaseAI(conn) {}

const char* AI::username()
{
  return "Shell AI";
}

const char* AI::password()
{
  return "friday";
}

//This function is run once, before your first turn.
void AI::init()
{
  seedMoney=30;
  gatheredEnough=500;
  pirateIdentify.resize(P_SIZE);
  shipIdentify.resize(S_SIZE);
  srand(time(NULL));
}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  cout<<"TurnNumber: "<<turnNumber()<<" gold: "<<players[playerID()].gold()<<" Treasures: "<<treasures.size()<<endl;
  buildLandable();
  buildEmpty();
  buildHarvest();
  buildMyPorts();
  
  for(size_t i=0;i<pirateIdentify.size();i++)
  {
    cout<<i<<")= "<<pirateIdentify[i].size()<<endl;
  }
  
  for(size_t i=0;i<pirates.size();i++)
  {
    bool needsCommand = pirates[i].owner()==playerID();
    for(size_t c=0;needsCommand && c<P_SIZE;c++)
    {
      needsCommand = !command(pirateIdentify[c], pirates[i], pirateJobList[c]);
    }
    if(needsCommand)
    {
      cout<<"Giving state to: "<<pirates[i].id()<<endl;
      giveJob(pirates[i]);
    }
  }
  for(size_t i=0;i<ships.size();i++)
  {
    bool needsCommand = ships[i].owner()==playerID();
    for(size_t c=0;needsCommand && c<S_SIZE;c++)
    {
      needsCommand = !command(shipIdentify[c], ships[i], shipJobList[c]);
    }
    if(needsCommand)
    {
      giveJob(ships[i]);
    }
  }
  return true;
}


void AI::buildLandable()
{
  landable = vector<vector<bool> >(mapSize(),vector<bool>(mapSize(),true));
  for(size_t i=0;i<tiles.size();i++)
  {
    landable[tiles[i].x()][tiles[i].y()] = (tiles[i].type()==0);
  }
  for(size_t i=0;i<pirates.size();i++)
  {
    if(pirates[i].owner() != playerID())
    {
      landable[pirates[i].x()][pirates[i].y()] = false;
    }
  }
  for(size_t i=0;i<ports.size();i++)
  {
    if(ports[i].owner()!= playerID())
    {
      landable[ports[i].x()][ports[i].y()]=false;
    }
  }
}

void AI::buildEmpty()
{
  empty.clear();
  vector<vector<Tile*> > hasNone(mapSize(),vector<Tile*>(mapSize(),static_cast<Tile*>(NULL)));
  for(size_t i=0;i<tiles.size();i++)
  {
    // if it is reachable by land
    if(landable[tiles[i].x()][tiles[i].y()])
    {
      hasNone[tiles[i].x()][tiles[i].y()] = &tiles[i];
    }
  }
  
  for(size_t i=0;i<treasures.size();i++)
  {
    // there is treasure there
    hasNone[treasures[i].x()][treasures[i].y()] = NULL;
  }
  for(size_t x=0;x<mapSize();x++)
  {
    for(size_t y=0;y<mapSize();y++)
    {
      if(hasNone[x][y]!=NULL)
      {
        empty.push_back(hasNone[x][y]);
      }
    }
  }
}

void AI::buildHarvest()
{
  harvest.clear();
  gold = vector<vector<size_t> >(mapSize(),vector<size_t>(mapSize(), 0));
  for(size_t i=0;i<treasures.size();i++)
  {
    if(treasures[i].gold()>1)
    {
      harvest.push_back(&treasures[i]);
      gold[treasures[i].x()][treasures[i].y()]+=treasures[i].gold();
    }
  }
}

void AI::buildMyPorts()
{
  myPorts.clear();
  for(size_t i=0;i<ports.size();i++)
  {
    if(ports[i].owner()==playerID())
    {
      myPorts.push_back(&(ports[i]));
    }
  }
}

void AI::stateSwitch(PirateStates from, PirateStates to, int id)
{
  cout<<"Switching: "<<id<<" from: "<<from<<" to "<<to<<endl;
  pirateIdentify[from].erase(id);
  pirateIdentify[to].insert(id);
}

void AI::stateSwitch(ShipStates from, ShipStates to, int id)
{
  pirateIdentify[from].erase(id);
  pirateIdentify[to].insert(id);
} 

void AI::crewCommand(Pirate& pirate)
{
  stateSwitch(CREW,SEED,pirate.id());
  //TODO USE HERE
  return;
  for(size_t i=0;i<pirates.size();i++)
  {
    if(pirates[i].owner()!= playerID() && pirates[i].health()>0)
    {
      pirate.attack(pirates[i]);
    }
  }
}

void AI::seedCommand(Pirate& pirate)
{
  vector<MoveHelper<Tile*> > sorted;
  sortNearest(pirate.x(), pirate.y(), empty, sorted, 0);
  if(sorted.size()>0 && pirate.gold()>0)
  {
    pirate.move(sorted[0].path[0]->x(),sorted[0].path[0]->y());
    int amount = gold[pirate.x()][pirate.y()];
    if(amount == 0)
    {
      pirate.dropTreasure(1);
      gold[pirate.x()][pirate.y()]=1;
    }
    empty.erase(sorted[0].it);
  }
  else
  {
    // remove yourself from the seed lists, add yourself to the gather lists
    stateSwitch(SEED,GATHER,pirate.id());
  }
}
void AI::gatherCommand(Pirate& pirate)
{
  vector<MoveHelper<Treasure*> > sorted;
  sortNearest(pirate.x(), pirate.y(), harvest, sorted, 0);
  if(sorted.size()>0)
  {
    pirate.move(sorted[0].path[0]->x(),sorted[0].path[0]->y());
//    int amount = gold[pirate.x()][pirate.y()];
//    if(amount > 0)
//    if(amount > 1)
    if((*sorted[0].it)->gold()>0)
    {
      pirate.pickupTreasure((*sorted[0].it)->gold());
      gold[pirate.x()][pirate.y()]=0;
    }
    harvest.erase(sorted[0].it);
/*
    if(pirate.gold()> gatheredEnough)
    {
      stateSwitch(GATHER,GOTOPORT,pirate.id());
    }
*/
  }
  else
  {
    // remove yourself from the seed lists, add yourself to the gather lists
    stateSwitch(GATHER,SEED,pirate.id());
  }
}

void AI::goToPortCommand(Pirate& pirate)
{
  vector<MoveHelper<Port*> > sorted;
  sortNearest(pirate.x(), pirate.y(), myPorts, sorted, 0);
  if(sorted.size()>0)
  {
    pirate.move(sorted[0].path[0]->x(),sorted[0].path[0]->y());
    // if there was exactly 1 step
    if(sorted[0].path.size()==1)
    {
      if(pirate.gold()>0)
      {
        pirate.dropTreasure(pirate.gold());
      }
      cout<<"Made it to port, starting seeding"<<endl;
      stateSwitch(GOTOPORT,STARTSEED,pirate.id());  
    }
  }
  else
  {
    cout<<"Couldn't find a port, starting my seed"<<endl;
    // remove yourself from the seed lists, add yourself to the gather lists
    stateSwitch(GOTOPORT,STARTSEED,pirate.id());
  }
}
void AI::startSeedCommand(Pirate& pirate)
{
  cout<<"Starting Seed "<<pirate.id()<<endl;
  bool onPort=false;;
  for(list<Port*>::iterator it = myPorts.begin(); !onPort && it!= myPorts.end();it++)
  {
    if(samePos(pirate, **it))
    {
      onPort=true;
    }
  }
  int amount = seedMoney;
  if(players[playerID()].gold() < amount)
  {
    amount = players[playerID()].gold();
  }
  if(onPort  && amount > 0)
  {
    cout<<"Picking up money"<<endl;
    pirate.pickupTreasure(amount);
    stateSwitch(STARTSEED,SEED,pirate.id());
  }
  else if(onPort)// no gold on not on a port, just go 
  {
    cout<<"On port, but no money"<<endl;
    stateSwitch(STARTSEED,GATHER,pirate.id());
  }
  else // not on a port
  {
    cout<<"Not on a port at all"<<endl;
    stateSwitch(STARTSEED,GOTOPORT,pirate.id());
  }
}

void AI::huntCommand(Ship& ship)
{
// 
}
void AI::cargoCommand(Ship& ship)
{
}
void AI::taxiCommand(Ship& ship)
{
}


void AI::giveJob(Pirate& pirate)
{
  //int join = rand()%pirateIdentify.size();
  int join = STARTSEED;
  pirateIdentify[join].insert(pirate.id());
  (this->*(pirateJobList[join]))(pirate);
}
void AI::giveJob(Ship& ship)
{
  int join = rand()%shipIdentify.size();
  shipIdentify[join].insert(ship.id());
  (this->*(shipJobList[join]))(ship);
}
//This function is run once, after your last turn.
void AI::end(){}
