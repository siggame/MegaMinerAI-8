#include "parser.h"
#include "sexp/sexp.h"
#include "sexp/parser.h"
#include "sexp/sfcompat.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>

using namespace std;

char *ToLower( char *str )
{
  for( int i = 0; i < strlen( str ); i++ )
  {
    str[ i ] = tolower( str[ i ] );
  }
  return str;
}


static bool parseMappable(Mappable& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) 
  {
    cerr << "Error in parseMappable.\n Parsing: " << *expression << endl;
    return false;
  }

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseMappable.\n Parsing: " << *expression << endl;
    return false;
  }

  object.x = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseMappable.\n Parsing: " << *expression << endl;
    return false;
  }

  object.y = atoi(sub->val);
  sub = sub->next;

  return true;

}
static bool parseBase(Base& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) 
  {
    cerr << "Error in parseBase.\n Parsing: " << *expression << endl;
    return false;
  }

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseBase.\n Parsing: " << *expression << endl;
    return false;
  }

  object.x = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseBase.\n Parsing: " << *expression << endl;
    return false;
  }

  object.y = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseBase.\n Parsing: " << *expression << endl;
    return false;
  }

  object.owner = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseBase.\n Parsing: " << *expression << endl;
    return false;
  }

  object.spawnsLeft = atoi(sub->val);
  sub = sub->next;

  return true;

}
static bool parsePlayer(Player& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) 
  {
    cerr << "Error in parsePlayer.\n Parsing: " << *expression << endl;
    return false;
  }

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlayer.\n Parsing: " << *expression << endl;
    return false;
  }

  object.playerName = new char[strlen(sub->val)+1];
  strncpy(object.playerName, sub->val, strlen(sub->val));
  object.playerName[strlen(sub->val)] = 0;
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlayer.\n Parsing: " << *expression << endl;
    return false;
  }

  object.byteDollars = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlayer.\n Parsing: " << *expression << endl;
    return false;
  }

  object.cycles = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parsePlayer.\n Parsing: " << *expression << endl;
    return false;
  }

  object.time = atoi(sub->val);
  sub = sub->next;

  return true;

}
static bool parseTile(Tile& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) 
  {
    cerr << "Error in parseTile.\n Parsing: " << *expression << endl;
    return false;
  }

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseTile.\n Parsing: " << *expression << endl;
    return false;
  }

  object.x = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseTile.\n Parsing: " << *expression << endl;
    return false;
  }

  object.y = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseTile.\n Parsing: " << *expression << endl;
    return false;
  }

  object.owner = atoi(sub->val);
  sub = sub->next;

  return true;

}
static bool parseVirus(Virus& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) 
  {
    cerr << "Error in parseVirus.\n Parsing: " << *expression << endl;
    return false;
  }

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseVirus.\n Parsing: " << *expression << endl;
    return false;
  }

  object.x = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseVirus.\n Parsing: " << *expression << endl;
    return false;
  }

  object.y = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseVirus.\n Parsing: " << *expression << endl;
    return false;
  }

  object.owner = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseVirus.\n Parsing: " << *expression << endl;
    return false;
  }

  object.level = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseVirus.\n Parsing: " << *expression << endl;
    return false;
  }

  object.movesLeft = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) 
  {
    cerr << "Error in parseVirus.\n Parsing: " << *expression << endl;
    return false;
  }

  object.living = atoi(sub->val);
  sub = sub->next;

  return true;

}

