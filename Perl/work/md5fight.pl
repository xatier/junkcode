#!/usr/bin/perl
use 5.012;
use Digest::MD5;
use strict;
#use warnings;

while (<>) {
  my %A;
  my %B;
  say "Fight!";
  ($A{"name"}, $B{"name"}) = split;
  my $ker = Digest::MD5->new;
  $ker->add($A{name});
  $A{md5} = $ker->hexdigest;
  $ker->add($B{name});
  $B{md5} = $ker->hexdigest;
  $A{hp}  = hex(substr($A{md5},  0, 3)) % 150 + 200;
  $B{hp}  = hex(substr($B{md5},  0, 3)) % 150 + 200;
  $A{atk} = hex(substr($A{md5},  0, 3)) % 50 + 50;
  $B{atk} = hex(substr($B{md5},  0, 3)) % 50 + 50;
  $A{def} = hex(substr($A{md5},  3, 3)) % 50 + 50;
  $B{def} = hex(substr($B{md5},  3, 3)) % 50 + 50;
  $A{spd} = hex(substr($A{md5},  6, 3)) % 50 + 50;
  $B{spd} = hex(substr($B{md5},  6, 3)) % 50 + 50;

  statee(\%A, \%B);

  fight(\%A, \%B);
  say "[" . ($A{hp} > $B{hp} ? $B{name} : $A{name}) . "] 落敗";
}

sub statee {
  my ($a, $b) = @_;
  say "($a->{name}=> hp: $a->{hp}, atk: $a->{atk}, def: $a->{def}, spd: $a->{spd})";
  say "($b->{name}=> hp: $b->{hp}, atk: $b->{atk}, def: $b->{def}, spd: $b->{spd})";
}

# 0123456789ABCDEF
sub fight {
  my ($a, $b) = @_;
  my $ptr = 0;
  my $who = ($a->{hp} > $b->{hp});
  
  while ($a->{hp} > 0 && $b->{hp} > 0) {
    if ($who) {
      if (ord(substr($a->{md5}, $ptr, 1)) == ord('F')) {
        say "[$a->{name}] 爆氣了，所有數值變為兩倍！";
        $a->{hp}  *= 2;
        $a->{atk} *= 2;
        $a->{def} *= 2;
        $a->{spd} *= 2;
      }
      elsif (ord(substr($a->{md5}, $ptr, 1)) > ord('C')){
        say "[$a->{name}] 發動連擊 把 [$b->{name}] 壓在地上 >////<";
        while (ord(substr($a->{md5}, $ptr, 1)) >= ord('A')) {
          my $hit = abs($a->{atk} - $b->{def}) * hex(substr($a->{md5}, $ptr, 1));      
          $b->{hp} -= $hit;
          say "[$b->{name}] 受到 $hit 點傷害";
          sleep 1;
          $ptr++;
          $ptr %= 17;
        }
        goto ker;
      }
      print "[$a->{name}] 向 [$b->{name}] 攻擊 ";
      if (ord(substr($b->{md5}, $ptr, 1)) > ord(substr($a->{md5}, $ptr, 1)) && $b->{spd} > $a->{spd}) {
        say "但是被 [$b->{name}] 避開了";
        goto ker;
      }
      my $hit = abs($a->{atk} - $b->{def}) * hex(substr($a->{md5}, $ptr, 1));
      
      $b->{hp} -= $hit;
      say "[$b->{name}] 受到 $hit 點傷害";
    
    }
    else {
      if (ord(substr($b->{md5}, $ptr, 1)) == ord('F')) {
        say "[$b->{name}] 爆氣了，所有數值變為兩倍！";
        $b->{hp}  *= 2;
        $b->{atk} *= 2;
        $b->{def} *= 2;
        $b->{spd} *= 2;
      }
      elsif (ord(substr($b->{md5}, $ptr, 1)) > ord('C')){
        say "[$b->{name}] 發動連擊 把 [$a->{name}] 壓在地上 >////<";
        while (ord(substr($b->{md5}, $ptr, 1)) >= ord('A')) {
          my $hit = abs($b->{atk} - $a->{def}) * hex(substr($b->{md5}, $ptr, 1));      
          $a->{hp} -= $hit;
          say "[$a->{name}] 受到 $hit 點傷害";
          sleep 1;
          $ptr++;
          $ptr %= 17;
        }
        goto ker;
      }
      print "[$b->{name}] 向 [$a->{name}] 攻擊 ";
      my $hit = abs($b->{atk} - $a->{def}) * hex(substr($b->{md5}, $ptr, 1));
      if (ord(substr($a->{md5}, $ptr, 1)) > ord(substr($b->{md5}, $ptr, 1)) && $a->{spd} > $b->{spd}) {
        say "但是被 [$a->{name}] 避開了";
        goto ker;
      }
      $a->{hp} -= $hit;
      say "[$a->{name}] 受到 $hit 點傷害";
    }
    ker:
      $a->{hp} = 0 if ($a->{hp} < 0);
      $b->{hp} = 0 if ($b->{hp} < 0);
      say "$a->{name} HP:$a->{hp}        $b->{name} HP:$b->{hp}";
      sleep 1;
      $who ^= 1;
      $ptr++;
      $ptr %= 17;
  }
}
