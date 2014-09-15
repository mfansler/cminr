#! /usr/bin/perl -w
    eval 'exec /usr/bin/perl -S $0 ${1+"$@"}'
        if 0; #$running_under_some_shell

use strict;
use File::Find ();

# Set the variable $File::Find::dont_use_nlink if you're using AFS,
# since AFS cheats.

# for the convenience of &wanted calls, including -eval statements:
use vars qw/*name *dir *prune/;
*name   = *File::Find::name;
*dir    = *File::Find::dir;
*prune  = *File::Find::prune;

sub wanted;
sub doexec ($@);


use Cwd ();
my $cwd = Cwd::cwd();


# Traverse desired filesystems
File::Find::find({wanted => \&wanted}, '.');
exit;


sub wanted {
    my ($dev,$ino,$mode,$nlink,$uid,$gid);

    /^.*\.o\z/s &&
    (($dev,$ino,$mode,$nlink,$uid,$gid) = lstat($_)) &&
    (int(-s _) > 5119) &&
    doexec(0, 'ls','-l','{}');
}


sub doexec ($@) {
    my $ok = shift;
    my @command = @_; # copy so we don't try to s/// aliases to constants
    for my $word (@command)
        { $word =~ s#{}#$name#g }
    if ($ok) {
        my $old = select(STDOUT);
        $| = 1;
        print "@command";
        select($old);
        return 0 unless <STDIN> =~ /^y/;
    }
    chdir $cwd; #sigh
    system @command;
    chdir $File::Find::dir;
    return !$?;
}

