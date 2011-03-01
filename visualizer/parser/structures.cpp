// -*-c++-*-

#include "structures.h"

#include <iostream>


std::ostream& operator<<(std::ostream& stream, Move ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "fromFile: " << ob.fromFile  <<'\n';
  stream << "fromRank: " << ob.fromRank  <<'\n';
  stream << "toFile: " << ob.toFile  <<'\n';
  stream << "toRank: " << ob.toRank  <<'\n';
  stream << "promoteType: " << ob.promoteType  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, Piece ob)
{
  stream << "id: " << ob.id  <<'\n';
  stream << "owner: " << ob.owner  <<'\n';
  stream << "file: " << ob.file  <<'\n';
  stream << "rank: " << ob.rank  <<'\n';
  stream << "hasMoved: " << ob.hasMoved  <<'\n';
  stream << "type: " << ob.type  <<'\n';
  return stream;
}



std::ostream& operator<<(std::ostream& stream, move ob)
{
  stream << "move" << "\n";
  stream << "fromFile: " << ob.fromFile  <<'\n';
  stream << "fromRank: " << ob.fromRank  <<'\n';
  stream << "toFile: " << ob.toFile  <<'\n';
  stream << "toRank: " << ob.toRank  <<'\n';
  stream << "promoteType: " << ob.promoteType  <<'\n';
  return stream;
}


std::ostream& operator<<(std::ostream& stream, GameState ob)
{
  stream << "turnNumber: " << ob.turnNumber  <<'\n';
  stream << "playerID: " << ob.playerID  <<'\n';
  stream << "gameNumber: " << ob.gameNumber  <<'\n';
  stream << "TurnsToStalemate: " << ob.TurnsToStalemate  <<'\n';
  stream << "player0Time: " << ob.player0Time  <<'\n';
  stream << "player1Time: " << ob.player1Time  <<'\n';

  stream << "\n\nMoves:\n";
  for(std::map<int,Move>::iterator i = ob.moves.begin(); i != ob.moves.end(); i++)
    stream << i->second << '\n';
  stream << "\n\nPieces:\n";
  for(std::map<int,Piece>::iterator i = ob.pieces.begin(); i != ob.pieces.end(); i++)
    stream << i->second << '\n';
  stream << "\nAnimation\n";
  for(std::vector<Animation*>::iterator i = ob.animations.begin(); i != ob.animations.end(); i++)
  {
    if((**i).type == MOVE)
      stream << *((move*)*i) << "\n";
  }
}

Game::Game()
{
  winner = -1;
}
