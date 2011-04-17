#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
from subprocess import Popen

Popen("mkdir /tmp/1", shell = True).wait()
Popen("mkdir /tmp/2", shell = True).wait()
Popen("mkdir /tmp/3", shell = True).wait()
Popen("mkdir /tmp/4", shell = True).wait()
Popen("celeryd --concurrency=1 --time-limit=600", shell = True, cwd="/home/ubuntu/megaminer7/arena/competition/t1")
Popen("celeryd --concurrency=1 --time-limit=600" , shell = True, cwd="/home/ubuntu/megaminer7/arena/competition/t2")
Popen("celeryd --concurrency=1 --time-limit=600", shell = True, cwd="/home/ubuntu/megaminer7/arena/competition/t3")
Popen("celeryd --concurrency=1 --time-limit=600", shell = True, cwd="/home/ubuntu/megaminer7/arena/competition/t4")
