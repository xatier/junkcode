#!/usr/bin/perl

use integer;

sub gen {
  $n = shift;
  ($x0, $x1, $y0, $y1, $count) = (0, 1, 1, $n, 2);
  ($x2, $y2) = ((($y0 + $n) / $y1 * $x1 - $x0), (($y0 + $n) / $y1 * $y1 - $y0));
  print "$x0/$y0 $x1/$y1 ";

  while ($x1 != $y1) {
    ($x0, $y0) = ($x1, $y1);
    ($x1, $y1) = ($x2, $y2);
    ($x2, $y2) = ((($y0 + $n) / $y1 * $x1 - $x0), (($y0 + $n) / $y1 * $y1 - $y0));
    print "$x1/$y1 ";
    $count++;
  }
  print "\nThe Farey sequence of order $n has $count terms.\n\n";
}


print "Enter an integer >= 1:";
while (<>) {
  chomp;
  gen($_);
  print "Enter an integer >= 1:";
}
