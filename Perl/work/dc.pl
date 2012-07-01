#!/usr/bin/perl
my @t = localtime(time);
for my $i (reverse 0 .. 2) {
    for (reverse 0 .. 8) {
        print (($t[$i] >> $_ & 1) ? "●" : "  ");
    }
    print "\n";
}
