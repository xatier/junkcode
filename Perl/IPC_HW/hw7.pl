#!/usr/bin/perl

our @stack;

sub show {
    return if ($_[0] == 0);
    show ($_[0] - 1);
    print "$stack[$_[0]-1] ";
}

sub qqq {
    my ($n, $k) = @_;
    if ($n < 0 || $k == 0) {
        return 0;
    }
    elsif ($n == 0) {
        show($#stack + 1);
        print "\n";
        return 1;
    }
    else {
        push @stack, $k;
        my $a = qqq($n-$k, $k);
        pop @stack;
        return $a + qqq($n, $k-1);
    }
}

sub ui {
    print "Enter a positive integer <= 20: ";
    if (defined ($_ = <>)) {
        chomp;
        printf ("There are %d ways to partition %d.\n", qqq($_, $_), $_);
        ui();
    }
    return;
}

ui();
