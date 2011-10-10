#####
### Missouri S&T ACM SIG-Game Arena (Thunderdome)
#####

from django.shortcuts import render_to_response

from mysite.thunderdome.models import Match, Competitor, MatchData

import beanstalkc


def _stalk_status(connection, tube_name):


def index(request):
    # Let's start by having this page show some arena health statistics
    p = dict() # payload for the render_to_response

    c = beanstalkc.Connection()
    c.use('match-requests')
    tube_status = connection.stats_tube('match-requests')
    (p['ready_requests'], p['running_requests']) = \
        [tube_status[x] for x in ('current-jobs-ready',
                                  'current-jobs-reserved')]
    c.close()

    (p['new_matches'], p['scheduled_matches'], p['running_matches'], 
     p['complete_matches'], p['failed_matches']) = \
         [Match.objects.filter(status = x).count 
          for x in ('1', '2', '3', '4', '0')]

    p['sanity'] = p['ready_requests']  == p['scheduled_matches'] \
              and p['running_matches'] == p['running_requests']

    return render_to_response('thunderdome/index.html', p)
