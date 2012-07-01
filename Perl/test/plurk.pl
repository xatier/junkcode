#!/usr/bin/perl

use HTTP::Daemon;
use HTTP::Status;
use Data::Dumper;
use LWP::Simple;
use 5.012;

my $httpdamon = new HTTP::Daemon;
say "Please contact me at: <URL:", $httpdamon->url, ">";
while (my ($c, $addr) = $httpdamon->accept) {
    $addr = join "." ,unpack("C*", $addr);
    say "connect: $addr";
    $c->send_file_response("/home/xatierlike/programming/Perl/test/index.html");
    my $r = $c->get_request;
    my ($token, $page, $pr_page, $cookie);
    if ($r->method eq 'POST') {
        say Dumper $r;
        # '_content' => 'form_tocken=adsf&page=zxvc&pr_page=qwre&run=%E6%8F%90%E4%BA%A4',
        say $r->{_content};

        if ($r->{_content} =~ /form_token=(.+?)&page=(\d+?)&pr_page=(\d+)&cookie=(.+?)&/) {
            ($token, $page, $pr_page, $cookie) = ($1, $2, $3, $4);
        }
        say "($token, $page, $pr_page, $cookie)";
    }
    say "done!";

    use LWP::Simple::Cookies(file => $cookie);

    ($page, $pr_page) = (1, 15);
    my $json = get("http://www.plurk.com/EmoticonDiscovery/getHot?form_token=$token&page=$page&pr_page=$pr_page");
    $json = get("http://www.plurk.com/EmoticonDiscovery/getHot?form_token=fe8ae24aa8f955fbeaab0775baa794ec&page=15&pr_page=10");
    say $json;
    $c->close;
    say "closed";
    undef $c;
}
undef $httpdamon;
