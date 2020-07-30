#!/usr/bin/env perl
# #!/usr/bin/perl -w
# $Id: named_colors.pl,v 1.1.1.1 2014/10/26 00:00:00 seiji Exp seiji $
# color name database converter
use POSIX;
use strict;
use warnings;
# use integer;
#-----------------------------------------------------------------------
my %colors = ();
my $index  =  0;

&usage() if (@ARGV > 1);

# construct color name hash table from the input file.
while (<>) {
    $colors{$4} = [ $1, $2, $3 ]
	if (/^\s*(\d+)\s+(\d+)\s+(\d+)\s+(\w.*)\s*$/);
}

# sort hash elements by name, and write out the results.
foreach (sort { $a cmp $b; } keys(%colors)) {
    print ",\n" if ($index++ > 0);
    printf "\t{ %-24s, 0x%02x, 0x%02x, 0x%02x }",
	"\"$_\"", $colors{$_}[0], $colors{$_}[1], $colors{$_}[2];
}

print "\n" if ($index > 0);
#-----------------------------------------------------------------------
sub usage()
{
    my    $cmd = `basename $0`;
    chomp $cmd;
    print STDERR "Usage:\t$cmd [rgb.txt]\n" .
		 "color name database converter\n";
    exit;
}
