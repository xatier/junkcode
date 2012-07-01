#!/usr/bin/perl

our @talbe = ();

sub gen {
    @tmp = ();
    $N = 1000000;
    $tmp[$_] = 1 for (0 .. $N);

    for $i (2 .. $N) {
        if ($tmp[$i] == 1) {
            $tmp[$i*$_] = 0 for (2 .. $N/$i);
        }
    }
    for (2 .. $N) {
        push (@table, $_ ) if ($tmp[$_] == 1);
    }
    print "done\n";
}

gen();

print "$_, " for (@table);
