# -*- coding: utf-8 -*-
import time
import rpyc
from bz2 import decompress
from subprocess import Popen

import traceback

dbManagerName='r03mwwcp2.device.mst.edu'
updateServerName='r03mwwcp2.device.mst.edu'
class ArenaVisualizer:
  def __init__(self):
    #something something Database callback something
    self.dbServer=rpyc.connect(dbManagerName,18863)
    
  def run(self):
    while True:
      time.sleep(1)
      next = self.dbServer.root.nextVideo()
      print next
      if next:
        #I am become like unto a tentacle!
        try:
          logText = self.dbServer.root.read(next)
          f = open('game.gamelog', 'wb')
          f.write(decompress(logText))
          f.close()
          s = Popen('./visualizer game.gamelog', shell = True)
          s.wait()
        except:
          print 'Tried and Failed!'
          traceback.print_exc()
          pass

if __name__ == '__main__':
  vis = ArenaVisualizer()
  vis.run()