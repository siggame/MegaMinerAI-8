#include "objectloader.h"
#include "../../piracy/boatdata.h"
#include "../../piracy/boatrender.h"
#include "../../piracy/piratedata.h"
#include "../../piracy/piratemap.h"
#include "../../piracy/piraterender.h"
#include "../../piracy/renderdata.h"
#include "../../piracy/treasuredata.h"
#include "../../piracy/treasurerender.h"
#include "../../piracy/shipdata.h"
#include "../../piracy/portdata.h"

typedef int idtype;

bool ObjectLoader::loadGamelog(const std::string & filename)
{
    //! @todo PUT THE LOADING LOGIC HERE!!
    Game game;

    if( !parseFile( game, filename.c_str() ) )
    {
      throw "Cannot Load Gamelog";
    }


  //! @todo THIS IS BROKEN!!!!
   // GameObject *go = new GameObject( -1 );
   // PirateMap *pm = new PirateMap();
    //pm->generateMap( game );
    //pm->setOwner( go );
   // go->setGOC( pm );

    //Renderer<DupObj>::reg( -1, go );

    unsigned int numTurns = game.states.size();
    unsigned int numFrames = optionsMan::getInt("numFrames");
    TimeManager::setTurn(0);
    TimeManager::setNumTurns( numTurns );


    std::map<idtype, LookupSet<GameObject*,idtype> > looksets;

    for (unsigned int turn = 0; turn < game.states.size(); turn++)
    {

	// pirates
	for (unsigned int unit = 0; unit < game.states[turn].pirates.size();unit++)
	{
	    unsigned int id = game.states[turn].pirates[unit].id;
	    if (looksets.find(id) == looksets.end())
	    {
		looksets.insert( std::pair<idtype,LookupSet<GameObject*,idtype> >(id,LookupSet<GameObject*,idtype>(numTurns,numFrames,id) ));
	    }

	    GameObject * pirate = new GameObject(id);

	    //setup stuff
	    PirateData * data = new PirateData();
	    //PirateRender * render = new PirateRender();

	    data->setOwner(pirate);
	    //render->setOwner(pirate);

	    pirate->setGOC(data);
	    //pirate->setGOC(render);

	    //end setup

	    looksets[id].addNode(pirate,turn,0);
	}

	// ships
	for (unsigned int unit = 0; unit < game.states[turn].ships.size();unit++)
	{
	    unsigned int id = game.states[turn].ships[unit].id;
	    if (looksets.find(id) == looksets.end())
	    {
		looksets.insert( std::pair<idtype,LookupSet<GameObject*,idtype> >(id,LookupSet<GameObject*,idtype>(numTurns,numFrames,id) ));
	    }

	    GameObject * ship = new GameObject(id);
	    //setup stuff

	    ShipData * data = new ShipData();
	    //ShipRender * render = new ShipRender();

	    //render->setOwner(ship);
	    data->setOwner(ship);

	    ship->setGOC(data);
	    //ship->setGOC(render);

	    //end setup

	    looksets[id].addNode(ship,turn,0);
	}

	// treasures
	for (unsigned int unit = 0; unit < game.states[turn].treasures.size();unit++)
	{
	    unsigned int id = game.states[turn].treasures[unit].id;
	    if (looksets.find(id) == looksets.end())
	    {
		looksets.insert( std::pair<idtype,LookupSet<GameObject*,idtype> >(id,LookupSet<GameObject*,idtype>(numTurns,numFrames,id) ));
	    }

	    GameObject * treasure = new GameObject(id);
	    //setup stuff

	    TreasureData * data = new TreasureData();
	    //TreasureRender * render = new TreasureRender();

	    //render->setOwner(treasure);
	    data->setOwner(treasure);

	    treasure->setGOC(data);
	    //treasure->setGOC(render);

	    //end setup

	    looksets[id].addNode(treasure,turn,0);
	}

	// ports
	for (unsigned int unit = 0; unit < game.states[turn].ports.size();unit++)
	{
	    unsigned int id = game.states[turn].ports[unit].id;
	    if (looksets.find(id) == looksets.end())
	    {
		looksets.insert( std::pair<idtype,LookupSet<GameObject*,idtype> >(id,LookupSet<GameObject*,idtype>(numTurns,numFrames,id) ));
	    }

	    GameObject * port = new GameObject(id);
	    //setup stuff

	    PortData * data = new PortData();
	    //PortRender * render = new PortRender();


	    //render->setOwner(port);
	    data->setOwner(port);

	    port->setGOC(data);
	    //port->setGOC(render);
	    //end setup

	    looksets[id].addNode(port,turn,0);
	}

    }

     std::map<idtype,LookupSet<GameObject*,idtype> > :: iterator it = looksets.begin();
    for (; it != looksets.end(); it++)
    {
	ObjectManager::reg(it->first,it->second);
    }

    return true;



#if 0

    //cout << "Number of Turns: " << g.states.size() << endl;

    for( int i = 0; i < (signed int)game.states.size(); i++ )
    {
  #if 0
      cout << "Turn: " << i << endl;
      cout << " -Mapp: " << g.states[i].mappables.size() << endl;
      cout << " -Unit: " << g.states[i].units.size() << endl;
      cout << " -Pyrt: " << g.states[i].pirates.size() << endl;
      cout << " -Plyr: " << g.states[i].players.size() << endl;
      cout << " -Ship: " << g.states[i].ships.size() << endl;
      cout << " -Tile: " << g.states[i].tiles.size() << endl;
      cout << " -Trea: " << g.states[i].treasures.size() << endl << endl;;
  #else

      enum dir
      {
	STOP,
	RIGHT,
	UP,
	LEFT,
	DOWN
      };

      int xoff[] = {0, 1, 0, -1, 0};
      int yoff[] = {0, 0, 1, 0, -1};
      dir direction = STOP;

      PirateDataInfo pdi;

      std::vector<std::vector<std::vector< PirateData> > >  piVec =
	std::vector<std::vector<std::vector<PirateData> > >(5,
	std::vector<std::vector<PirateData> >(game.states[0].mapSize,
	std::vector<PirateData> (game.states[0].mapSize) ) );

      for( std::map<int,Pirate>::iterator p = game.states[i].pirates.begin();
	  p != game.states[i].pirates.end();
	  p++
	 )
	 {

	  //We're past turn 0, so movement from the last turn should happen
	  // AND pirate exists
	  if(i>0 && game.states[i-1].pirates.find(p->first) != game.states[i-1].pirates.end())
	  {
	    //Find direction enum
	    int delta;
	    delta = p -> second.x - game.states[i-1].pirates[p->first].x;

	    switch(delta)
	    {
	      case -1:
		direction = LEFT;
		break;
	      case 1:
		direction = RIGHT;
		break;

	      default:
		direction = STOP;
		break;
	    }

	    delta = p->second.y - game.states[i-1].pirates[p->first].y;
	    if (delta != 0)//There was any vertical motion
	    {
	      switch(delta)
	      {
		case -1:
		  direction = UP;
		  break;
		case 1:
		  direction = DOWN;
		  break;
	      }
	    }
	  }

	  pdi.x = p->second.x;
	  pdi.y = p->second.y;
	  pdi.owner = p->second.owner;
	  pdi.totalHealth += p->second.health;
	  pdi.numPirates++;
	  pdi.totalStrength += p->second.strength;
	  pdi.movesLeft = p->second.movesLeft;
	  pdi.attacksLeft = p->second.attacksLeft;
	  pdi.piratesInStack.push_front(p->second.id);

	  int frame = (direction == STOP) ? 0 : 50;

	  //piVec[direction][p->second.x + xoff[direction]][p->second.y + yoff[direction]].addPirateStack( pdi, i, frame );

	 }


      //Step through moving stacks
      int stackId = 0;
      for(int z = 0; z < 5; z++)
      {
	for(int x = 0; x < game.states[0].mapSize; x++)
	{
	  for(int y = 0; y < game.states[0].mapSize; y++)
	  {
	    go = new GameObject( stackId );
	    PirateRender *pr = new PirateRender();
	    PirateData *pd = new PirateData();
	    *pd = piVec[z][x][y];
	    pd->setOwner( go );

	    pr->setOwner( go );

	    go->setGOC( pd );
	    go->setGOC( pr );
	    //Renderer<DupObj>::reg( stackId, go );

	    stackId++;
	  }
	}
      }

      for( std::map<int,Ship>::iterator s = game.states[i].ships.begin();
	  s != game.states[i].ships.end();
	  s++ )
      {
	if( s->second.id > boatId )
	{
	  boatId = s->second.id;
	  go  = new GameObject( boatId );
	  BoatData *bd = new BoatData();
	  bd->parseBoat( game, boatId );
	  BoatRender *br = new BoatRender();

	  bd->setOwner( go );
	  br->setOwner( go );
	  go->setGOC( bd );
	  go->setGOC( br );

	 // Renderer<DupObj>::reg( boatId, go );

	  boats++;
	}
      }

    for( std::map<int,Treasure>::iterator t = game.states[i].treasures.begin();
	  t != game.states[i].treasures.end();
	  t++ )
      {
	if( t->second.id > treasureId )
	{
	  treasureId = t->second.id;
	  go  = new GameObject( treasureId );
	  TreasureData *td = new TreasureData();
	  td->parseTreasure( game, treasureId );
	  TreasureRender *tr = new TreasureRender();

	  td->setOwner( go );
	  tr->setOwner( go );
	  go->setGOC( td );
	  go->setGOC( tr );

	  //Renderer<DupObj>::reg( treasureId, go );

	  treasures++;
	}
      }
  #endif

    }

    std::cout << "Boats: " << boats << ", Pirates: " << pirates << std::endl;
#endif

}

