#####
### Missouri S&T ACM SIG-Game Arena (Thunderdome)
#####

from django.conf.urls.defaults import patterns, url

urlpatterns = patterns('thunderdome.views',
    url(r'^$','index'),
    url(r'^inject$', 'inject'),
    url(r'^view/(?P<game_id>\d+)$', 'view_game'),
    url(r'^scoreboard$', 'scoreboard'),
    url(r'^view_client/(?P<client_id>\d+)$', 'view_client'),
)
