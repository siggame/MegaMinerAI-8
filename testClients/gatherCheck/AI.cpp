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
void AI::init(){}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  displayShips();
  list<Ship*> npcs;
  vector<Crew> fleets;
  for(size_t i=0;i<ships.size();i++)
  {
    if(ships[i].owner() >1)
    {
      npcs.push_back(&ships[i]);
    }
    if(ships[i].owner()==playerID())
    {
      Crew working;
      working.ship = &ships[i];
      for(size_t p=0;p<pirates.size();p++)
      {
        if(pirates[i].x()==ships[i].x() && pirates[i].y()== ships[i].y())
        {
          working.mates.push_back(&pirates[i]);
        }
      }
    }
  }
  for(size_t i=0;i<ships.size();i++)
  {
    if(ships[i].owner() != playerID())
    {
      continue;
    }
    vector<MoveHelper<Ship*> > options;
    sortNearest(ships[i].x(),ships[i].y(),npcs,options,1);
    // if there are NPC ships
    if(options.size()>0)
    {
      if(options[0].path.size()>1)
      {
        ships[i].move(options[0].path[0]->x(),options[0].path[0]->y());
        if(options[0].path.size()>2)
        {
          cout<<"Moving twice!"<<endl;
          ships[i].move(options[0].path[1]->x(),options[0].path[1]->y());
        }
      }
      //*
      else
      {
        ships[i].attack(*(*options[0].it));
      }
      //*/
      /*
      else
      {
        
      }
      */
      npcs.erase(options[0].it);
    }
  }
  for(size_t i=0;i<pirates.size();i++)
  {
    
  }
  return true;
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

//This function is run once, after your last turn.
void AI::end(){}
