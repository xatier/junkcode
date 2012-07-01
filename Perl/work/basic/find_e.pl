#!/usr/bin/perl
# this is a example th caculate 'e'
use Math::BigFloat;

$e = Math::BigFloat->new(0.0);
$a = Math::BigFloat->new(1);
$b = Math::BigFloat->new(1);

for (1 .. 100) {
  $b = $_ * $a;
  $e += 1/$a;
  $a = $b;
}

printf("%.50f\n", $e);
