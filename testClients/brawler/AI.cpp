#include "AI.h"
//#include "util.h"

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
  int target=0;
  cout<<"Starting turn: "<<turnNumber()<<endl;
//  objectCheck();
  displayShips();
  for(size_t i=0;i<ships.size();i++)
  {
    if(ships[i].owner()==playerID())
    {
      vector<MoveHelper<Ship> > options;
      sortNearest(ships[i].x(),ships[i].y(),ships,options,1);
      size_t nearest=0;
      // find the nearest enemy ship
      while(nearest<options.size() && options[nearest].goal->owner() == playerID()){nearest++;}
      // if you found a ship
      if(nearest < options.size())
      {
        cout<<"Target: "<<options[nearest].goal->id()<<" Path size: "<<options[nearest].path.size()<<endl;
        if(options[nearest].path.size()<3)
        {
          cout<<"FIRE!"<<endl;
          ships[i].attack(*options[nearest].goal);
        }
        else 
        {
          if(options[nearest].path[0]->x() == ships[i].x(), options[nearest].path[0]->y() == ships[i].y())
          {
            cout<<"ITS AT YOUR PO!"<<endl;
          }
          ships[i].move(options[nearest].path[0]->x(),options[nearest].path[0]->y());
        }
      }
      else
      {
        cout<<"NO PATHS!"<<endl;
      }
    }
  }

  return true;
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
