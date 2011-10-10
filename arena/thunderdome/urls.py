#####
### Missouri S&T ACM SIG-Game Arena (Thunderdome)
#####

from django.conf.urls.defaults import *

urlpatterns = patterns('mysite.thunderdome.views',
    (r'^$','index'),
)
