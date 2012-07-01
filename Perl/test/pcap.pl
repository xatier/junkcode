#!/usr/bin/perl

use 5.012;

use Net::PcapUtils;
use NetPacket::Ethernet qw(:strip);
use NetPacket::IP qw(IP_PROTO_TCP);
use NetPacket::TCP;
use Data::HexDump;


sub process_pkt {
    my ($user_data,$header, $packet) = @_;
    # decode the Ethernet and IP headers
    my $ip = NetPacket::IP->decode(eth_strip($packet));
   
    if ($ip->{proto} == IP_PROTO_TCP) { 
        # decode TCP headers
        my $tcp = NetPacket::TCP->decode($ip);
        # now we get TCP packet XD
        say "\n$ip->{src_ip}($tcp->{src_port}) -> $ip->{dest_ip}($tcp->{dest_port})";
        say HexDump $ip->{data};
    }
}

my $filter = join(" ", @ARGV);
say $filter;
Net::PcapUtils::loop(\&process_pkt, SNAPLEN=> 65536, FILTER => $filter);
