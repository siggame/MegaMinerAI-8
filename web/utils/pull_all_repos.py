from WebServerInterface import WebServerInterface, NoSuchRepository
import git
import os


PWD = os.getcwd()

w = WebServerInterface("megaminerai.com")
list_of_logins = w.login_list()

for (team_id, login) in list_of_logins:
    try:
        repo_dict = w.get_ssh_path(login)
        clone_to = "%s/repos/%s"%(PWD, login,)
        path = repo_dict['path']
        print "Cloning %s's repository from %s to %s"%(login, 
                                                       path.split('/')[-3:],
                                                       clone_to.split('/')[-1],)
        r = git.Repo(path)
        r_new = r.clone(clone_to)
        r_new.git.checkout('master')
        r_new.git.checkout(repo_dict['commit_id'])
    except NoSuchRepository, e:
        print "%s doesn't have a repository!"%(login,)

print "Donesies! Cloned %d repositories to ./repos"%(len(list_of_logins),)
