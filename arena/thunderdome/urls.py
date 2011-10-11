#####
### Missouri S&T ACM SIG-Game Arena (Thunderdome)
#####

from django.conf.urls.defaults import patterns, url

urlpatterns = patterns('thunderdome.views',
    url(r'^$','index'),
)
