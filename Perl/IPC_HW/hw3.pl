#!/usr/bin/perl

our @table = ();

sub gen {
    @tmp = ();
    $N = 1000000;
    $tmp[$_] = 1 for (1 .. $N);

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

sub factorization {
    $n = shift;
    print "Prime factorization of $n = ";
    ($i, $N, $S) = (0, 1, 1);
    while ($n > 1) {
        $p = $table[$i];
        $e = 0;
        while ($n % $p == 0) {
            $e++;
            $n /= $p;
        }
        if ($e > 0) {
            print "pow($p,$e)";
            $N *= $e + 1;
            $ss = 0;
            $ss += $p**$_ for (0 .. $e);
            $S *= $ss;
        }
        $i++;
    }
    print "\nNumber of divisors = $N\nSum of divisors = $S\n\n";
}

gen();
print "Enter an integer >= 2: ";
while (chomp($_ = <>)) {
    factorization($_);
    print "Enter an integer >= 2: ";
}
