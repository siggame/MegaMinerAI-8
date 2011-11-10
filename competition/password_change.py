from twill.commands import go, fv, submit, get_browser

def change_password(name, old, new):
    go('https://password.mst.edu/cgi-bin/cgiwrap/pwchanger/changer.pl')
    fv('2', 'userid', name)
    submit()

    fv('2', 'oldpw', old)
    submit()

    fv('2', 'pw', new)
    fv('2', 'pw_verify', new)
    fv('2', 'agreeaup', 'on')
    fv('2', 'agreegoogleaup', 'on')
    submit()

    return '<B>Password change completed.</B>' in get_browser().get_html()
