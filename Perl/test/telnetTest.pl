#!/usr/bin/perl
use warnings;
use Net::Telnet;
use Encode;
$|++;
system("clear");
my $t = new Net::Telnet(Timeout => 100);
$t->open("bs2.to");
$t->waitfor(encode("Big5", decode("utf8", '/您的帳號/')));
$t->print("taugod");
$t->print("3.14159");
$t->print("");
my @ls = $t->getlines();
print for (@ls);

=a
my @a = ("f", "\033OA", "\033OA", "f", "q", "\n", "1", "\n");
for (0 .. 10) {
  for (0 .. 7) {
    $t->put($a[$_]);
    &getmap($t);
    $t->put('L' - 'A' + 1);
    sleep 1;
  }
}
=cut
$t->close;
print "Hellow~\n";


sub getmap {
  system("clear");
  my $t = shift;
  my $line = $t->getline();
  for (1 .. 6) {
    my $lines = $t->getline();
    $line = decode("Big5", $line);
    $line = encode("utf8", $line);
    print $line;
  }
  for (7 .. 24) {
    my $line = $t->getline();
  }
}
