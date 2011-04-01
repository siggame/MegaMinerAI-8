#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
import data
import structures
from util import *
from copy import copy

def insertModel(list, model):
  if model.parent and model.parent not in list:
    insertModel(list, model.parent)
  if model not in list:
    list.append(model)

def parseData():
  aspects = data.aspects

  if 'timer' in aspects:
    import timerAspect
    timerAspect.install(data)

  models = []
  globals = data.globals
  constants = data.constants
  animations = []
  for i in members(data):
    if isinstance(i, structures.Model):
      insertModel(models, i)
    elif isinstance(i, structures.Animation):
      animations.append(i)
  return {'models':models, 'globals':globals, 'constants':constants, 'animations':animations, 'aspects':aspects}



if __name__ == '__main__':
  objects = parseData()
  
  import writeC
  writeC.write(copy(objects))

  import writeServer
  writeServer.write(copy(objects))
  
  import writeJava
  writeJava.write(objects)
  
  import writeCS
  writeCS.write(objects)
  
  import writePython
  writePython.write(objects)
  
  
  import writeVisualizer
  writeVisualizer.write(objects)
  
