# -*- coding: iso-8859-1 -*-
import pexpect
import sys
import time
import os

from ssh_session import ssh_session

TimeStamp = time.strftime("%m%d%y_%I%M%S%p",
                            time.localtime())

host = sys.argv[1]
accounts = file(sys.argv[2])
command = sys.argv[3]

for line in accounts:
  name, password = line.strip().split(' ')
  session = ssh_session(name, host, password, 1)
  session.ssh(command)

