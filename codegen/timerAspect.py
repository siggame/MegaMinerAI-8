from structures import *

def install():
  import data
  data.globals.append( Variable('player0Time', int, 'Player 0\'s time remaining') )
  data.globals.append( Variable('player1Time', int, 'Player 1\'s time remaining') )

  data.aspects.append('timer')
