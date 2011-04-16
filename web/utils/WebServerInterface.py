# 
# WebServerAuthenticator
# 
# Use this class to verify that a team's login/password combo
# is valid. It's for the arena
# 
from hashlib import sha1
import httplib
import urllib
import json

class WebServerException(Exception):
    def __init__(self, message):
        self.message = str(message)
    def __str__(self):
        return self.message

class NoSuchLogin(WebServerException):
    pass

class NoSuchRepository(WebServerException):
    pass

class WebServerInterface(object):
    INTERFACE_SALT = "PiNeApPlE TuEsDay?"
    
    def __init__(self, web_server_url):
        """
        Params:
        web_server_url - the url of the siggame webserver
        """
        self.url = web_server_url

    def _query_web_server(self, method, param_dict, http_method='GET'):
        # Make a connection to the specified URL
        conn = httplib.HTTPConnection(self.url)
        # Create a GET query string and send it...
        params = urllib.urlencode(param_dict)
        try:
            conn.request(http_method, "/api/%s?%s"%(method, params,))
        except:
            m = "Couldn't connect to server at %s" % (self.url,)
            raise WebServerException(m)
        # Grab the response
        response = conn.getresponse() 
        if response.status != 200:
            # Error if it's not an "HTTP 200 OK" response
            m = "Webserver Error: HTTP %d %s" % (response.status,
                                                 response.reason)
            raise WebServerException(m)
        r = json.loads(response.read())
        # Get the data out and check the responses.
        conn.close()
        return r
    
    def auth_team(self, login, passwd):
        """
        login - the team's login
        passwd - the team's password
        """
        data = self._query_web_server('auth_team', 
                                      {'login': login, 'passwd': passwd})
        if data['error']:
            print "WebServerAuthenticator error:",data['error']
            return False
        else:
            return data['authenticated']

    def login_list(self):
        return self._query_web_server('login_list', {})

    def get_ssh_path(self, login):
        """
        login - the team's login
        Error:
          Success - returns a dict {'path', 'commit_id', 'version'}
          BadLogin - throws NoSuchLogin (inherits from WebServerException)
          NoRepo - throws NoSuchRepository (inherits from WebServerException)
          Other Error - throws WebServerException
        """
        data = self._query_web_server('repo_query', {'login': login})
        if data['error']:
            if data['error'] == 'no_such_login':
                raise NoSuchLogin(data['error'])
            elif data['error'] == 'no_repository':
                raise NoSuchRepository(data['error'])
            else:
                raise WebServerException(data['error'])
        else:
            path = '%s/%s/%s'%(data['path'], data['id'], data['repo'],)
            return {'path': path,
                    'commit_id': data['commit_id'],
                    'version':data['version']}

    def set_game_stat(self, p1_name, p2_name, p1_score, p2_score,
                      p1_version, p2_version, log_name):
        """
        p*_name - string
        p*_score - int
        p*_version - string
        log_name - string
        Error:
          returns True if it worked, False if it didn't
        """
        info = {'player_1': p1_name, 'player_2':p2_name, 
                'player_1_score':p1_score, 'player_2_score': p2_score,
                'player_1_tag':p1_version, 'player_2_tag': p2_version, 
                'log_name': log_name}
        message = json.dumps(info)
        h = sha1(message+self.INTERFACE_SALT).hexdigest()
        data = self._query_web_server('game_stat', {'message': message, 'verify': h})
        if data['error']:
            return False
        else:
            return True

    
if __name__ == '__main__':
    w = WebServerInterface('megaminerai.com')
    try:
        print w.auth_team('Shell AI', 'password')
        webs = w.get_ssh_path('Shell AI')
        from os.path import split
        print split(webs['path'])[0][:-4]
    except NoSuchRepository, e:
        print e
    except NoSuchLogin, e:
        print e

    try:
        print w.get_ssh_path('Shell AI')
    except NoSuchLogin, e:
        print e

    print w.login_list()
    w.set_game_stat("coollogin", "derp", 10, 20,
                      "V0.1", "v1.0", "loggy")
