#!/usr/bin/perl -w
require 5.10.1;

#a eazy array sort example
@array = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
for (0..@array+0) {
	printf("%2d  ", $_);
}

print "\n";

sub my_sort {
	for ($i = 0;  $i < @_+0; $i++) {
		for ($j = $i+1;  $j < @_+0; $j++) {
			($_[$i], $_[$j]) = ($_[$j], $_[$i]) if ($_[$i] < $_[$j]);
		}
	}
}

my_sort (@array);
for(@array) {
	printf("%2d  ", $_);
}

=a

printf ("\nthree ways to get the length of the array\n");
$len = @array;
print "$len ";
$len = scalar(@array);
print "$len ";
$len = 0 + @array;
print "$len ";

print @array;

print "\n================\n";
print "a fib number exanple\n";
@fib = (1, 1);
for ($i = 0; $i <= 92; $i++) {
	$fib[$i+2] = $fib[$i+1] + $fib[$i];
	print $fib[$i] . "\n";
}

=cut
