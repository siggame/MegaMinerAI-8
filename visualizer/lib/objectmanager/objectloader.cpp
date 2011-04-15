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
#include "../../piracy/piracylocations.h"
#include "../../piracy/objecttype.h"

#include "../goc_owner.h"
#include "../../piracy/gold.h"
#include "../renderer/renderer.h"
#include "../../piracy/dupObj.h"
#include "../selectionrender/selectionrender.h"

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
    GameObject *go = new GameObject( 1 );
    PirateMap *pm = new PirateMap();
    PirateData * data2 = new PirateData();
    pm->generateMap( game );
    pm->setOwner( go );
    go->setGOC( pm );
    Renderer<DupObj>::registerConstantObj( 1, go );

    go = new GameObject( 2 );
    go->setGOC( SelectionRender::get() );
    SelectionRender::get()->setOwner( go );
    Renderer<DupObj>::registerConstantObj( 2, go );

    return true;
    //Renderer<DupObj>::reg( -1, go );

    unsigned int numTurns = game.states.size();
    unsigned int numFrames = optionsMan::getInt("numFrames");
    TimeManager::setTurn(0);
    TimeManager::setNumTurns( numTurns );


    std::map<idtype, LookupSet<GameObject*,idtype> > looksets;

    for (unsigned int turn = 0; turn < game.states.size(); turn++)
    {
    //  looksets[-999].addNode( go, turn, 0 );

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
	    PiracyLocation * loc = new PiracyLocation();
	    GOC_Owner * owner = new GOC_Owner(pirate, game.states[turn].pirates[unit].owner);
	    Gold * gold = new Gold(pirate,game.states[turn].pirates[unit].gold);
	    ObjectType * type = new ObjectType(pirate,POT_PIRATE);

	    data->parsePirate(game,id,turn);
	    loc->parseLocation(&(game.states[turn].pirates[unit]));

	    data->setOwner(pirate);
	    loc->setOwner(pirate);


	    pirate->setGOC(data);
	    pirate->setGOC(loc);
	    pirate->setGOC(owner);
	    pirate->setGOC(gold);
	    pirate->setGOC(type);


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
	    PiracyLocation * loc = new PiracyLocation();
	    GOC_Owner * owner = new GOC_Owner(ship, game.states[turn].ships[unit].owner);
	    Gold * gold = new Gold(ship,game.states[turn].ships[unit].gold);
	    ObjectType * type = new ObjectType(ship,POT_SHIP);
	    //ShipRender * render = new ShipRender();

	    //render->setOwner(ship);
	    data->parseShip(game,id,turn);
	    loc->parseLocation(&(game.states[turn].ships[unit]));


	    loc->setOwner(ship);
	    data->setOwner(ship);

	    ship->setGOC(data);
	    ship->setGOC(loc);
	    ship->setGOC(owner);
	    ship->setGOC(gold);
	    ship->setGOC(type);

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
	    PiracyLocation * loc = new PiracyLocation();
	    Gold * gold = new Gold(treasure,game.states[turn].treasures[unit].gold);
	    ObjectType * type = new ObjectType(treasure,POT_TREAS);

	    data->parseTreasure(game,id,turn);
	    loc->parseLocation(&(game.states[turn].treasures[unit]));


	    data->setOwner(treasure);
	    loc->setOwner(treasure);

	    treasure->setGOC(data);
	    treasure->setGOC(loc);
	    treasure->setGOC(gold);
	    treasure->setGOC(type);

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
	    PiracyLocation * loc = new PiracyLocation();
	    GOC_Owner * owner = new GOC_Owner(port, game.states[turn].ports[unit].owner);
	    ObjectType * type = new ObjectType(port,POT_PORT);


	    data->parsePort(game,id,turn);
	    loc->parseLocation(&(game.states[turn].ports[unit]));

	    data->setOwner(port);
	    loc->setOwner(port);

	    port->setGOC(data);
	    port->setGOC(loc);
	    port->setGOC(owner);
	    port->setGOC(type);
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
}

