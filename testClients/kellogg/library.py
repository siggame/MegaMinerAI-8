# -*-python-*-

import os

from ctypes import *

try:
  if os.name == 'posix':
    library = CDLL("./libclient.so")
  elif os.name == 'nt':
    library = CDLL("./client.dll")
  else:
    raise Exception("Unrecognized OS: "+os.name)
except OSError:
  raise Exception("It looks like you didn't build libclient. Run 'make' and try again.")

# commands

library.createConnection.restype = c_void_p
library.createConnection.argtypes = []

library.serverLogin.restype = c_int
library.serverLogin.argtypes = [c_void_p, c_char_p, c_char_p]

library.createGame.restype = c_int
library.createGame.argtypes = [c_void_p]

library.joinGame.restype = c_int
library.joinGame.argtypes = [c_void_p, c_int]

library.endTurn.restype = None
library.endTurn.argtypes = [c_void_p]

library.getStatus.restype = None
library.getStatus.argtypes = [c_void_p]

library.networkLoop.restype = c_int
library.networkLoop.argtypes = [c_void_p]

#Functions
library.baseSpawn.restype = c_int
library.baseSpawn.argtypes = [c_void_p, c_int]

library.playerTalk.restype = c_int
library.playerTalk.argtypes = [c_void_p, c_char_p]

library.virusMove.restype = c_int
library.virusMove.argtypes = [c_void_p, c_int, c_int]

library.virusTalk.restype = c_int
library.virusTalk.argtypes = [c_void_p, c_char_p]

# accessors

#Globals 
library.getTurnNumber.restype = c_int
library.getTurnNumber.argtypes = [c_void_p]

library.getPlayerID.restype = c_int
library.getPlayerID.argtypes = [c_void_p]

library.getGameNumber.restype = c_int
library.getGameNumber.argtypes = [c_void_p]

library.getBaseCost.restype = c_int
library.getBaseCost.argtypes = [c_void_p]

library.getScaleCost.restype = c_float
library.getScaleCost.argtypes = [c_void_p]

library.getWidth.restype = c_int
library.getWidth.argtypes = [c_void_p]

library.getHeight.restype = c_int
library.getHeight.argtypes = [c_void_p]

library.getBase.restype = c_void_p
library.getBase.argtypes = [c_void_p, c_int]

library.getBaseCount.restype = c_int
library.getBaseCount.argtypes = [c_void_p]

library.getPlayer.restype = c_void_p
library.getPlayer.argtypes = [c_void_p, c_int]

library.getPlayerCount.restype = c_int
library.getPlayerCount.argtypes = [c_void_p]

library.getTile.restype = c_void_p
library.getTile.argtypes = [c_void_p, c_int]

library.getTileCount.restype = c_int
library.getTileCount.argtypes = [c_void_p]

library.getVirus.restype = c_void_p
library.getVirus.argtypes = [c_void_p, c_int]

library.getVirusCount.restype = c_int
library.getVirusCount.argtypes = [c_void_p]

# getters

#Data
library.mappableGetId.restype = c_int
library.mappableGetId.argtypes = [c_void_p]

library.mappableGetX.restype = c_int
library.mappableGetX.argtypes = [c_void_p]

library.mappableGetY.restype = c_int
library.mappableGetY.argtypes = [c_void_p]

library.baseGetId.restype = c_int
library.baseGetId.argtypes = [c_void_p]

library.baseGetX.restype = c_int
library.baseGetX.argtypes = [c_void_p]

library.baseGetY.restype = c_int
library.baseGetY.argtypes = [c_void_p]

library.baseGetOwner.restype = c_int
library.baseGetOwner.argtypes = [c_void_p]

library.baseGetSpawnsLeft.restype = c_int
library.baseGetSpawnsLeft.argtypes = [c_void_p]

library.playerGetId.restype = c_int
library.playerGetId.argtypes = [c_void_p]

library.playerGetPlayerName.restype = c_char_p
library.playerGetPlayerName.argtypes = [c_void_p]

library.playerGetByteDollars.restype = c_int
library.playerGetByteDollars.argtypes = [c_void_p]

library.playerGetCycles.restype = c_int
library.playerGetCycles.argtypes = [c_void_p]

library.playerGetTime.restype = c_int
library.playerGetTime.argtypes = [c_void_p]

library.tileGetId.restype = c_int
library.tileGetId.argtypes = [c_void_p]

library.tileGetX.restype = c_int
library.tileGetX.argtypes = [c_void_p]

library.tileGetY.restype = c_int
library.tileGetY.argtypes = [c_void_p]

library.tileGetOwner.restype = c_int
library.tileGetOwner.argtypes = [c_void_p]

library.virusGetId.restype = c_int
library.virusGetId.argtypes = [c_void_p]

library.virusGetX.restype = c_int
library.virusGetX.argtypes = [c_void_p]

library.virusGetY.restype = c_int
library.virusGetY.argtypes = [c_void_p]

library.virusGetOwner.restype = c_int
library.virusGetOwner.argtypes = [c_void_p]

library.virusGetLevel.restype = c_int
library.virusGetLevel.argtypes = [c_void_p]

library.virusGetMovesLeft.restype = c_int
library.virusGetMovesLeft.argtypes = [c_void_p]

library.virusGetLiving.restype = c_int
library.virusGetLiving.argtypes = [c_void_p]


#Properties
