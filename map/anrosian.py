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

def makeSymmetry(map):
  size = len(map)

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

def findWaters(map):
  size = len(map)
  groupCount = 0
  groups = []
  for i in map:
    for j in i:
      j.group = 0

  for i in xrange(size):
    for j in xrange(size):
      if map[i][j].type == '.' and map[i][j].group == 0:
        groupCount += 1
        adjacent = [(i, j)]
        groups.append([])

        while adjacent:
          next = adjacent.pop()
          tile = map[next[0]][next[1]]
          if tile.type == '.' and tile.group == 0:
            tile.group = groupCount
            groups[-1].append(next)
            for k in neighbors(size, *next):
              adjacent.append(k)

  return groups

def placeStarts(map):
  waters = sorted(findWaters(map), key=len, reverse=True)

  neighbors = groupNeighbors(len(map), waters[0])

  random.shuffle(neighbors)

  for i in neighbors:
    if map[i[0]][i[1]].type == 'X':
      map[i[0]][i[1]].type = 'P'
      break

def placePorts(map, number = 5):
  waters = sorted(findWaters(map), key=len, reverse=True)

  neighbors = groupNeighbors(len(map), waters[0])

  random.shuffle(neighbors)

  for i in neighbors:
    if not number:
      return 
    if map[i[0]][i[1]].type == 'X':
      map[i[0]][i[1]].type = `number`
      number -= 1


def makeMap(size, islands, growth):
  map = [ [Tile() for i in xrange(size) ] for j in xrange(size) ]
  
  makeSymmetry(map)

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
  
  for i in xrange(growth):
    borders = [i for i in groupNeighbors(size, land) if map[i[0]][i[1]].type == '.' ]
    next = random.choice(borders)
    map[next[0]][next[1]].type = 'X'
    land.append(next)
 
  placeStarts(map)
  placePorts(map)

  print '\n'.join([' '.join([j.type for j in i]) for i in map] )

if len(sys.argv) < 3:
  makeMap(40, 10, 200)
else:  
  makeMap(int(sys.argv[1]),int(sys.argv[2]),int(sys.argv[3]))
  
