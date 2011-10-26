using System;
using System.Runtime.InteropServices;

/// \brief A basic AI interface.

///This class implements most the code an AI would need to interface with the lower-level game code.
///AIs should extend this class to get a lot of builer-plate code out of the way
///The provided AI class does just that.
public abstract class BaseAI
{
  public static Base[] bases;
  public static Player[] players;
  public static Tile[] tiles;
  public static Virus[] viruses;
  IntPtr connection;
  public static int iteration;
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
    count = Client.getBaseCount(connection);
    bases = new Base[count];
    for(int i = 0; i < count; i++)
    {
      bases[i] = new Base(Client.getBase(connection, i));
    }
    count = Client.getPlayerCount(connection);
    players = new Player[count];
    for(int i = 0; i < count; i++)
    {
      players[i] = new Player(Client.getPlayer(connection, i));
    }
    count = Client.getTileCount(connection);
    tiles = new Tile[count];
    for(int i = 0; i < count; i++)
    {
      tiles[i] = new Tile(Client.getTile(connection, i));
    }
    count = Client.getVirusCount(connection);
    viruses = new Virus[count];
    for(int i = 0; i < count; i++)
    {
      viruses[i] = new Virus(Client.getVirus(connection, i));
    }

    if(!initialized)
    {
      initialized = true;
      init();
    }
    return run();
  }


  ///How many turns it has been since the beginning of the game
  public int turnNumber()
  {
    return Client.getTurnNumber(connection);
  }
  ///Player Number; either 0 or 1 (0 is player 1, 1 is player 2)
  public int playerID()
  {
    return Client.getPlayerID(connection);
  }
  ///What number game this is for the server
  public int gameNumber()
  {
    return Client.getGameNumber(connection);
  }
  ///BaseCost used in the virus price formula
  public int baseCost()
  {
    return Client.getBaseCost(connection);
  }
  ///Scalar used in the virus price formula
  public float scaleCost()
  {
    return Client.getScaleCost(connection);
  }
  ///The width of the map (max X value)
  public int width()
  {
    return Client.getWidth(connection);
  }
  ///The height of the map (max Y value)
  public int height()
  {
    return Client.getHeight(connection);
  }
}
