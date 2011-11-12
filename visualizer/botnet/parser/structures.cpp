// -*-c++-*-

#include "structures.h"

#include <iostream>


std::ostream& operator<<(std::ostream& stream, Mappable ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Base ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  stream << "owner: " << ob.owner  <<'\n';
  stream << "spawnsLeft: " << ob.spawnsLeft  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Player ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "playerName: " << ob.playerName  <<'\n';
  stream << "byteDollars: " << ob.byteDollars  <<'\n';
  stream << "cycles: " << ob.cycles  <<'\n';
  stream << "time: " << ob.time  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Tile ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  stream << "owner: " << ob.owner  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Virus ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  stream << "owner: " << ob.owner  <<'\n';
  stream << "level: " << ob.level  <<'\n';
  stream << "movesLeft: " << ob.movesLeft  <<'\n';
  stream << "living: " << ob.living  <<'\n';
  return stream;
}



std::ostream& operator<<(std::ostream& stream, Combat ob)
{
  stream << "Combat" << "\n";
  stream << "moving: " << ob.moving  <<'\n';
  stream << "stationary: " << ob.stationary  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Combine ob)
{
  stream << "Combine" << "\n";
  stream << "moving: " << ob.moving  <<'\n';
  stream << "stationary: " << ob.stationary  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Crash ob)
{
  stream << "Crash" << "\n";
  stream << "crashing: " << ob.crashing  <<'\n';
  stream << "dx: " << ob.dx  <<'\n';
  stream << "dy: " << ob.dy  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Create ob)
{
  stream << "Create" << "\n";
  stream << "creating: " << ob.creating  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Move ob)
{
  stream << "Move" << "\n";
  stream << "moving: " << ob.moving  <<'\n';
  stream << "dx: " << ob.dx  <<'\n';
  stream << "dy: " << ob.dy  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, PlayerTalk ob)
{
  stream << "PlayerTalk" << "\n";
  stream << "speaker: " << ob.speaker  <<'\n';
  stream << "message: " << ob.message  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Recycle ob)
{
  stream << "Recycle" << "\n";
  stream << "recycling: " << ob.recycling  <<'\n';
  stream << "base: " << ob.base  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, GameState ob)
{
  stream << "turnNumber: " << ob.turnNumber  <<'\n';
  stream << "playerID: " << ob.playerID  <<'\n';
  stream << "gameNumber: " << ob.gameNumber  <<'\n';
  stream << "baseCost: " << ob.baseCost  <<'\n';
  stream << "scaleCost: " << ob.scaleCost  <<'\n';
  stream << "width: " << ob.width  <<'\n';
  stream << "height: " << ob.height  <<'\n';

  stream << "\n\nMappables:\n";
  for(std::map<int,Mappable>::iterator i = ob.mappables.begin(); i != ob.mappables.end(); i++)
    stream << i->second << '\n';
  stream << "\n\nBases:\n";
  for(std::map<int,Base>::iterator i = ob.bases.begin(); i != ob.bases.end(); i++)
    stream << i->second << '\n';
  stream << "\n\nPlayers:\n";
  for(std::map<int,Player>::iterator i = ob.players.begin(); i != ob.players.end(); i++)
    stream << i->second << '\n';
  stream << "\n\nTiles:\n";
  for(std::map<int,Tile>::iterator i = ob.tiles.begin(); i != ob.tiles.end(); i++)
    stream << i->second << '\n';
  stream << "\n\nViruss:\n";
  for(std::map<int,Virus>::iterator i = ob.viruses.begin(); i != ob.viruses.end(); i++)
    stream << i->second << '\n';
  stream << "\nAnimation\n";
  for
    (
    std::map< int, std::vector< SmartPointer< Animation > > >::iterator j = ob.animations.begin(); 
    j != ob.animations.end(); 
    j++ 
    )
  {
  for(std::vector< SmartPointer< Animation > >::iterator i = j->second.begin(); i != j->second.end(); i++)
  {
//    if((*(*i)).type == COMBAT)
//      stream << *((Combat*)*i) << "\n";
//    if((*(*i)).type == COMBINE)
//      stream << *((Combine*)*i) << "\n";
//    if((*(*i)).type == CRASH)
//      stream << *((Crash*)*i) << "\n";
//    if((*(*i)).type == CREATE)
//      stream << *((Create*)*i) << "\n";
//    if((*(*i)).type == MOVE)
//      stream << *((Move*)*i) << "\n";
//    if((*(*i)).type == PLAYERTALK)
//      stream << *((PlayerTalk*)*i) << "\n";
//    if((*(*i)).type == RECYCLE)
//      stream << *((Recycle*)*i) << "\n";
  }
  

  }
  return stream;
}

Game::Game()
{
  winner = -1;
}
