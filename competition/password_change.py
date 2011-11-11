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
    
if __name__ == "__main__":
    ### Expects the first argument to be the info file, and the second to be the default password ###
    import sys
    with open(sys.argv[1], 'r') as f:
        accounts = [line.split() for line in f.read().strip().split('\n')]
    for account in accounts:
        # Get the username and passwords for each account
        try:
            username, oldPassword, newPassword = account
        except ValueError:
            username, newPassword = account
            oldPassword = sys.argv[2]
        print username, oldPassword, newPassword
        try:
            change_password(username, oldPassword, newPassword)
        except Exception as e:
            print "Exception while changing password for: ", username, "=", e

