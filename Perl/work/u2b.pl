#!/usr/bin/perl

################################################
# just another youtube search tool in cmd line #
#                                              #
#                                      xatier  #
################################################

use 5.014;
no warnings;
use WWW::Mechanize;
use Data::Dumper;
use Getopt::Std;

our $opt_n;
getopts('n:');

my $keywords = join("+", @ARGV);
my $limit = $opt_n // 6;

if ($keywords eq "") {
    say <<EOF;
    Usage:
        ./u2b.pl keywords
        ./u2b.pl -n 3 keywords

        default n = 6
EOF
    exit;
}


# new Mechanize
my $mech = WWW::Mechanize->new();

# youtube query URL
my $url = "http://www.youtube.com/results?hl=en&search_query=$keywords";
say "try to search for $limit results ...\n" . $url;

$mech->get( $url );

# http://www.youtube.com/watch?v=XXXXXXXXXXX
my $ref = $mech->find_all_links( url_regex => qr/watch\?v=/i );


# for all valid video links
my @playlist = ();
for (@$ref) {
    if ($_->[0] =~ /watch\?v=.{11}/ and $_->[1] =~ /Watch Later/) {
        push @playlist, $_->[0];
    }
    last if (@playlist == $limit);
}


if (@playlist > 0) {
    say "search results:";
    for (@playlist) {
        $mech->get ("http://www.youtube.com$_");
        say $mech->title();
        say "http://www.youtube.com$_\n";
    }
}
=cut
