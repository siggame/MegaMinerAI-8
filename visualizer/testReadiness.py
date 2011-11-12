import socket
from struct import *
import time
import os
import random

READY_PORT = 49205
FILE_PORT = 49235
IPs = [ '131.151.115.150' ] 
while 1: 
  for i in IPs:
    s = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
    print "connecting"
    s.connect( (i, READY_PORT) )
    
    print "connected"

    ready = s.recv( 1 )

    ready = unpack( 'b', ready )[ 0 ] 

    s.close()

    print "ready" 


    time.sleep( 5 )

    if ready == 1:
      d = os.listdir( '/home/jacob/gamelogs/' )

      fOpen = '/home/jacob/gamelogs/{0}'.format( d[ random.randint( 0, len( d ) - 1 ) ] )
      print fOpen

      f = open( fOpen, 'rb' )


      MSG = f.read()
      st = pack( '!{0}s'.format( len(MSG) ), MSG )
      sz = pack( '!I', len( MSG ) )

      s = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
      s.connect( (i, FILE_PORT) )

      s.send( sz )
      s.send( st )

      s.close()

      time.sleep( 2 )

