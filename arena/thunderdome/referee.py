#!/usr/bin/env python
### Missouri S&T ACM SIG-Game Arena (Thunderdome)
#####

# Some magic to get a standalone python program hooked in to django
import sys
sys.path = ['/home/mnuck/', '/home/mnuck/django_dev_site'] + sys.path

from django.core.management import setup_environ
from django_dev_site import settings

setup_environ(settings)

# Non-Django 3rd Part Imports
import beanstalkc
import json

# My Imports
from thunderdome.models import Game, Client, GameData

def main():
    games = Game.objects.filter(status="Scheduled")
    for game in games:
        print [x.name for x in game.clients.all()], game.priority
    
main()
