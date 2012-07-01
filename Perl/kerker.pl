#!/usr/bin/perl
use 5.010;

@a = ( 1 .. 10);
say join " ",  map {$_**2} @a;
