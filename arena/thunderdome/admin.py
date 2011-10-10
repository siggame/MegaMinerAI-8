#####
### Missouri S&T ACM SIG-Game Arena (Thunderdome)
#####

from mysite.thunderdome.models import *
from django.contrib import admin

admin.site.register(Competitor)
admin.site.register(Match)
admin.site.register(MatchData)
