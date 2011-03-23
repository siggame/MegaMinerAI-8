from structures import *

def install(data):
  data.Player.data.append( Variable('time', int, 'Time remaining') )