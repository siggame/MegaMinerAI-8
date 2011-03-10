#include "parser.h"
#include "sexp/sexp.h"
#include "sexp/parser.h"
#include "sexp/sfcompat.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>

using namespace std;


static bool parseMove(Move& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) goto ERROR;

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.fromFile = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.fromRank = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.toFile = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.toRank = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.promoteType = atoi(sub->val);
  sub = sub->next;

  return true;

  ERROR:
  cerr << "Error in parseMove.\n Parsing: " << *expression << endl;
  return false;
}
static bool parsePiece(Piece& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) goto ERROR;

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.owner = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.file = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.rank = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.hasMoved = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.type = atoi(sub->val);
  sub = sub->next;

  return true;

  ERROR:
  cerr << "Error in parsePiece.\n Parsing: " << *expression << endl;
  return false;
}

static bool parseMove(move& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = MOVE;
  sub = expression->list->next;
  if( !sub ) goto ERROR;
  object.fromFile = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.fromRank = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.toFile = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.toRank = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.promoteType = atoi(sub->val);
  sub = sub->next;
  return true;


  ERROR:
  cerr << "Error in parsemove.\n Parsing: " << *expression << endl;
  return false;
}

static bool parseSexp(Game& game, sexp_t* expression)
{
  sexp_t* sub, *subsub;
  if( !expression ) return false;
  expression = expression->list;
  if( !expression ) return false;
  if(expression->val != NULL && strcmp(expression->val, "status") == 0)
  {
    GameState gs;
    while(expression->next != NULL)
    {
      expression = expression->next;
      sub = expression->list;
      if ( !sub ) return false;
      if(string(sub->val) == "game")
      {
          sub = sub->next;
          if ( !sub ) return false;
          gs.turnNumber = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.playerID = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.gameNumber = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.TurnsToStalemate = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.player0Time = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.player1Time = atoi(sub->val);
          sub = sub->next;
      }
      else if(string(sub->val) == "Move")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Move object;
          flag = parseMove(object, sub);
          gs.moves[object.id] = object;
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
      else if(string(sub->val) == "Piece")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Piece object;
          flag = parsePiece(object, sub);
          gs.pieces[object.id] = object;
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
    }
    game.states.push_back(gs);
  }
  else if(string(expression->val) == "animations")
  {
    std::vector<Animation*> animations;
    while(expression->next)
    {
      expression = expression->next;
      sub = expression->list;
      if ( !sub ) return false;
      if(string(sub->val) == "move")
      {
        move* animation = new move;
        if ( !parseMove(*animation, expression) )
          return false;
        animations.push_back(animation);
      }
    }
    game.states[game.states.size()-1].animations = animations;
  }
  else if(string(expression->val) == "ident")
  {
    expression = expression->next;
    if ( !expression ) return false;
    sub = expression->list;
    while(sub)
    {
      subsub = sub->list;
      if ( !subsub ) return false;
      int number = atoi(subsub->val);
      if(number >= 0)
      {
        subsub = subsub->next;
        if ( !subsub ) return false;
        subsub = subsub->next;
        if ( !subsub ) return false;
        game.players[number] = subsub->val;
      }
      sub = sub->next;
    }
  }
  else if(string(expression->val) == "game-winner")
  {
    expression = expression->next;
    if ( !expression ) return false;
    expression = expression->next;
    if ( !expression ) return false;
    expression = expression->next;
    if ( !expression ) return false;
    game.winner = atoi(expression->val);
		expression = expression->next;
		if( !expression ) return false;
		game.winReason = expression->val;
  }

  return true;
}


bool parseFile(Game& game, const char* filename)
{
  bool value;
  FILE* in = fopen(filename, "r");
  int size;
  if(!in)
    return false;

  parseFile(in);

  sexp_t* st = NULL;

  while(st = parse())
  {
    if( !parseSexp(game, st) )
    {
      while(parse()); //empty the file, keep Lex happy.
      fclose(in);
      return false;
    }
    destroy_sexp(st);
  }

  fclose(in);

  return true;
}


bool parseString(Game& game, const char* string)
{
  sexp_t* st = NULL;

  st = extract_sexpr(string);
  bool flag = true;
  while(st && flag)
  {
    flag = parseSexp(game, st);
    destroy_sexp(st);
    st = parse();
  }

  return flag;
}
