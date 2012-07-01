=head1 NAME

                                                         
     xscreen.pm - xatier's screen for Linux system Terminal based on Term::Screen by Mark Kaehny       
                                                         
     Date:                          01/30/2012               

                 
=head1 SYNOPSIS                                        


    use xscreen;

    $scr = xscreen->new();
    die " Something's wrong \n" unless ($scr);
    $scr->clrscr();      # clear the screen

    $scr->at(5, 3);      # move the curses to (5, 3)
    $scr->move(5, 3);    # the same with at()

    $scr->x();           # get/set x of the curses             y/x means row/col
    $scr->x(col);
    $scr->y();
    $scr->y(row);

    # you can also use like this:

    $scr->at(3, 10)->puts("Q__Q")->color('0wy')->move(5, 5)->puts("Q__Q")->color('0yb');

    .....

    to be writed ... XD

=head1 DESCRIPTION


    xscreen support colors!!!    


=head1 Methods


=over 3

=cut

package xscreen;
use strict;
use warnings;
use Term::Screen;

# constructor

sub new {
    my ($class, %cnf) = @_;

    my $self  = {};
    $self->{_x} = 0;
    $self->{_y} = 0;

    $self->{scr} = Term::Screen->new();
    die "can't create a new screen :$!" unless $self->{scr};
    $self->{scr}->noecho();
    $self->{scr}->clrscr();

    $self->{color} = "0wb";

    bless ($self, $class);
    return $self;

}

=item x(x)

    get/set x of the curses

=cut

sub x {
    my ($self, $x) = @_;
    $self->{_x} = $x if (defined $x and $x =~ /\d+/);
    return $self->{_x};
}

=item y(y)

    get/set y of the curses

=cut

sub y {
    my ($self, $y) = @_;
    $self->{_y} = $y if (defined $y and $y =~ /\d+/);
    return $self->{_y};
}

=item color (string)

    set color with string of '1yw' format

=cut

sub color {
    my ($self, $c) = @_;
    $self->{color} = $c if ($c =~ /[01][brgylpcw][brgylpcw]/);
    return $self;
}


=item puts (string)

    print a string on the screen

=cut

sub puts {
    my ($self, $str) = @_;
    $self->{scr}->puts(sprintf "\033[%sm%s\033[m", $self->_get_color_str(), $str);
    return $self;
}

# translate color formatted like '1yb' to the control string like '1;30;38'

sub _get_color_str {
    my $self = shift;
    my $str = "";
    my @c  = qw (b r g y l p c w);
    if (substr($self->{color}, 0, 1) eq '1') {
        $str .= "1;";
    }
    elsif (substr($self->{color}, 0, 1) eq '0') {
        $str .= "0;";
    }
    for (0 .. 7) {
        if (substr($self->{color}, 1, 1) eq $c[$_]) {
            $str .= sprintf("%d;", $_+30);
        }
    }
    for (0 .. 7) {
        if (substr($self->{color}, 2, 1) eq $c[$_]) {
            $str .= sprintf("%d", $_+40);
        }
    }
    return $str;
}

=item at(y, x)

    move the curses to (y, x)

=cut

sub at {
    my ($self , $y, $x) = @_;
    $self->{scr}->at($y, $x);
    $self->y($y);
    $self->x($x);
    return $self
}

=item move(y, x)

    behaves the same with at()

=cut

sub move {
    my ($self , $y, $x) = @_;
    $self->at($y, $x);
    return $self;
}

=item clrscr()

    cleen screen

=cut

sub clrscr {
    my $self = shift;
    $self->{scr}->clrscr();
    return $self;
}

=item scr()

    return a Term::Screen object so that you can use its methods

=cut

sub scr {
    my $self = shift;
    return $self->{scr};
}

=item bar($y, $x, $str)

    make a bar of text

=cut

sub bar {
    my ($self, $y, $x, $str) = @_;
    my $color_tmp = $self->{color};
    $self->at($y, $x)->color('1wl')->puts(" " . $str . " ");
    $self->{color} = $color_tmp;
    return $self;
}

=item box ($y, $x, $str)

    make a box of text like :

         +--------------------+
         | this is a box test |
         +--------------------+

=cut

sub box {
    my ($self, $y, $x, $str) = @_;

    $self->at($y-1, $x-1)->puts("+" . "-"x (length($str)+2) . "+");
    $self->at($y, $x-1)->puts("| " . $str . " |");
    $self->at($y+1, $x-1)->puts("+" . "-"x (length($str)+2) . "+");

    return $self;
}

=item eat_line ($y, $x, $len)
    
    return the string you input for max $len length

=cut

sub eat_line {
    my ($self, $y, $x, $len) = @_;
    my $color_tmp = $self->{color};
    my $get = "";
    $len++;
    $self->at($y, $x)->color('1wb')->puts(" "x$len);
    my $left = $len;
    $self->at($y, $x);

    while ($left > 0) {
        my $c = $self->{scr}->getch();
        if ((ord substr $c, 0, 1) == 127 && $left <= $len-1 ) {   # for Backspace
            $self->at($y, $x+$len-$left-1)->puts(" ")->at($y, $x+$len-$left-1);
            chop $get;                      # cut it off !
            $left++;
        }
        elsif ((ord substr $c, 0, 1) == 13) {              # for '\r' (Enter)
            $self->{color} = $color_tmp;
            return $get;
        }
        elsif ($left == 1) {
            redo;
        }
        else {
            $self->puts($c);
            $get .= $c;
            $left--;
        }
    }
}

1;

__END__

=back

=head1 AUTHOR

    xscreen.pm by xatier Lee  (xatierlike @gmail.com)

=head1 SEE ALSO

    Term::Screen
=cut

