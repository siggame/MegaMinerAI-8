# -*- coding: iso-8859-1 -*-
import random
import sys
class Tile:
  type = '.'
  
def neighbors(size, x, y):
  result = []
  for i in (-1, 0), (1, 0), (0, -1), (0, 1):
    xf = x + i[0]
    yf = y + i[1]
    
    if xf < 0 or xf >= size or yf < 0 or yf >= size:
      continue
    else:
      result.append( (xf, yf) )
  return result

def groupNeighbors(size, l):
  result = []
  for i in l:
    for j in neighbors(size, i[0], i[1]):
      result.append(j)
  return result

def makeMap(size, islands, growth):
  map = [ [Tile() for i in xrange(size) ] for j in xrange(size) ]
  
  #set up the symmetry
  #this seems like it could be refactored, not sure how yet
  if random.randint(0, 2) == 0:
    #diagonal symmetry
    for i in xrange(size):
      for j in xrange(i+1, size):
        map[i][j] = map[j][i]
  else:
    if random.randint(0, 1):
      #vertical symmetry
      for i in xrange(size):
        for j in xrange(size/2):
          map[i][j] = map[i][size-1-j]
    else:
      #rotational symmetry
      for i in xrange(size):
        for j in xrange(size/2):
          map[i][j] = map[size-1-i][size-1-j]

  if random.randint(0, 1):
    #rotate the map pi/2
    map = [ [ map[j][size-1-i] for j in xrange(size) ] for i in xrange(size) ]

  
  land = []
  
  for i in xrange(islands):
    x = random.randrange(size)
    y = random.randrange(size)
    if map[x][y].type == 'X':
      continue
    land.append( (x, y) )
    map[x][y].type = 'X'
  
  print groupNeighbors(size, land)
  for i in xrange(growth):
    borders = [i for i in groupNeighbors(size, land) if map[i[0]][i[1]].type == '.' ]
    next = random.choice(borders)
    map[next[0]][next[1]].type = 'X'
    land.append(next)
  
  
  print '\n'.join([' '.join([j.type for j in i]) for i in map] )

if len(sys.argv) < 3:
  makeMap(40, 10, 200)
else:  
  makeMap(int(sys.argv[1]),int(sys.argv[2]),int(sys.argv[3]))
  
