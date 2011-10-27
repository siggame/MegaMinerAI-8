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
import beanstalkc, boto
import subprocess, shutil, os
import socket, time


def main():
    stalk = beanstalkc.Connection()
    stalk.watch('master-requests')    
    server = start_server()
    refs = list()
    refs.append( start_referee(1, '/home/mnuck/arena/server') )
    refs.append( start_referee(2, '/home/mnuck/arena/server') )
    refs.append( start_referee(3, '/home/mnuck/arena/server') )
    refs.append( start_referee(4, '/home/mnuck/arena/server') )
    refs.append( start_referee(5, '/home/mnuck/arena/server') )
    refs.append( start_referee(6, '/home/mnuck/arena/server') )
    refs.append( start_referee(7, '/home/mnuck/arena/server') )
    refs.append( start_referee(8, '/home/mnuck/arena/server') )
    refs.append( start_referee(9, '/home/mnuck/arena/server') )
    refs.append( start_referee(10, '/home/mnuck/arena/server') )
    while True:
        time.sleep(1)


def start_server():
    command = ['python', 'main.py']
    return subprocess.Popen(command, cwd='server',
                            stdout=file("/dev/null", "w"),
                            stderr=subprocess.STDOUT)


def start_referee(ref_id, server_path):
    subprocess.call(['rm', '-rf', str(ref_id)])
    subprocess.call(['mkdir', str(ref_id)])
    subprocess.call(['ln', '../aws_creds.py'], cwd='%s/' % ref_id)
    subprocess.call(['ln', '../referee.py'], cwd='%s/' % ref_id)
    command = ['./referee.py', server_path]
    return subprocess.Popen(command, cwd=str(ref_id))
#                            stdout=file("/dev/null", "w"),
#                            stderr=subprocess.STDOUT)

main()
