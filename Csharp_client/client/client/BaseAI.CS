using System;
using System.Runtime.InteropServices;

/// \brief A basic AI interface.

///This class implements most the code an AI would need to interface with the lower-level game code.
///AIs should extend this class to get a lot of builer-plate code out of the way
///The provided AI class does just that.
public abstract class BaseAI
{
  static Pirate[] pirates;
  static Port[] ports;
  static Ship[] ships;
  static Tile[] tiles;
  static Treasure[] treasures;
  IntPtr connection;
  static int iteration;
  bool initialized;

  public BaseAI(IntPtr c)
  {
    connection = c;
  }
    
  ///
  ///Make this your username, which should be provided.
  public abstract String username();
  ///
  ///Make this your password, which should be provided.
  public abstract String password();
  ///
  ///This is run on turn 1 before run
  public abstract void init();
  ///
  ///This is run every turn . Return true to end the turn, return false
  ///to request a status update from the server and then immediately rerun this function with the
  ///latest game status.
  public abstract bool run();

  ///
  ///This is run on after your last turn.
  public abstract void end();


  public bool startTurn()
  {
    iteration++;
    int count = 0;
    count = Client.INSTANCE.getPirateCount(connection);
    pirates = new Pirate[count];
    for(int i = 0; i < count; i++)
    {
      pirates[i] = new Pirate(Client.INSTANCE.getPirate(connection, i));
    }
    count = Client.INSTANCE.getPortCount(connection);
    ports = new Port[count];
    for(int i = 0; i < count; i++)
    {
      ports[i] = new Port(Client.INSTANCE.getPort(connection, i));
    }
    count = Client.INSTANCE.getShipCount(connection);
    ships = new Ship[count];
    for(int i = 0; i < count; i++)
    {
      ships[i] = new Ship(Client.INSTANCE.getShip(connection, i));
    }
    count = Client.INSTANCE.getTileCount(connection);
    tiles = new Tile[count];
    for(int i = 0; i < count; i++)
    {
      tiles[i] = new Tile(Client.INSTANCE.getTile(connection, i));
    }
    count = Client.INSTANCE.getTreasureCount(connection);
    treasures = new Treasure[count];
    for(int i = 0; i < count; i++)
    {
      treasures[i] = new Treasure(Client.INSTANCE.getTreasure(connection, i));
    }

    if(!initialized)
    {
      initialized = true;
      init();
    }
    return run();
  }


  ///How many turns it has been since the beginning of the game
  int turnNumber()
  {
    return Client.INSTANCE.getTurnNumber(connection);
  }
  ///Player Number; either 0 or 1
  int playerID()
  {
    return Client.INSTANCE.getPlayerID(connection);
  }
  ///What number game this is for the server
  int gameNumber()
  {
    return Client.INSTANCE.getGameNumber(connection);
  }
  ///Player 0's time remaining
  int player0Time()
  {
    return Client.INSTANCE.getPlayer0Time(connection);
  }
  ///Player 1's time remaining
  int player1Time()
  {
    return Client.INSTANCE.getPlayer1Time(connection);
  }
}
