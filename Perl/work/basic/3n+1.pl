#!/usr/bin/perl -w
require 5.10.1;

# the 3n+1 problem in Perl
print "hi, I'm xatier\n";
print "this is a 3n+1 problem in Perl example!\n";
$start = (times)[0];
print("&x from 20 to 100...\n");
for $x (20..1000) {
	fun($x);
}
$end = (times)[0];
printf "that took %.2f CPU seconds\n", $end - $start;

sub fun {
	print '$_[0]' . " = $_[0], cycle length = ";
	$len = 0;
	while ($_[0] != 1) {
		if ($_[0] & 1) {
			$_[0] = $_[0]*3+1;
		}
		else {
			$_[0] /= 2;
		}
		$len++;
	}
	print $len, "\n";
}
