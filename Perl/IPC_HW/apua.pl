#!/usr/bin/perl

our %mem = {};
use bigint;
use strict;

sub qqq {
    my ($n, $k) = @_;
    if ($n < 0 || $k == 0) {
        return 0;
    }
    elsif ($n == 0) {
        return 1;
    }
    else {
        my ($v, $a, $b);
        $v = $n - $k;
        if (exists $mem{"$v,$k"}) {
            $a = $mem{"$v,$k"};
        }
        else {
            $a = qqq($v, $k);
            $mem{"$v,$k"} = $a;
        }
        $v = $k - 1;
        if (exists $mem{"$n,$v"}) {
            $b = $mem{"$n,$v"};
        }
        else {
            $b = qqq($n, $v);
            $mem{"$n,$v"} = $b;
        }
        return $a + $b;
    }
}

sub P {
    qqq($_[0], $_[0]);
}

print P(50) . "\n";
