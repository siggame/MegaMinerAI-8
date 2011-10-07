import com.sun.jna.Pointer;

/// \brief A basic AI interface.

///This class implements most the code an AI would need to interface with the lower-level game code.
///AIs should extend this class to get a lot of builer-plate code out of the way
///The provided AI class does just that.
public abstract class BaseAI
{
  static Base[] bases;
  static Player[] players;
  static Tile[] tiles;
  static Virus[] viruses;
  Pointer connection;
  static int iteration;
  boolean initialized;

  public BaseAI(Pointer c)
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
  public abstract boolean run();

  ///
  ///This is run on after your last turn.
  public abstract void end();


  public boolean startTurn()
  {
    iteration++;
    int count = 0;
    count = Client.INSTANCE.getBaseCount(connection);
    bases = new Base[count];
    for(int i = 0; i < count; i++)
    {
      bases[i] = new Base(Client.INSTANCE.getBase(connection, i));
    }
    count = Client.INSTANCE.getPlayerCount(connection);
    players = new Player[count];
    for(int i = 0; i < count; i++)
    {
      players[i] = new Player(Client.INSTANCE.getPlayer(connection, i));
    }
    count = Client.INSTANCE.getTileCount(connection);
    tiles = new Tile[count];
    for(int i = 0; i < count; i++)
    {
      tiles[i] = new Tile(Client.INSTANCE.getTile(connection, i));
    }
    count = Client.INSTANCE.getVirusCount(connection);
    viruses = new Virus[count];
    for(int i = 0; i < count; i++)
    {
      viruses[i] = new Virus(Client.INSTANCE.getVirus(connection, i));
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
  ///Player Number; either 0 or 1 (0 is player 1, 1 is player 2)
  int playerID()
  {
    return Client.INSTANCE.getPlayerID(connection);
  }
  ///What number game this is for the server
  int gameNumber()
  {
    return Client.INSTANCE.getGameNumber(connection);
  }
  ///BaseCost used in the virus price formula
  int basecost()
  {
    return Client.INSTANCE.getBasecost(connection);
  }
  ///Scalar used in the virus price formula
  float scalecost()
  {
    return Client.INSTANCE.getScalecost(connection);
  }
}
