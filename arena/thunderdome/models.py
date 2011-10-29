#####
### Missouri S&T ACM SIG-Game Arena (Thunderdome)
#####

# Standard Imports
from datetime import datetime
from random import random

# Non-Django 3rd Party Imports
import beanstalkc
import time
import json

# Django Imports
from django import forms
from django.db import models
from django.forms.widgets import CheckboxSelectMultiple
from django.db.models import Max

class Client(models.Model):
    ### A competitor in the arena
    name            = models.CharField(max_length=100)
    current_version = models.CharField(max_length=100, default='')
    embargoed       = models.BooleanField(default=False) # fail to compile?
        
    def last_game(self):
        last = self.game_set.all().aggregate(Max('pk'))
        if last['pk__max']:
            return last['pk__max']
        else:
            return -1
    
    def last_visualized(self):
        vis = self.game_set.all().aggregate(Max('visualized'))
        if vis['visualized__max']:
            return vis['visualized__max']
        else:
            return datetime(1970,1,1,0,0)
    
    def wins(self):
        return [x.game for x in self.gamedata_set.filter(won=True)]
    
    def losses(self):
        return [x.game for x in self.gamedata_set.filter(won=False)]
    
    def __unicode__(self):
        return self.name

    
class Game(models.Model):
    ### A single match
    clients     = models.ManyToManyField(Client, through='GameData')
    status      = models.CharField(max_length=20, 
                                   default='New')
    priority    = models.IntegerField(default=1000)
    gamelog_url = models.CharField(max_length=200, default='')
    visualized  = models.DateTimeField(default=datetime(1970,1,1),null=True)
    completed   = models.DateTimeField(null=True)
    stats       = models.TextField(default='') # holds extra stuff via JSON
    
    def schedule(self):
        if self.status != 'New':
            return False
        if self.pk == None:
            self.save()
        return self.force_schedule()
    
    def force_schedule(self):
        c = beanstalkc.Connection()
        c.use('game-requests')
        payload = json.dumps({'game_id'    : str(self.pk),
                              'entry_time' : str(time.time()) })
        c.put(payload, priority=self.priority)
        c.close()
        self.status='Scheduled'
        self.save()
        return True

    def __unicode__(self):
        return unicode(self.pk)


class GameData(models.Model):
    ### each Match will have one of these for each competitor in that match
    game       = models.ForeignKey(Game)
    client     = models.ForeignKey(Client)
    compiled   = models.NullBooleanField()
    won        = models.NullBooleanField()
    version    = models.CharField(max_length=100, default='')
    stats      = models.TextField(default='') # holds extra stuff via JSON

    def __unicode__(self):
        return u"%s - %s" % (self.game.pk, self.client.name)


class InjectedGameForm(forms.Form):
    ### Used to manually inject a game into the queue
    priority = forms.IntegerField(min_value=0, max_value=1000)
    clients = forms.MultipleChoiceField(widget=CheckboxSelectMultiple)
    
    def __init__(self, *args, **kwargs):
        super(InjectedGameForm, self).__init__(*args, **kwargs)
        self.fields['clients'].choices = [(x.pk, x.name) for x in 
                                          Client.objects.all()]

    
