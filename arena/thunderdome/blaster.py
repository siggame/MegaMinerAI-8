#!/usr/bin/env python
### Missouri S&T ACM SIG-Game Arena (Thunderdome)
#####

# Some magic to get a standalone python program hooked in to django
import sys
sys.path = ['/srv/', '/srv/uard'] + sys.path

from django.core.management import setup_environ
import settings

setup_environ(settings)

# Non-Django 3rd Party Imports
import beanstalkc
import subprocess
import time


def main():
    stalk = beanstalkc.Connection()
    stalk.watch('master-requests')

    port = 19000
    servers = list()
    for i in xrange(2):
        servers.append( start_server(i, str(port)) )
        port += 1
        
    refs = list()
    port = 19000
    for server_id in xrange(len(servers)):
        for i in xrange(8):
            refs.append( start_referee(server_id, i, '/home/mnuck/arena/s%i/server' % server_id, str(port)))
        port += 1

    while True:
        time.sleep(1)


def start_server(server_id, port='19000'):
    subprocess.call(['rm', '-rf', 's%s' % str(server_id)])
    subprocess.call(['mkdir', 's%s' % str(server_id)])
    subprocess.call(['cp', '-R', 'server', 's%s' % str(server_id)])
    command = ['python', 'main.py', '-arena', '-port', port]
    return subprocess.Popen(command, cwd='s%s/server' % str(server_id),
                            stdout=file("/dev/null", "w"),
                            stderr=subprocess.STDOUT)


def start_referee(server_id, ref_id, server_path, port='19000'):
    subprocess.call(['rm', '-rf', '%s-%s' % (str(server_id),str(ref_id))])
    subprocess.call(['mkdir', '%s-%s' % (str(server_id),str(ref_id))])
    subprocess.call(['ln', '../aws_creds.py'], cwd='%s-%s/' % (str(server_id),str(ref_id)))
    subprocess.call(['ln', '../referee.py'], cwd='%s-%s/' % (str(server_id),str(ref_id)))
    command = ['./referee.py', server_path, port]
    print command
    return subprocess.Popen(command, cwd='%s-%s' % (str(server_id),str(ref_id)))
#                            stdout=file("/dev/null", "w"),
#                            stderr=subprocess.STDOUT)

main()
