#include "AI.h"
//#include "util.h"

AI::AI(Connection* conn) : BaseAI(conn) {}
bool lowHigh(const Objective& lhs, const Objective& rhs){return lhs.priority < rhs.priority;}
bool highLow(const Objective& lhs, const Objective& rhs){return lhs.priority > rhs.priority;}
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
  database="P0.brawler";
  if(playerID()!=0)
  {
    database="P1.brawler";
  }
  weights.putInInit(database,20,6,6);
  cout<<"Initialization called"<<endl;
  objectCheck();
}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  cout<<"Turn Number: "<<turnNumber()<<endl;
  displayPirates();
  vector<vector<Objective> > grid(mapSize(),vector<Objective>(mapSize()));
  list<Pirate*> actors;
  map<int, bool> myPirate;
  // initialize the map
  for(size_t x=0;x<mapSize();x++)
  {
    for(size_t y=0;y<mapSize();y++)
    {
      grid[x][y].X=x;
      grid[x][y].Y=y;
    }
  }
  // Creates a map for pirates to who owns them
  for(size_t i=0; i<pirates.size();i++)
  {
    myPirate[pirates[i].id()]=pirates[i].owner()==playerID();
  }
  // TODO changes because of treasure stuff
  int x, y;
  // Rate the treasures
  for(size_t i=0;i<treasures.size();i++)
  {
    x= treasures[i].x();
    y= treasures[i].y();
    // No one holding it
    grid[x][y].priority += treasures[i].gold();
    grid[x][y].needs += 1;
  }
  for(size_t i=0; i<pirates.size();i++)
  {
    x = pirates[i].x();
    y = pirates[i].y();
    // if I don't own it
    if(pirates[i].owner() != playerID())
    {
      grid[x][y].priority++;
      grid[x][y].priority+=pirates[i].gold();
      grid[x][y].needs++;
      grid[x][y].pToAttack = &pirates[i];
    }
    else
    {
      actors.push_back(&pirates[i]);
    }
  }
  for(size_t i=0; i<ships.size();i++)
  {
    x=ships[i].x();
    y=ships[i].y();
    if(ships[i].owner() != playerID())
    {
      grid[x][y].priority++;
      grid[x][y].needs++;
    }
  }
  vector<Objective> objectives;
  for(size_t x=0;x<mapSize();x++)
  {
    for(size_t y=0;y<mapSize();y++)
    {
      if(grid[x][y].priority > 0)
      {
        objectives.push_back(grid[x][y]);
      }
    }
  }
  // sorts the objectives based on priority
  sort(objectives.begin(),objectives.end(),highLow);
  
  int spawn=0;
  // for each objective
  for(size_t o=0;o<objectives.size();o++)
  {
    vector<MoveHelper<Pirate*> > usable;
    sortNearest(objectives[o].x(),objectives[o].y(),actors,usable,0);
    // for the nearest guys, until you got all you need or you are out of guys
    for(size_t i=0;i<usable.size() && objectives[o].needs > 0;i++)
    {
      // remove that this is needed
      objectives[o].needs--;
      if(usable[i].path.size()>1)
      {
        (*usable[i].it)->move(usable[i].path[0]->x(),usable[i].path[0]->y());
      }
      else
      {
        if(objectives[o].pToAttack != NULL)
        {
          (*usable[i].it)->attack(*objectives[o].pToAttack);
        }
      }
      //objectives[o].workers.push_back(*usable[i].it);
      actors.erase(usable[i].it);      
    }
    /*
    // if you got all you need
    if(objectives[o].needs==0)
    {
      // cause them to go
      execute(objectives[o]);
    }
    else
    {
      // spawn some more guys
      spawn+=objectives[o].needs;
      // put the guys back into actors
      for(size_t i=0;i<objectives[o].workers.size();i++)
      {
        actors.push_back(objectives[o].workers[i]);
      }
    }
    */
  }
  for(size_t i=0;i<ports.size();i++)
  {
    if(ports[i].owner()==playerID())
    {
      for(size_t p=0;p<spawn;p++)
      {
        ports[i].createPirate();
      }
    }
  }
  return true;
}

void AI::execute(Objective& obj)
{
/*
  for(size_t i=0;i<obj.workers.size();i++)
  {
    // if the next space is the target
    if(obj.path[0]->x()==obj.pAttackTarget->x() && obj.path[0]->y()==obj.pAttackTarget->y())
    {
      obj.workers[i]->attack(*obj.pAttackTarget);
    }
  }
*/
}

