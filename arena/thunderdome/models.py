#####
### Missouri S&T ACM SIG-Game Arena (Thunderdome)
#####

# Non-Django 3rd Party Imports
import beanstalkc
import time
import json

# Django Imports
from django.db import models


class Client(models.Model):
    ### A competitor in the arena
    name            = models.CharField(max_length=100)
    current_version = models.CharField(max_length=100, default='')
    embargoed       = models.BooleanField(default=False) # fail to compile?

    def __unicode__(self):
        return self.name

    
class Game(models.Model):
    ### A single match
    STATUS_CHOICES = \
        (('1', 'New'),
         ('2', 'Scheduled'),
         ('3', 'Running'),
         ('4', 'Complete'),
         ('0', 'Failed'))
    clients     = models.ManyToManyField(Client, through='GameData')
    status      = models.CharField(max_length=1, 
                                   choices=STATUS_CHOICES,
                                   default='1')
    priority    = models.IntegerField(default=1000)
    gamelog_url = models.CharField(max_length=200, default='')
    stats       = models.TextField(default='') # holds extra stuff via JSON

    def schedule(self):
        if self.status != '1':
            return False
        if self.pk == None:
            self.save()
        c = beanstalkc.Connection()
        c.use('game-requests')
        payload = json.dumps({'game_id'    : str(self.pk),
                              'entry_time' : str(time.time()) })
        c.put(payload, priority=self.priority)
        c.close()
        self.status=2
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
    stats      = models.TextField(default='') # holds extra stuff via JSON

    def __unicode__(self):
        return u"%s - %s" % (self.match.pk, self.client.name)
