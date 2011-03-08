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


std::ostream& operator<<(std::ostream& stream, Unit ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  stream << "owner: " << ob.owner  <<'\n';
  stream << "health: " << ob.health  <<'\n';
  stream << "strength: " << ob.strength  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Pirate ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  stream << "owner: " << ob.owner  <<'\n';
  stream << "health: " << ob.health  <<'\n';
  stream << "strength: " << ob.strength  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Port ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  stream << "owner: " << ob.owner  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Ship ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  stream << "owner: " << ob.owner  <<'\n';
  stream << "health: " << ob.health  <<'\n';
  stream << "strength: " << ob.strength  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Tile ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  stream << "type: " << ob.type  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Treasure ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "x: " << ob.x  <<'\n';
  stream << "y: " << ob.y  <<'\n';
  stream << "pirate: " << ob.pirate  <<'\n';
  return stream;
}



std::ostream& operator<<(std::ostream& stream, GameState ob)
{
  stream << "turnNumber: " << ob.turnNumber  <<'\n';
  stream << "playerID: " << ob.playerID  <<'\n';
  stream << "gameNumber: " << ob.gameNumber  <<'\n';
  stream << "player0Time: " << ob.player0Time  <<'\n';
  stream << "player1Time: " << ob.player1Time  <<'\n';

  stream << "\n\nMappables:\n";
  for(std::map<int,Mappable>::iterator i = ob.mappables.begin(); i != ob.mappables.end(); i++)
    stream << i->second << '\n';
  stream << "\n\nUnits:\n";
  for(std::map<int,Unit>::iterator i = ob.units.begin(); i != ob.units.end(); i++)
    stream << i->second << '\n';
  stream << "\n\nPirates:\n";
  for(std::map<int,Pirate>::iterator i = ob.pirates.begin(); i != ob.pirates.end(); i++)
    stream << i->second << '\n';
  stream << "\n\nPorts:\n";
  for(std::map<int,Port>::iterator i = ob.ports.begin(); i != ob.ports.end(); i++)
    stream << i->second << '\n';
  stream << "\n\nShips:\n";
  for(std::map<int,Ship>::iterator i = ob.ships.begin(); i != ob.ships.end(); i++)
    stream << i->second << '\n';
  stream << "\n\nTiles:\n";
  for(std::map<int,Tile>::iterator i = ob.tiles.begin(); i != ob.tiles.end(); i++)
    stream << i->second << '\n';
  stream << "\n\nTreasures:\n";
  for(std::map<int,Treasure>::iterator i = ob.treasures.begin(); i != ob.treasures.end(); i++)
    stream << i->second << '\n';
  stream << "\nAnimation\n";
  for(std::vector<Animation*>::iterator i = ob.animations.begin(); i != ob.animations.end(); i++)
  {
  }
}

Game::Game()
{
  winner = -1;
}
