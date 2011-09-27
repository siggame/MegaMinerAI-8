using System;
using System.Runtime.InteropServices;

public class Client {
  [DllImport("client")]
  public static extern IntPtr createConnection();
  [DllImport("client")]
  public static extern int serverConnect(IntPtr connection, string host, string port);

  [DllImport("client")]
  public static extern int serverLogin(IntPtr connection, string username, string password);
  [DllImport("client")]
  public static extern int createGame(IntPtr connection);
  [DllImport("client")]
  public static extern int joinGame(IntPtr connection, int id);

  [DllImport("client")]
  public static extern void endTurn(IntPtr connection);
  [DllImport("client")]
  public static extern void getStatus(IntPtr connection);

  [DllImport("client")]
  public static extern int networkLoop(IntPtr connection);


    //commands
  [DllImport("client")]
  public static extern int baseSpawn(IntPtr self, int Level);
  [DllImport("client")]
  public static extern int playerTalk(IntPtr self, string message);
  [DllImport("client")]
  public static extern int virusMove(IntPtr self, int x, int y);
  [DllImport("client")]
  public static extern int virusTalk(IntPtr self, string message);

    //accessors
  [DllImport("client")]
  public static extern int getTurnNumber(IntPtr connection);
  [DllImport("client")]
  public static extern int getPlayerID(IntPtr connection);
  [DllImport("client")]
  public static extern int getGameNumber(IntPtr connection);
  [DllImport("client")]
  public static extern int getBasecost(IntPtr connection);
  [DllImport("client")]
  public static extern float getScalecost(IntPtr connection);

  [DllImport("client")]
  public static extern IntPtr getBase(IntPtr connection, int num);
  [DllImport("client")]
  public static extern int getBaseCount(IntPtr connection);
  [DllImport("client")]
  public static extern IntPtr getPlayer(IntPtr connection, int num);
  [DllImport("client")]
  public static extern int getPlayerCount(IntPtr connection);
  [DllImport("client")]
  public static extern IntPtr getTile(IntPtr connection, int num);
  [DllImport("client")]
  public static extern int getTileCount(IntPtr connection);
  [DllImport("client")]
  public static extern IntPtr getVirus(IntPtr connection, int num);
  [DllImport("client")]
  public static extern int getVirusCount(IntPtr connection);


    //getters
  [DllImport("client")]
  public static extern int mappableGetId(IntPtr ptr);
  [DllImport("client")]
  public static extern int mappableGetX(IntPtr ptr);
  [DllImport("client")]
  public static extern int mappableGetY(IntPtr ptr);

  [DllImport("client")]
  public static extern int baseGetId(IntPtr ptr);
  [DllImport("client")]
  public static extern int baseGetX(IntPtr ptr);
  [DllImport("client")]
  public static extern int baseGetY(IntPtr ptr);
  [DllImport("client")]
  public static extern int baseGetOwner(IntPtr ptr);

  [DllImport("client")]
  public static extern int playerGetId(IntPtr ptr);
  [DllImport("client")]
  public static extern string playerGetPlayerName(IntPtr ptr);
  [DllImport("client")]
  public static extern int playerGetByteDollars(IntPtr ptr);
  [DllImport("client")]
  public static extern int playerGetCycles(IntPtr ptr);

  [DllImport("client")]
  public static extern int tileGetId(IntPtr ptr);
  [DllImport("client")]
  public static extern int tileGetX(IntPtr ptr);
  [DllImport("client")]
  public static extern int tileGetY(IntPtr ptr);
  [DllImport("client")]
  public static extern int tileGetOwner(IntPtr ptr);

  [DllImport("client")]
  public static extern int virusGetId(IntPtr ptr);
  [DllImport("client")]
  public static extern int virusGetX(IntPtr ptr);
  [DllImport("client")]
  public static extern int virusGetY(IntPtr ptr);
  [DllImport("client")]
  public static extern int virusGetOwner(IntPtr ptr);
  [DllImport("client")]
  public static extern int virusGetLevel(IntPtr ptr);
  [DllImport("client")]
  public static extern int virusGetMovesLeft(IntPtr ptr);


    //properties

}
