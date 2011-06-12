#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
from subprocess import Popen

NUM_TENTACLES = 2

for i in range(NUM_TENTACLES):
  Popen("rm -rf /tmp/"+str(i), shell = True).wait()
  Popen("mkdir /tmp/"+str(i), shell = True).wait()
  f = open("/tmp/"+str(i)+"/config.cfg",'w')
  f.write(str(19000+1000*i)+'\n')
  f.write(str(i)+'\n')
  f.close()
  Popen("cp tentacle.py celeryconfig.py WebServerInterface.py /tmp/"+str(i),shell = True).wait()
  Popen("cp -r "+"server /tmp/"+str(i),shell = True, cwd = "../..").wait()
  Popen("celeryd -n tentacle."+str(i), shell = True, cwd="/tmp/"+str(i))
