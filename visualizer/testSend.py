import socket
from struct import *
import time
import os
import random

IPs = [ '127.0.0.1' ]

TCP_PORT = 12345

counter = 0

while 1:

  d = os.listdir( '/home/jacob/gamelogs/' )

  fOpen = '/home/jacob/gamelogs/{0}'.format( d[ random.randint( 0, len( d ) - 1 ) ] )
  print fOpen

  f = open( fOpen, 'rb' )


  MSG = f.read()
  st = pack( '!{0}s'.format( len(MSG) ), MSG )
  sz = pack( '!I', len( MSG ) )

  for i in IPs:
    s = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
    s.connect( (i, TCP_PORT) )

    s.send( sz )

    s.send( st )

    s.close()
  time.sleep( 2 )
  counter += 1
  print counter
