#!/usr/bin/perl

########################################
# game of life 
#
# The Game of Life is not your typical computer game. 
# It is a 'cellular automaton', and was invented by Cambridge mathematician John Conway.
#
# The Rules
#
#   For a space that is 'populated':
#       Each cell with one or no neighbors dies, as if by loneliness.
#       Each cell with four or more neighbors dies, as if by overpopulation.
#       Each cell with two or three neighbors survives.
#   For a space that is 'empty' or 'unpopulated'
#       Each cell with three neighbors becomes populated.
# 
# Reference: http://www.bitstorm.org/gameoflife/
#
########################################

use xscreen;
use strict;

our $N = 25;                 # map length
our $xs = xscreen->new();

our @map = ();               # current state
our @nmap = ();              # the next state
our @dir = (                                                                                                                            
    [-1, -1], [-1, 0], [-1, 1],                                                                                                         
    [ 0, -1],          [ 0, 1],                                                                                                         
    [ 1, -1], [ 1, 0], [ 1, 1]                                                                                                          
  );

our $c = 0;                  # color

sub init {
    # init the map
    for my $i (1 .. $N) {
        for my $j (1 .. $N) {
            $map[$i][$j] = $nmap[$i][$j] = 0;
        }
    }
    $c = 0;
}


sub print_map {
    for my $i (1 .. $N) {
        for my $j (1 .. $N) {
            my $cc = sprintf("0%sb", substr("rgylpc", $c, 1));
            $xs->at($i, $j*2)->color($cc)->puts("O ")->color('0wb') if ($map[$i][$j] == 1);
            $xs->at($i, $j*2)->puts("\033[0;37;40m. \033[m") if ($map[$i][$j] == 0);
        }
    }
    $c++;
    $c %= 6;
}

sub update {
    for my $i (1 .. $N) {
        for my $j (1 .. $N) {
            $map[$i][$j] = $nmap[$i][$j];
        }
    }
}

# generate the next state
sub gen_next {
    for my $i (1 .. $N) {
        for my $j (1 .. $N) {
            # how many neibors do i have ?
            my $t = 0;
            for my $k (0 .. 7) {
                $t += $map[$i+$dir[$k][0]][$j+$dir[$k][1]];
            }
            # following the Rules above
            if ($map[$i][$j] == 1) {
                if ($t == 0 or $t == 1) {
                    $nmap[$i][$j] = 0;
                }
                elsif ($t >= 4)  {
                    $nmap[$i][$j] = 0;
                }
                elsif ($t == 2 or $t == 3) {
                    $nmap[$i][$j] = 1;
                }
            }
            elsif ($map[$i][$j] == 0) {
                if ($t == 3) {
                    $nmap[$i][$j] = 1;
                }
            }
        }
    }
}

# go go go!
sub go {
    while (1) {
        eval {
            gen_next();
            print_map();
            update();
            my $k = $xs->scr()->getch();
            last if ($k eq 'q');   # <q> for quit
            cmd() if ($k eq 'c');
            rnd() if ($k eq 'r');
            help() if ($k eq 'h');
        };
        if ($@) {
            print "QQ";
        }
    }
}

# command mode
sub cmd {
    my $str = $xs->at(26, 0)->puts("cmd # ")->eat_line(26, 6, 10);
    set () if ($str eq "set");
    init () if ($str eq "clear");
}

# random mode
sub rnd {
    my $T = 80;
    while ($T--) {
        $nmap[int rand$N][int rand $N] ^= 1;
    }
    update();
}

# print help message
sub help {
    $xs->box(5, 5, "[c]ommand mode");
    $xs->bar(7, 5, "    [ set ] the cells on the map       ");
    $xs->bar(8, 5, "    [clear] kill all cells on the map  ");
    $xs->box(11, 5, "[r]andom mode");
    $xs->bar(13, 5, "    randomly set the cells            ");
    $xs->scr()->getch();
}

# set the map yourself
sub set {
    $xs->at(26, 0)->puts("<space> to set cells     <q>uit");
    # move to the center of the map
    my $x = int $N / 2;
    my $y = int $N / 2;


    while (1) {
        $xs->at($y, $x*2);
        my $k = $xs->scr()->getch();
        last if ($k eq 'q');
        if ($k eq 'ku') {
            $y--;
            $y = 1 if ($y > $N);
            $y = $N if ($y < 1);
        }
        elsif ($k eq 'kd') {
            $y++;
            $y = 1 if ($y > $N);
            $y = $N if ($y < 1);
        }
        elsif ($k eq 'kr') {
            $x++;
            $x = 1 if ($x > $N);
            $x = $N if ($x < 1);
        }
        elsif ($k eq 'kl') {
            $x--;
            $x = 1 if ($x > $N);
            $x = $N if ($x < 1);
        }
        elsif ($k eq ' ') {
            $map[$y][$x] ^= 1;
            print_map();
            $xs->at($y, $x*2);
        }
    }
    $xs->at(26, 0)->puts("                                    ");
}


init();

# this a simple example
$map[3][2] = $map[1][3] = $map[3][3] = $map[2][4] = $map[3][4] = 1;


print "Press [q] for quit    [h] for help\n";
print_map();
go();

