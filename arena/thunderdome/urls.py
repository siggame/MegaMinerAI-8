#####
### Missouri S&T ACM SIG-Game Arena (Thunderdome)
#####

from django.conf.urls.defaults import patterns, url

urlpatterns = patterns('thunderdome.views',
    url(r'^$','scoreboard'),
    url(r'^inject$', 'inject'),
    url(r'^view/(?P<game_id>\d+)$', 'view_game'),
    
    url(r'^get_next_game_url_to_visualize$', 'get_next_game_url_to_visualize'),
    url(r'^game_visualized/(?P<game_id>\d+)$', 'game_visualized'),
                    
    url(r'^health$', 'health'),
    url(r'^view_client/(?P<client_id>\d+)$', 'view_client'),
    url(r'^view_match/(?P<match_id>\d+)$', 'view_match'),
    url(r'^matchup/(?P<client1_id>\d+)vs(?P<client2_id>\d+)$', 'matchup'),
)
