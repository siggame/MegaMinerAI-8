import socket
from struct import *
import time

IPs = [ '192.168.1.132', '127.0.0.1' ]

TCP_PORT = 12345

gamelogs = [ '/home/jacob/gamelogs/100.glog', '/home/jacob/gamelogs/123.glog', '/home/jacob/gamelogs/100.glog', '/home/jacob/gamelogs/123.glog' ]

for g in gamelogs:
  f = open( g, 'rb' )

  MSG = f.read()
  st = pack( '!{0}s'.format( len(MSG) ), MSG )
  sz = pack( '!I', len( MSG ) )

  for i in IPs:
    s = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
    s.connect( (i, TCP_PORT) )

    s.send( sz )

    s.send( st )

    s.close()
  time.sleep( 20 )
