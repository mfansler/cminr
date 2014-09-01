
from os import *
from pwd import *

username = getlogin ()
if (not username):
    uid = getuid ()
    userinfo = getpwuid (uid)
    username = userinfo[0]

print "username = " + userinfo[0]
