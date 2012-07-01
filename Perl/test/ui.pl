#!/usr/bin/perl
use strict;
use warnings;
use Term::Screen;
use xscreen;
=e
our $scr;

    $scr = Term::Screen->new();
    die "can't create a new screen :$!" unless $scr;
    $scr->echo();
    $scr->clrscr();

my $i = 30;
while ($i--) {
    my $c = $scr->getch();
    print "BS!! " if ((ord substr $c, 0, 1) == 127); 
    print " | " . $c ." | ";
}
=cut

#=e
my $ms = xscreen->new();
print "  " . $ms->y() . " ". $ms->x();
$ms->at(3, 10)->puts("Q__Q")->color('0wy')->move(5, 5)->puts("Q__Q")->color('0yb');
$ms->bar(8, 6, "this is a bar test");
$ms->box(12,10, "this is a box test");
my $ss = $ms->eat_line(15, 10, 10);
$ms->at(17, 0)->puts($ss);
print "  " . $ms->y() . " ". $ms->x();
#=cut
=d
my @c = qw (b r g y l p c w);
for my $i (0 .. 7) {
    for my $j (0 .. 7) {
        $ms->color(sprintf("1%s%s", $c[$j], $c[$i]))->puts('QQ');
    }
}
=cut
