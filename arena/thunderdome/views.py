#####
### Missouri S&T ACM SIG-Game Arena (Thunderdome)
#####

# Non-Django 3rd Party Imports
import beanstalkc

# Django Imports
from django.shortcuts import render_to_response, get_object_or_404
from django.http import HttpResponseRedirect
from django.core.context_processors import csrf

# My Imports
from thunderdome.models import Game, Client, GameData, InjectedGameForm

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
          for x in ('New', 'Scheduled', 'Running', 'Complete', 'Failed')]

    p['sanity'] = p['ready_requests']  == p['scheduled_games'] \
              and p['running_games'] == p['running_requests']

    return render_to_response('thunderdome/index.html', p)


def inject(request):
    ### Handle manual injection of a game into the system
    if request.method == 'POST':
        form = InjectedGameForm(request.POST)
        if form.is_valid():
            game = Game.objects.create(priority=form.cleaned_data['priority'])
            for client in Client.objects.filter(pk__in = \
                                                form.cleaned_data['clients']):
                GameData(game=game, client=client).save()
            game.schedule()
            payload = {'game': game}
            payload.update(csrf(request))
            return HttpResponseRedirect('view/%s' % game.pk)
    else:
        form = InjectedGameForm()
    
    payload = {'form': form}
    payload.update(csrf(request))
    return render_to_response('thunderdome/inject.html', payload)


def view_game(request, game_id):
    ### View the status of a single game
    return render_to_response('thunderdome/view_game.html', 
                              {'game': get_object_or_404(Game, pk=game_id)})
