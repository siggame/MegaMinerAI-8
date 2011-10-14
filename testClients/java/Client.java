import com.sun.jna.Library;
import com.sun.jna.Pointer;
import com.sun.jna.Native;

public interface Client extends Library {
  Client INSTANCE = (Client)Native.loadLibrary("client", Client.class);
  Pointer createConnection();
  boolean serverConnect(Pointer connection, String host, String port);

  boolean serverLogin(Pointer connection, String username, String password);
  int createGame(Pointer connection);
  int joinGame(Pointer connection, int id);

  void endTurn(Pointer connection);
  void getStatus(Pointer connection);

  int networkLoop(Pointer connection);


    //commands
  int baseSpawn(Pointer object, int Level);
  int playerTalk(Pointer object, String message);
  int virusMove(Pointer object, int x, int y);
  int virusTalk(Pointer object, String message);

    //accessors
  int getTurnNumber(Pointer connection);
  int getPlayerID(Pointer connection);
  int getGameNumber(Pointer connection);
  int getBaseCost(Pointer connection);
  float getScaleCost(Pointer connection);
  int getWidth(Pointer connection);
  int getHeight(Pointer connection);

  Pointer getBase(Pointer connection, int num);
  int getBaseCount(Pointer connection);
  Pointer getPlayer(Pointer connection, int num);
  int getPlayerCount(Pointer connection);
  Pointer getTile(Pointer connection, int num);
  int getTileCount(Pointer connection);
  Pointer getVirus(Pointer connection, int num);
  int getVirusCount(Pointer connection);


    //getters
  int mappableGetId(Pointer ptr);
  int mappableGetX(Pointer ptr);
  int mappableGetY(Pointer ptr);

  int baseGetId(Pointer ptr);
  int baseGetX(Pointer ptr);
  int baseGetY(Pointer ptr);
  int baseGetOwner(Pointer ptr);
  int baseGetSpawnsLeft(Pointer ptr);

  int playerGetId(Pointer ptr);
  String playerGetPlayerName(Pointer ptr);
  int playerGetByteDollars(Pointer ptr);
  int playerGetCycles(Pointer ptr);

  int tileGetId(Pointer ptr);
  int tileGetX(Pointer ptr);
  int tileGetY(Pointer ptr);
  int tileGetOwner(Pointer ptr);

  int virusGetId(Pointer ptr);
  int virusGetX(Pointer ptr);
  int virusGetY(Pointer ptr);
  int virusGetOwner(Pointer ptr);
  int virusGetLevel(Pointer ptr);
  int virusGetMovesLeft(Pointer ptr);


    //properties

}
