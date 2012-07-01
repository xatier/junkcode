#!/usr/bin/perl

sub good {
    $n = shift;
    $l = length($n) - 2;
    @L = ();
    push @L, $n if ($l <= 0);
    for (0 .. $l - 1) {
        push @L, substr($n, $_, 3);
    }

    @L = sort @L;

    for (1 .. $#L) {
        return 0 if ($L[$_] == $L[$_-1]);
    }
    return 1;
}

sub bad {
    return $_[0] =~ /1/ && $_[0] =~ /3/ && $_[0] =~ /5/;
}

sub ugly {
    $n = shift;
    $n /= 2 while $n % 2 == 0;
    $n /= 3 while $n % 3 == 0;
    $n /= 5 while $n % 5 == 0;
    return $n == 1
}

print "Enter an unsigned integer >= 1: ";
while (chomp($_ = <>)) {
    print good($_) ? "Good, " : "Not good, ";
    print bad($_)  ? "Bad, "  : "Not bad, ";
    print ugly($_)  ? "Ugly"  : "Not ugly", "\n";
    print "Enter an unsigned integer >= 1: ";
}
