#!/usr/bin/perl

use integer;

sub sum1 {
    $n = shift;
    ($sum, $sign) = ($n, 1);
    @S = ('+', '-');
    print "$n";
    $n /= 10;
    while ($n > 0) {
      print "$S[$sign]$n";
      $sum += $n*(-1)**$sign;
      $sign = 1 - $sign;
      $n /= 10;
    }
    print " = $sum\n";
}

sub sum2 {
    $n = shift;
    ($l, $sum) = (length($n) - 1, 0);
    for (reverse 0 .. $l) {
        $sum += ($n / (10**$_));
        print $n / (10**$_) . "+";
    }
    print "\b = $sum\n";
}

sub sum3 {
    $n = shift;
    ($l, $sum) = (length($n), 0);
    for (1 .. $l) {
        $sum += ($n % (10**$_));
        printf "%0*d+", $_, $n % (10**$_);
    }
    print "\b = $sum\n\n";
}

print "Enter an integer >=0: ";
while (chomp($_ = <>)) {
    sum1($_);
    sum2($_);
    sum3($_);
    print "Enter an integer >=0: ";
}
