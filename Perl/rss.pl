#!/usr/bin/perl -CDS

use 5.014;

use XML::Feed;
use WWW::Shorten::TinyURL;

# max articles number each feed
use constant THRESHOLD => 5;

# RSS feed urls
my @urls = (
    "http://feeds2.feedburner.com/solidot",
    "http://www.36kr.com/feed",
    "http://pansci.tw/feed",
    "http://blog.gslin.org/feed",
    "https://www.linux.com/rss/feeds.php",
    "http://www.linuxplanet.org/blogs/?feed=rss2",
    "http://perlsphere.net/atom.xml",
    "http://planet.linux.org.tw/atom.xml",
    "http://security-sh3ll.blogspot.com/feeds/posts/default",
    "http://feeds.feedburner.com/TheGeekStuff",
    "http://coolshell.cn/feed",
);

# force to print
$|++;
my $done = 0;
my @data = ();
for my $url (@urls) {
    say "fetching ..." . (sprintf "%2d", int ($done/@urls * 100)) . "%";

    # get RSS Feed via URI
    my $feed = XML::Feed->parse(URI->new($url)) or die XML::Feed->errstr;

    my $count = 0;
    for my $entry ($feed->entries) {
        push @data, [$feed->title, $entry->title, $entry->link];
        $count++;
        last if ($count >= THRESHOLD);
    }
    $done++;
}

say "done!";

for (@data) {
    say "$_->[0] | $_->[1]\n$_->[2]";
    my $short =  makeashorterlink($_->[2]);
    say $short;
    say "============================================";
}
