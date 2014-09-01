use strict;
use warnings;
use English;

my $login = getlogin ();
if (! $login)
{
    printf ("getlogin () failed\n");
    printf ("uid = %d\n", $UID);
    $login = getpwuid ($<);
}

printf ("login = %s\n", $login);
