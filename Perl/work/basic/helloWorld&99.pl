#!/usr/bin/perl -w
require 5.010;
use 5.010;
print "Hello world~~\n";
say "Hello world";
=asdf
for ($i = 2; $i < 10; $i++) {
	for ($j = 1; $j < 10; $j++) {
		$str = "$i * $j = " . $i*$j . " ";
		print $str;
		if (($j%3) == 0) {
			print "\n";
		}
	}
	print ("\n");
}
=cut

print qq++,qq--,qq**,qq//,qq&&,qq||,qq!!,qq^^,qq@@;

