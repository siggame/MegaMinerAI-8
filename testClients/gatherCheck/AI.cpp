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
  int myPort=0;
  while(ports[myPort].owner()!=playerID())myPort++;
  //displayPirates();
  cout<<"GOLD: "<<players[playerID()].gold()<<endl;
  //displayShips();
  // ships I want to steal from
  list<Crew> toAttack;
  // ships I want to take
  list<Crew> abandoned;
  // ships I have with treasure
  list<Crew> goToPort;
  // ships I have without treasure
  list<Crew> toCommand;
  /*
  for(size_t p=0;p<pirates.size();p++)
  {
    // if I have a pirate here
    if(pirates[p].owner()==playerID())
    {
      //cout<<"Moves Left Pirate; "<<pirates[p].movesLeft()<<endl;
      int nearest=INT_MAX,nearestIndex=0;
      for(size_t i=0;i<ships.size();i++)
      {
        int dist = abs(pirates[p].x()-ships[i].x())+abs(pirates[p].y()-ships[i].y());
        if(dist < nearest)
        {
          nearest = dist;
          nearestIndex=i;
        }
      }
      // tries to board ships if they are near by
      if(nearest == 1)
      {
        cout<<"Boarding a ship!"<<endl;
        vector<Tile*> path = getPath(pirates[p].x(),pirates[p].y(),ships[nearestIndex].x(),ships[nearestIndex].y(),0);
        pirates[p].move(path[0]->x(),path[0]->y());
      }
    }
  }
  */
  // builds up the lists
  for(size_t i=0;i<ships.size();i++)
  {
    Crew working;
    working.ship = &ships[i];
    working.gold = ships[i].gold();
    for(size_t p=0;p<pirates.size();p++)
    {
      if(samePos(ships[i],pirates[p]))
      {
        working.mates.push_back(&pirates[p]);
        working.gold+=pirates[p].gold();
        // TODO check error for droping when you have none
        if(pirates[p].gold()>0 && pirates[p].owner()==playerID())pirates[p].dropTreasure(pirates[p].gold());
      }
    }
    // if I own it
    if(ships[i].owner()==playerID())
    {
      // if I have gold
      if(working.gold>players[playerID()].gold() || (working.mates.size() < 4) && working.gold>pirateCost())
      {
        goToPort.push_back(working);
      }
      else
      {
        toCommand.push_back(working);
      }
    }
    else
    {
      if(working.mates.size()==0)
      {
        abandoned.push_back(working);
      }
      else if(working.gold>0)
      {
        toAttack.push_back(working);
      }
    }
  }
  // for each ship I control that has treasure
  for(list<Crew>::iterator it=goToPort.begin();it!=goToPort.end();it++)
  {
    cout<<"Holy shit, I have treasure!"<<endl;
    vector<Tile*> path = getPath((*it)->x(),(*it)->y(),ports[myPort].x(),ports[myPort].y(),1);
    cout<<"I can move: "<<(*it)->movesLeft()<<endl;
    // the path is always going to include 1 step the ship can't go
    for(int i=0;i<2 && i< path.size();i++)
    {
      cout<<"Moving home!"<<endl;
      (*it)->move(path[i]->x(),path[i]->y());
    }
    if(samePos(*(*it).ship,ports[myPort]))
    {
      cout<<"Home!"<<endl;
    }
    /*
    // if I reached the port
    if(path.size()<3)
    {
      cout<<"Pirates can make it!"<<endl;
      // for each mate
      for(size_t i=0;i<(*it).mates.size();i++)
      {
        int amount=0;
        for(size_t t=0;t<(*it).booty.size();t++)
        {
          //cout<<"Treasure: "<<*(*it).booty[t]<<endl;
          //cout<<"Pirate: "<<*(*it).mates[i]<<endl;
          if((*it).booty[t]->pirateID()==(*it).mates[i]->id())
          {
            amount+=(*it).booty[t]->amount();
          }
        }
        if(amount>0)
        {
          cout<<"Found a pirate with gold"<<endl;
          /*
          if(path.size()>2)
          {
            cout<<"Moving the last step"<<endl;
            // move the last step
            (*it).mates[i]->move(path[path.size()-1]->x(),path[path.size()-1]->y());
          }
          else * /if(samePos(*(*it).mates[i],ports[myPort]))
          {
            cout<<"Droping: "<<amount<<endl;
            // Hope you can drop any amount
            (*it).mates[i]->dropTreasure(amount);
            futureGold+=amount;
          }
        }
      }
    }
    */
  }
//*
  while(players[playerID()].gold()>pirateCost())
  {
    ports[myPort].createPirate();
  }
// */
  // for each ship that is abandoned
  for(list<Crew>::iterator it=abandoned.begin();it!=abandoned.end();it++)
  {
    vector<MoveHelper<Crew> > options;
    sortNearest(toCommand,(*it)->x(),(*it)->y(),options,1);
    //int toSend=0;
    // if there is a ship that can move there
    if(options.size()>0)
    {
      // advance the ship
      for(int i=0;i<2 && i< options[0].path.size()-1;i++)
      {
        (*options[0].it)->move(options[0].path[i]->x(),options[0].path[i]->y());
      }
      if(options[0].path.size()<4 && options[0].path.size()>0)
      {
        for(size_t x=0;x+1<options[0].path.size();x++)
        {
          cout<<options[0].path[x]->x()<<","<<options[0].path[x]->y()<<endl;
        }
        
        int end = options[0].path.size()-1;
        //TODO handle round problems
        // for half the men of the ships crew
        for(size_t i=0;i<(*options[0].it).mates.size()/2;i++)
        {
          cout<<"Boarding a ship! "<<(*options[0].it).mates[i]->x()<<" "<<(*options[0].it).mates[i]->y()<<" "
                                        <<options[0].path[end]->x()<<" "<<options[0].path[end]->y()<<endl;
          
          (*options[0].it).mates[i]->move(options[0].path[end]->x(),options[0].path[end]->y());
        }
      }
      toCommand.erase(options[0].it);
    }
  }
  // for each ship that is carrying money
  for(list<Crew>::iterator it=toAttack.begin();it!=toAttack.end();it++)
  {
    vector<MoveHelper<Crew> > options;
    sortNearest(toCommand,(*it)->x(),(*it)->y(),options,1);
    int needed = (*it).mates.size()+1;
    for(size_t o=0;o<options.size() && needed > 0; o++)
    {
     // advance the ship
      for(int i=0;i<2 && i< options[o].path.size()-1;i++)
      {
        cout<<"We are off to raid the NPCS"<<endl;
        (*options[o].it)->move(options[o].path[i]->x(),options[o].path[i]->y());
      }
      if(options[o].path.size()<4 && options[o].path.size()>0)
      {
        cout<<"Its time to attack"<<endl;
        //int target = lowestLiving((*it).mates);
        //for(size_t i=0;i<(*options[o].it).mates.size() && i*2<(*it).mates[target]->health();i++)
        for(size_t i=0;i<(*options[o].it).mates.size();i++)
        {
          //cout<<"Attacking: "<<(*it).mates[target]->id()<<endl;
          (*options[o].it).mates[i]->attack(*(*it).mates[rand()%(*it).mates.size()]);
        }
      }
      toCommand.erase(options[o].it); 
    }
  }
  /*
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
            npcs.erase(options[0].it);
    }
  }
  for(size_t i=0;i<pirates.size();i++)
  {
    
  }
  */
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
