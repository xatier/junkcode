#!/usr/bin/perl

use 5.014;

my $dir = $ARGV[0] // `pwd`;
chdir $dir;
say "start auto commit under: " . `pwd`;

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
