public interface Client : Library {
  Client INSTANCE = (Client)Native.loadLibrary("client", Client.class);
  [DllImport("client")]
  IntPtr createConnection();
  [DllImport("client")]
  boolean serverConnect(IntPtr connection, String host, String port);

  [DllImport("client")]
  boolean serverLogin(IntPtr connection, String username, String password);
  [DllImport("client")]
  int createGame(IntPtr connection);
  [DllImport("client")]
  int joinGame(IntPtr connection, int id);

  [DllImport("client")]
  void endTurn(IntPtr connection);
  [DllImport("client")]
  void getStatus(IntPtr connection);

  [DllImport("client")]
  int networkLoop(IntPtr connection);


    //commands
  [DllImport("client")]
  int pieceMove(IntPtr object, int file, int rank, int type);

    //accessors
  [DllImport("client")]
  int getTurnNumber(IntPtr connection);
  [DllImport("client")]
  int getPlayerID(IntPtr connection);
  [DllImport("client")]
  int getGameNumber(IntPtr connection);
  [DllImport("client")]
  int getTurnsToStalemate(IntPtr connection);
  [DllImport("client")]
  int getPlayer0Time(IntPtr connection);
  [DllImport("client")]
  int getPlayer1Time(IntPtr connection);

  [DllImport("client")]
  IntPtr getMove(IntPtr connection, int num);
  [DllImport("client")]
  int getMoveCount(IntPtr connection);
  [DllImport("client")]
  IntPtr getPiece(IntPtr connection, int num);
  [DllImport("client")]
  int getPieceCount(IntPtr connection);


    //getters
  [DllImport("client")]
  int moveGetId(IntPtr ptr);
  [DllImport("client")]
  int moveGetFromFile(IntPtr ptr);
  [DllImport("client")]
  int moveGetFromRank(IntPtr ptr);
  [DllImport("client")]
  int moveGetToFile(IntPtr ptr);
  [DllImport("client")]
  int moveGetToRank(IntPtr ptr);
  [DllImport("client")]
  int moveGetPromoteType(IntPtr ptr);

  [DllImport("client")]
  int pieceGetId(IntPtr ptr);
  [DllImport("client")]
  int pieceGetOwner(IntPtr ptr);
  [DllImport("client")]
  int pieceGetFile(IntPtr ptr);
  [DllImport("client")]
  int pieceGetRank(IntPtr ptr);
  [DllImport("client")]
  int pieceGetHasMoved(IntPtr ptr);
  [DllImport("client")]
  int pieceGetType(IntPtr ptr);


    //properties

}
