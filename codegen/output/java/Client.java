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
  int unitMove(Pointer object, int x, int y);
  int unitTalk(Pointer object, String message);
  int pirateMove(Pointer object, int x, int y);
  int pirateTalk(Pointer object, String message);
  int piratePickupTreasure(Pointer object, int amount);
  int pirateDropTreasure(Pointer object, int amount);
  int pirateAttack(Pointer object, Pointer Target);
  int portCreatePirate(Pointer object);
  int portCreateShip(Pointer object);
  int shipMove(Pointer object, int x, int y);
  int shipTalk(Pointer object, String message);
  int shipAttack(Pointer object, Pointer Target);

    //accessors
  int getTurnNumber(Pointer connection);
  int getPlayerID(Pointer connection);
  int getGameNumber(Pointer connection);
  int getPlayer0Time(Pointer connection);
  int getPlayer1Time(Pointer connection);

  Pointer getPirate(Pointer connection, int num);
  int getPirateCount(Pointer connection);
  Pointer getPort(Pointer connection, int num);
  int getPortCount(Pointer connection);
  Pointer getShip(Pointer connection, int num);
  int getShipCount(Pointer connection);
  Pointer getTile(Pointer connection, int num);
  int getTileCount(Pointer connection);
  Pointer getTreasure(Pointer connection, int num);
  int getTreasureCount(Pointer connection);


    //getters
  int mappableGetId(Pointer ptr);
  int mappableGetX(Pointer ptr);
  int mappableGetY(Pointer ptr);

  int unitGetId(Pointer ptr);
  int unitGetX(Pointer ptr);
  int unitGetY(Pointer ptr);
  int unitGetOwner(Pointer ptr);
  int unitGetHealth(Pointer ptr);
  int unitGetStrength(Pointer ptr);

  int pirateGetId(Pointer ptr);
  int pirateGetX(Pointer ptr);
  int pirateGetY(Pointer ptr);
  int pirateGetOwner(Pointer ptr);
  int pirateGetHealth(Pointer ptr);
  int pirateGetStrength(Pointer ptr);

  int portGetId(Pointer ptr);
  int portGetX(Pointer ptr);
  int portGetY(Pointer ptr);
  int portGetOwner(Pointer ptr);

  int shipGetId(Pointer ptr);
  int shipGetX(Pointer ptr);
  int shipGetY(Pointer ptr);
  int shipGetOwner(Pointer ptr);
  int shipGetHealth(Pointer ptr);
  int shipGetStrength(Pointer ptr);

  int tileGetId(Pointer ptr);
  int tileGetX(Pointer ptr);
  int tileGetY(Pointer ptr);
  int tileGetType(Pointer ptr);

  int treasureGetId(Pointer ptr);
  int treasureGetX(Pointer ptr);
  int treasureGetY(Pointer ptr);
  Pointer treasureGetPirate(Pointer ptr);


    //properties

}
