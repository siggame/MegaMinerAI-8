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

  if ( !sub ) goto ERROR;

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.x = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.y = atoi(sub->val);
  sub = sub->next;

  return true;

  ERROR:
  cerr << "Error in parseMappable.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseBase(Base& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) goto ERROR;

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.x = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.y = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.owner = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.spawnsLeft = atoi(sub->val);
  sub = sub->next;

  return true;

  ERROR:
  cerr << "Error in parseBase.\n Parsing: " << *expression << endl;
  return false;
}
static bool parsePlayer(Player& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) goto ERROR;

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.playerName = new char[strlen(sub->val)+1];
  strncpy(object.playerName, sub->val, strlen(sub->val));
  object.playerName[strlen(sub->val)] = 0;
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.byteDollars = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.cycles = atoi(sub->val);
  sub = sub->next;

  return true;

  ERROR:
  cerr << "Error in parsePlayer.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseTile(Tile& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) goto ERROR;

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.x = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.y = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.owner = atoi(sub->val);
  sub = sub->next;

  return true;

  ERROR:
  cerr << "Error in parseTile.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseVirus(Virus& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  sub = expression->list;

  if ( !sub ) goto ERROR;

  object.id = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.x = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.y = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.owner = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.level = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.movesLeft = atoi(sub->val);
  sub = sub->next;

  if ( !sub ) goto ERROR;

  object.living = atoi(sub->val);
  sub = sub->next;

  return true;

  ERROR:
  cerr << "Error in parseVirus.\n Parsing: " << *expression << endl;
  return false;
}

static bool parseCombat(Combat& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = COMBAT;
  sub = expression->list->next;
  if( !sub ) goto ERROR;
  object.moving = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.stationary = atoi(sub->val);
  sub = sub->next;
  return true;


  ERROR:
  cerr << "Error in parseCombat.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseCombine(Combine& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = COMBINE;
  sub = expression->list->next;
  if( !sub ) goto ERROR;
  object.moving = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.stationary = atoi(sub->val);
  sub = sub->next;
  return true;


  ERROR:
  cerr << "Error in parseCombine.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseCrash(Crash& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = CRASH;
  sub = expression->list->next;
  if( !sub ) goto ERROR;
  object.crashing = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.dx = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.dy = atoi(sub->val);
  sub = sub->next;
  return true;


  ERROR:
  cerr << "Error in parseCrash.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseCreate(Create& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = CREATE;
  sub = expression->list->next;
  if( !sub ) goto ERROR;
  object.creating = atoi(sub->val);
  sub = sub->next;
  return true;


  ERROR:
  cerr << "Error in parseCreate.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseMove(Move& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = MOVE;
  sub = expression->list->next;
  if( !sub ) goto ERROR;
  object.moving = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.dx = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.dy = atoi(sub->val);
  sub = sub->next;
  return true;


  ERROR:
  cerr << "Error in parseMove.\n Parsing: " << *expression << endl;
  return false;
}
static bool parsePlayerTalk(PlayerTalk& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = PLAYERTALK;
  sub = expression->list->next;
  if( !sub ) goto ERROR;
  object.speaker = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.message = new char[strlen(sub->val)+1];
  strncpy(object.message, sub->val, strlen(sub->val));
  object.message[strlen(sub->val)] = 0;
  sub = sub->next;
  return true;


  ERROR:
  cerr << "Error in parsePlayerTalk.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseRecycle(Recycle& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = RECYCLE;
  sub = expression->list->next;
  if( !sub ) goto ERROR;
  object.recycling = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.base = atoi(sub->val);
  sub = sub->next;
  return true;


  ERROR:
  cerr << "Error in parseRecycle.\n Parsing: " << *expression << endl;
  return false;
}
static bool parseVirusTalk(VirusTalk& object, sexp_t* expression)
{
  sexp_t* sub;
  if ( !expression ) return false;
  object.type = VIRUSTALK;
  sub = expression->list->next;
  if( !sub ) goto ERROR;
  object.speaker = atoi(sub->val);
  sub = sub->next;
  if( !sub ) goto ERROR;
  object.message = new char[strlen(sub->val)+1];
  strncpy(object.message, sub->val, strlen(sub->val));
  object.message[strlen(sub->val)] = 0;
  sub = sub->next;
  return true;


  ERROR:
  cerr << "Error in parseVirusTalk.\n Parsing: " << *expression << endl;
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
    std::map< int, std::vector<Animation*> > animations;
    while(expression->next)
    {
      expression = expression->next;
      sub = expression->list;
      if ( !sub ) return false;
      if(string(ToLower( sub->val ) ) == "combat")
      {
        Combat* animation = new Combat;
        if ( !parseCombat(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)animation)->owner ].push_back( animation );
      }
      if(string(ToLower( sub->val ) ) == "combine")
      {
        Combine* animation = new Combine;
        if ( !parseCombine(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)animation)->owner ].push_back( animation );
      }
      if(string(ToLower( sub->val ) ) == "crash")
      {
        Crash* animation = new Crash;
        if ( !parseCrash(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)animation)->owner ].push_back( animation );
      }
      if(string(ToLower( sub->val ) ) == "create")
      {
        Create* animation = new Create;
        if ( !parseCreate(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)animation)->owner ].push_back( animation );
      }
      if(string(ToLower( sub->val ) ) == "move")
      {
        Move* animation = new Move;
        if ( !parseMove(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)animation)->owner ].push_back( animation );
      }
      if(string(ToLower( sub->val ) ) == "player-talk")
      {
        PlayerTalk* animation = new PlayerTalk;
        if ( !parsePlayerTalk(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)animation)->owner ].push_back( animation );
      }
      if(string(ToLower( sub->val ) ) == "recycle")
      {
        Recycle* animation = new Recycle;
        if ( !parseRecycle(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)animation)->owner ].push_back( animation );
      }
      if(string(ToLower( sub->val ) ) == "virus-talk")
      {
        VirusTalk* animation = new VirusTalk;
        if ( !parseVirusTalk(*animation, expression) )
          return false;

        animations[ ((AnimOwner*)animation)->owner ].push_back( animation );
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
  FILE* in = tmpfile();

  if(!in)
    return false;

  fputs( string, in );
  fseek( in, 0, SEEK_SET );

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
