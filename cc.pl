#!/usr/bin/perl

use 5.014;

say `pwd`;
my $dir = $ARGV[0] // `pwd`;
chdir $dir;
say `pwd`;
#=dd
while (1) {
    my $diff = `git diff`;
    if ($diff) {
        my $t = `date +"%F [%T]"`;
        `git add .`;
        `git commit -m "auto commit @ $t"`;
        `git push`;
    }
    sleep 10;
}
#=cut
