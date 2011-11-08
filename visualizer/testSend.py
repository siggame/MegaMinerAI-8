import socket
from struct import *

TCP_IP = '127.0.0.1'
TCP_PORT = 12345

f = open( '/home/jacob/gamelogs/100.glog', 'rb' )

MSG = f.read()

st = pack( '!{0}s'.format( len(MSG) ), MSG )

s = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
s.connect( (TCP_IP, TCP_PORT) )

sz = pack( '!I', len( MSG ) )
s.send( sz )

s.send( st )

s.close()
