#!/usr/bin/perl
# this is a example to caculate 'pi'
use Math::BigFloat;

$pi = Math::BigFloat->new(0.0);

for (0 .. 100000) {
  $a = 4.0*(1/(2*$_+1));
  if ($_ & 1) {
    $pi -= $a;
  }
  else {
    $pi += $a;
  }
}

printf("%.50f\n", $pi);
