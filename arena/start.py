#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
import sys
from subprocess import Popen
import pexpect

GIT_PATH = "ssh://siggame@r99acm.device.mst.edu:2222/srv/megaminer7.git"
password = 'MSeiggagMaimnee1r'

command = "git clone " + GIT_PATH
p = pexpect.spawn(command, cwd = "/home/ubuntu") 
i = p.expect(['Password:',pexpect.EOF])
if i == 0:
  p.sendline(password)
  p.expect(pexpect.EOF, timeout = 300)

Popen("/usr/bin/python /home/ubuntu/megaminer7/arena/tentacle/start.py", shell=True, cwd = "/home/ubuntu/megaminer7/arena/tentacle")
