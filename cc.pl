#!/usr/bin/perl

use 5.014;

say `pwd`;
while (1) {
    my $diff = `git diff`;
    if ($diff) {
        my $t = time;
        `git add .`;
        `git commit -m "$t"`;
        `git push`;
    }
}
