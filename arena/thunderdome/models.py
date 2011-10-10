#####
### Missouri S&T ACM SIG-Game Arena (Thunderdome)
#####

from django.db import models
from django.core.exceptions import ValidationError

import beanstalkc


class Competitor(models.Model):
    ### A competitor in the arena
    name            = models.CharField(max_length=100)
    current_version = models.CharField(max_length=100, default='')
    embargoed       = models.BooleanField(default=False) # fail to compile?

    def __unicode__(self):
        return self.name

class Match(models.Model):
    ### A single match
    STATUS_CHOICES = \
        (('1', 'New'),
         ('2', 'Scheduled'),
         ('3', 'Running'),
         ('4', 'Complete'),
         ('0', 'Failed'))
    competitors = models.ManyToManyField(Competitor, through='MatchData')
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
        c.use('match-requests')
        c.put(str(self.pk), priority=self.priority)
        c.close()
        self.status=2
        self.save()
        return True

    def __unicode__(self):
        return unicode(self.pk)


class MatchData(models.Model):
    ### each Match will have one of these for each competitor in that match
    match      = models.ForeignKey(Match)
    competitor = models.ForeignKey(Competitor)
    version    = models.CharField(max_length=100)
    compiled   = models.NullBooleanField()
    won        = models.NullBooleanField()
    stats      = models.TextField(default='') # holds extra stuff via JSON

    def __unicode__(self):
        return u"%s - %s" % (self.match.pk, self.competitor.name)