void AI::displayPirates()
{
  for(size_t i=0;i<pirates.size();i++)
  {
    ///Unique Identifier
    cout<<"\tID\t"<<pirates[i].id();
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    cout<<"\tX\t"<<pirates[i].x();
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    cout<<"\tY\t"<<pirates[i].y();
    ///The owner of the unit
    cout<<"\tOwner\t"<<pirates[i].owner();
    ///health of the unit
    cout<<"\tHealth\t"<<pirates[i].health();
    ///attacking strength of the unit
    cout<<"\tStrength\t"<<pirates[i].strength();
    cout<<endl;
  }
}
void AI::displayPorts()
{
  for(size_t i=0;i<ports.size();i++)
  {
    ///Unique Identifier
    cout<<"\tID\t"<<ports[i].id();
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    cout<<"\tX\t"<<ports[i].x();
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    cout<<"\tY\t"<<ports[i].y();
    ///The ownder of the port
    cout<<"\tOwner\t"<<ports[i].owner();
    cout<<endl;
  }
}

void AI::displayShips()
{
  for(size_t i=0;i<ships.size();i++)
  {
    ///Unique Identifier
    cout<<"\tID\t"<<ships[i].id();
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    cout<<"\tX\t"<<ships[i].x();
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    cout<<"\tY\t"<<ships[i].y();
    ///The owner of the unit
    cout<<"\tOwner\t"<<ships[i].owner();
    ///health of the unit
    cout<<"\tHealth\t"<<ships[i].health();
    ///attacking strength of the unit
    cout<<"\tStrength\t"<<ships[i].strength();
    cout<<endl;
  }
}

void AI::displayTiles()
{
  vector<int> count(2,0);
  for(size_t i=0;i<tiles.size();i++)
  {
    /*
    ///Unique Identifier
    cout<<"\tID\t"<<tiles[i].id();
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    cout<<"\tX\t"<<tiles[i].x();
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    cout<<"\tY\t"<<tiles[i].y();
    ///land = 0, water = 1
    cout<<"\tType\t"<<tiles[i].type();
    cout<<endl;
    */
    if(tiles[i].type()>count.size())
    {
      count.resize(tiles[i].type());
    }
    count[tiles[i].type()]++;
  }
  cout<<"\ttype\tnumber"<<endl;
  for(size_t i=0;i<count.size();i++)
  {
    cout<<"\t"<<i<<")\t"<<count[i]<<endl;
  }
  cout<<endl;
}

void AI::displayTreasure()
{
  for(size_t i=0;i<treasures.size();i++)
  {
    ///Unique Identifier
    cout<<"\tID\t"<<treasures[i].id();
    ///The X position of this object.  X is horizontal, with 0,0 as the top left corner
    cout<<"\tX\t"<<treasures[i].x();
    ///The Y position of this object.  Y is vertical, with 0,0 as the top left corner
    cout<<"\tY\t"<<treasures[i].y();
    //TODO Pirate carring treasure
    cout<<endl;
  }
}
void AI::objectCheck()
{
  cout<<"--Base AI variables--"<<endl;
  cout<<"turnNumber\t"<<turnNumber();
  ///Player Number; either 0 or 1
  cout<<"playerID\t"<<playerID();
  ///What number game this is for the server
  cout<<"gameNumber\t"<<gameNumber()<<endl;
  ///Player 0's time remaining
  cout<<"player0Time\t"<<players[0].time()<<endl;
  ///Player 1's time remaining
  cout<<"player1Time\t"<<players[1].time()<<endl;
  ///Player 0's name
  cout<<"player0Name\t"<<players[0].playerName()<<endl;
  ///Player 1's name
  cout<<"player1Name\t"<<players[1].playerName()<<endl;
  ///The cost of a pirate
  cout<<"pirateCost\t"<<pirateCost()<<endl;
  ///The cost of a ship
  cout<<"shipCost\t"<<shipCost()<<endl;
  cout<<"portCost\t"<<portCost()<<endl;
  cout<<"boardX\t"<<mapSize()<<endl;
  cout<<"--Object counts--"<<endl;
  cout<<"Pirates : "<<pirates.size()<<endl;
//  displayPirates();
  cout<<"Ports   : "<<ports.size()<<endl;
  displayPorts();
  cout<<"Ships   : "<<ships.size()<<endl;
  displayShips();
  cout<<"Tiles   : "<<tiles.size()<<endl;
  displayTiles();
  cout<<"Treasure: "<<treasures.size()<<endl;
//  displayTreasure();
}

//This function is run once, after your last turn.
void AI::end()
{
  // right now, player 0 always wins!
  weights.putInEnd(playerID()==0);
  cout<<"End Called"<<endl;
  objectCheck();
}
