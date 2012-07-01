#!/usr/bin/perl
use strict;
#use warnings;
use Term::Screen;
use Encode;

our %cur;
our @board;
our @dir = (
    [-1, -1], [-1, 0], [-1, 1],
    [ 0, -1],          [ 0, 1],
    [ 1, -1], [ 1, 0], [ 1, 1]
  );

our @map_val = ();
our $scr;

sub init {
  $scr = new Term::Screen;
  unless ($scr) { die " Something's wrong \n"; }
  $scr->noecho();
  $scr->clrscr();
  my ($y, $x) = (0, 0);


  open MAP, "gray_map";
  while (<MAP>) {
    $scr->at($y, $x);
    $scr->puts($_);
    $y++;
  }

  for my $i (0 .. 7) {
    for my $j (0 .. 7) {
        $board[$i][$j] = 0;
        $map_val[$i][$j] = sqrt(sqrt(($i-3.5)**2 + ($j-3.5)**2));
    }
  }
    
  $board[3][3] = $board[4][4]= 1;
  $board[3][4] = $board[4][3]= 2;

  update_map();

  $cur{y} = $cur{x} = 3;

  update_cur();

}

sub update_map {
  for my $i (0 .. 7) {
    for my $j (0 .. 7) {
        $scr->at(5+$i, 22+$j*2)->puts("\033[;33m█\033[m") if ($board[$i][$j] == 0);
        $scr->at(5+$i, 22+$j*2)->puts("\033[;36m○\033[m") if ($board[$i][$j] == 1);
        $scr->at(5+$i, 22+$j*2)->puts("\033[;36m●\033[m") if ($board[$i][$j] == 2);
        $scr->at(5+$i, 22+$j*2)->puts("QQ") if ($board[$i][$j] == 3);
    }
  }
  update_cur();
}

sub user {
  my $done = 0;
  return $done if ($board[$cur{y}][$cur{x}] != 0);


  for my $i (0 .. 7) {
    my ($y, $x) = ($cur{y}, $cur{x});
    my ($eat, $ly, $lx) = (0, -1, -1);

    $y += $dir[$i][0];
    $x += $dir[$i][1];


    while (1) {
      if (!(0 <= $y && $y <= 7 && 0 <= $x && $x <= 7)) {
        $eat = 0;
        last;
      }
      if ($board[$y][$x] == 2) {
        $y += $dir[$i][0];
        $x += $dir[$i][1];
        $eat++;
      }
      elsif ($board[$y][$x] == 1) {
        ($ly, $lx) = ($y, $x);
        last;
      }
      else {
        $eat = 0;
        last;
      }
    }

    ($y, $x) = ($cur{y}, $cur{x});

    if ($eat > 0) {
      $board[$cur{y}][$cur{x}] = 1;
      while ($eat--) {
        $y += $dir[$i][0];
        $x += $dir[$i][1];
        $board[$y][$x] = 1;
        last if ($y == $ly && $x == $lx);
      }
      $done = 1;
    }
  }
  return $done;
}


sub comp {

  my @steps = ();

  for my $cy (0 .. 7) {
    for my $cx (0 .. 7) {
      next if ($board[$cy][$cx] != 0);
      
      for my $i (0 .. 7) {
        my ($y, $x) = ($cy, $cx);
        my ($eat, $ly, $lx) = (0, -1, -1);

        $y += $dir[$i][0];
        $x += $dir[$i][1];

        while (1) {
          if (!(0 <= $y && $y <= 7 && 0 <= $x && $x <= 7)) {
            $eat = 0;
            last;
          }
          if ($board[$y][$x] == 1) {
            $y += $dir[$i][0];
            $x += $dir[$i][1];
            $eat++;
          }
          elsif ($board[$y][$x] == 2) {
            ($ly, $lx) = ($y, $x);
            last;
          }
          else {
            $eat = 0;
            last;
          }
        }
        $steps[$cy*8+$cx] += $eat;
      }
    }
  }

  my %best;
  ($best{val}, $best{y}, $best{x}) = (0, -1, -1);
  for (0 .. 63) {
    if ($steps[$_]*$map_val[$_/8][$_%8] > $best{val}) {
      ($best{val}, $best{y}, $best{x}) = ($steps[$_]*$map_val[$_/8][$_%8], $_/8, $_%8);
    }
  }

  if ($best{y} == -1 || $best{x} == -1) {
    return;
  }

  ($cur{y}, $cur{x}) = ($best{y}, $best{x});

  for my $i (0 .. 7) {
    my ($y, $x) = ($cur{y}, $cur{x});
    my ($eat, $ly, $lx) = (0, -1, -1);

    $y += $dir[$i][0];
    $x += $dir[$i][1];

    while (1) {
      if (!(0 <= $y && $y <= 7 && 0 <= $x && $x <= 7)) {
        $eat = 0;
        last;
      }
      if ($board[$y][$x] == 1) {
        $y += $dir[$i][0];
        $x += $dir[$i][1];
        $eat++;
      }
      elsif ($board[$y][$x] == 2) {
        ($ly, $lx) = ($y, $x);
        last;
      }
      else {
        $eat = 0;
        last;
      }
    }

    ($y, $x) = ($cur{y}, $cur{x});

    if ($eat > 0) {
      $board[$cur{y}][$cur{x}] = 2;
      while ($eat--) {
        $y += $dir[$i][0];
        $x += $dir[$i][1];
        $board[$y][$x] = 2;
        last if ($y == $ly && $x == $lx);
      }
    }
  }
}

sub update_cur {
  $scr->at(5 + $cur{y}, 22 + $cur{x}*2);
}

init();
while (my $key = $scr->getch()) {
  last if ($key eq 'q');
  $cur{y} = $cur{y}-- <=  0? 7: $cur{y} if ($key eq 'ku');
  $cur{y} = $cur{y}++ >=  7? 0: $cur{y} if ($key eq 'kd');
  $cur{x} = $cur{x}-- <=  0? 7: $cur{x} if ($key eq 'kl');
  $cur{x} = $cur{x}++ >=  7? 0: $cur{x} if ($key eq 'kr');

  $board[$cur{y}][$cur{x}] = 0 if ($key eq 'x');
  $board[$cur{y}][$cur{x}] = 1 if ($key eq 'c');
  $board[$cur{y}][$cur{x}] = 2 if ($key eq 'v');

  if ($key eq ' ') {
    my $d = user();
   if (!(0 <= $cur{y} && $cur{y} <= 7)) {
      printf("|___|: $cur{y}\n");
    }
    update_cur();
    update_map();

    sleep 1;
    comp() if ($d);
    if (!(0 <= $cur{y} && $cur{y} <= 7)) {
      printf("Q___Q: $cur{y}\n");
    }
  }

  update_cur();
  update_map();
}

$scr->at(24, 0)->puts("wave~\n");
