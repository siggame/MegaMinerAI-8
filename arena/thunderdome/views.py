#####
### Missouri S&T ACM SIG-Game Arena (Thunderdome)
#####

# Non-Django 3rd Party Imports
import beanstalkc

# Django Imports
from django.shortcuts import render_to_response

# My Imports
from thunderdome.models import Game


def index(request):
    # Let's start by having this page show some arena health statistics
    p = dict() # payload for the render_to_response

    c = beanstalkc.Connection()
    c.use('game-requests')
    tube_status = c.stats_tube('game-requests')
    (p['ready_requests'], p['running_requests']) = \
        [tube_status[x] for x in ('current-jobs-ready',
                                  'current-jobs-reserved')]
    c.close()

    (p['new_games'], p['scheduled_games'], p['running_games'], 
     p['complete_games'], p['failed_games']) = \
         [Game.objects.filter(status = x).count 
          for x in ('1', '2', '3', '4', '0')]

    p['sanity'] = p['ready_requests']  == p['scheduled_games'] \
              and p['running_games'] == p['running_requests']

    return render_to_response('thunderdome/index.html', p)
