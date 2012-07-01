#!/usr/bin/perl
use 5.012;
for my $i (2 .. 6) {
  say(' 'x(6-$_).'*'x($_*2-1)) for ($i-2 .. $i);
}
