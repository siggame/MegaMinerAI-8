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

for line in accounts:
  name, password, hint = line.split(' ')
  print name
  session = ssh_session(name, host, password, 1)
  session.scp_back("~", name)