static bool parseCombat(Combat& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = COMBAT;
  sub = expression->list->next;
  if( !sub ) 
  {
    cerr << "Error in parseCombat.\n Parsing: " << *expression << endl;
    return false;
  }
  object.moving = atoi(sub->val);
  sub = sub->next;
  if( !sub ) 
  {
    cerr << "Error in parseCombat.\n Parsing: " << *expression << endl;
    return false;
  }
  object.stationary = atoi(sub->val);
  sub = sub->next;
  return true;

}
static bool parseCombine(Combine& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = COMBINE;
  sub = expression->list->next;
  if( !sub ) 
  {
    cerr << "Error in parseCombine.\n Parsing: " << *expression << endl;
    return false;
  }
  object.moving = atoi(sub->val);
  sub = sub->next;
  if( !sub ) 
  {
    cerr << "Error in parseCombine.\n Parsing: " << *expression << endl;
    return false;
  }
  object.stationary = atoi(sub->val);
  sub = sub->next;
  return true;

}
static bool parseCrash(Crash& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = CRASH;
  sub = expression->list->next;
  if( !sub ) 
  {
    cerr << "Error in parseCrash.\n Parsing: " << *expression << endl;
    return false;
  }
  object.crashing = atoi(sub->val);
  sub = sub->next;
  if( !sub ) 
  {
    cerr << "Error in parseCrash.\n Parsing: " << *expression << endl;
    return false;
  }
  object.dx = atoi(sub->val);
  sub = sub->next;
  if( !sub ) 
  {
    cerr << "Error in parseCrash.\n Parsing: " << *expression << endl;
    return false;
  }
  object.dy = atoi(sub->val);
  sub = sub->next;
  return true;

}
static bool parseCreate(Create& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = CREATE;
  sub = expression->list->next;
  if( !sub ) 
  {
    cerr << "Error in parseCreate.\n Parsing: " << *expression << endl;
    return false;
  }
  object.creating = atoi(sub->val);
  sub = sub->next;
  return true;

}
static bool parseMove(Move& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = MOVE;
  sub = expression->list->next;
  if( !sub ) 
  {
    cerr << "Error in parseMove.\n Parsing: " << *expression << endl;
    return false;
  }
  object.moving = atoi(sub->val);
  sub = sub->next;
  if( !sub ) 
  {
    cerr << "Error in parseMove.\n Parsing: " << *expression << endl;
    return false;
  }
  object.dx = atoi(sub->val);
  sub = sub->next;
  if( !sub ) 
  {
    cerr << "Error in parseMove.\n Parsing: " << *expression << endl;
    return false;
  }
  object.dy = atoi(sub->val);
  sub = sub->next;
  return true;

}
static bool parsePlayerTalk(PlayerTalk& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = PLAYERTALK;
  sub = expression->list->next;
  if( !sub ) 
  {
    cerr << "Error in parsePlayerTalk.\n Parsing: " << *expression << endl;
    return false;
  }
  object.speaker = atoi(sub->val);
  sub = sub->next;
  if( !sub ) 
  {
    cerr << "Error in parsePlayerTalk.\n Parsing: " << *expression << endl;
    return false;
  }
  object.message = new char[strlen(sub->val)+1];
  strncpy(object.message, sub->val, strlen(sub->val));
  object.message[strlen(sub->val)] = 0;
  sub = sub->next;
  return true;

}
static bool parseRecycle(Recycle& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = RECYCLE;
  sub = expression->list->next;
  if( !sub ) 
  {
    cerr << "Error in parseRecycle.\n Parsing: " << *expression << endl;
    return false;
  }
  object.recycling = atoi(sub->val);
  sub = sub->next;
  if( !sub ) 
  {
    cerr << "Error in parseRecycle.\n Parsing: " << *expression << endl;
    return false;
  }
  object.base = atoi(sub->val);
  sub = sub->next;
  return true;

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
          gs.baseCost = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.scaleCost = atof(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.width = atoi(sub->val);
          sub = sub->next;
          if ( !sub ) return false;
          gs.height = atoi(sub->val);
          sub = sub->next;
      }
      else if(string(sub->val) == "Mappable")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Mappable object;
          flag = parseMappable(object, sub);
          gs.mappables[object.id] = object;
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
      else if(string(sub->val) == "Base")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Base object;
          flag = parseBase(object, sub);
          gs.bases[object.id] = object;
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
      else if(string(sub->val) == "Player")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Player object;
          flag = parsePlayer(object, sub);
          gs.players[object.id] = object;
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
      else if(string(sub->val) == "Tile")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Tile object;
          flag = parseTile(object, sub);
          gs.tiles[object.id] = object;
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
      else if(string(sub->val) == "Virus")
      {
        sub = sub->next;
        bool flag = true;
        while(sub && flag)
        {
          Virus object;
          flag = parseVirus(object, sub);
          gs.viruses[object.id] = object;
          sub = sub->next;
        }
        if ( !flag ) return false;
      }
    }
    game.states.push_back(gs);
  }
  else if(string(expression->val) == "animations")
  {
    std::map< int, std::vector< SmartPointer< Animation > > > animations;
    while(expression->next)
    {
      expression = expression->next;
      sub = expression->list;
      if ( !sub ) return false;
      if(string(ToLower( sub->val ) ) == "combat")
      {
        SmartPointer<Combat> animation = new Combat;
        if ( !parseCombat(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)&*animation)->owner ].push_back( animation );
      }
      if(string(ToLower( sub->val ) ) == "combine")
      {
        SmartPointer<Combine> animation = new Combine;
        if ( !parseCombine(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)&*animation)->owner ].push_back( animation );
      }
      if(string(ToLower( sub->val ) ) == "crash")
      {
        SmartPointer<Crash> animation = new Crash;
        if ( !parseCrash(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)&*animation)->owner ].push_back( animation );
      }
      if(string(ToLower( sub->val ) ) == "create")
      {
        SmartPointer<Create> animation = new Create;
        if ( !parseCreate(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)&*animation)->owner ].push_back( animation );
      }
      if(string(ToLower( sub->val ) ) == "move")
      {
        SmartPointer<Move> animation = new Move;
        if ( !parseMove(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)&*animation)->owner ].push_back( animation );
      }
      if(string(ToLower( sub->val ) ) == "player-talk")
      {
        SmartPointer<PlayerTalk> animation = new PlayerTalk;
        if ( !parsePlayerTalk(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)&*animation)->owner ].push_back( animation );
      }
      if(string(ToLower( sub->val ) ) == "recycle")
      {
        SmartPointer<Recycle> animation = new Recycle;
        if ( !parseRecycle(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)&*animation)->owner ].push_back( animation );
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
  //bool value;
  FILE* in = fopen(filename, "r");
  //int size;
  if(!in)
    return false;

  parseFile(in);

  sexp_t* st = NULL;

  while((st = parse()))
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

  parseString( string );

  sexp_t* st = NULL;

  while((st = parse()))
  {
    if( !parseSexp(game, st) )
    {
      while(parse()); //empty the file, keep Lex happy.
      return false;
    }
    destroy_sexp(st);
  }

  return true;
}
