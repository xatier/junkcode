#!/usr/bin/perl

sub judge {
    return 0 if $_[0] eq '+' || $_[0] eq '-';
    return 1 if $_[0] eq '.';
    return 2 if ord '0' <= ord $_[0] && ord $_[0] <= ord '9';
    return 3 if $_[0] eq '\n';
}

sub f {
    $n = shift;
    $q = 's';
    for (0 .. length($n) - 1) {
        $j = judge(substr($n, $_, 1));
        if ($q eq 's') {
            $q = ($j == 0 ? 's' : $j == 1 ? 'f' : $j == 2 ? 'd' : 'e');
        }
        elsif ($q eq 'd') {
            $q = ($j == 2 ? 'd' : $j == 1 ? 'r' : 'e');
        }
        elsif ($q eq 'f') {
            $q = ($j == 2 ? 'r' : 'e');
        }
        elsif ($q eq 'r') {
            $q = ($j == 2 ? 'r' : 'e');
        }
    }
    return $q eq 'r';
}

print "Enter a real constant:";
while (chomp($_ = <>)) {
    print f($_) ? "Accepted\n" : "Rejected\n";
    print "Enter a real constant:";
}
