#!/usr/bin/env perl
# #!/usr/bin/perl -w
# $Id: palette_ids.pl,v 1.1.1.2 2014/12/04 00:00:00 seiji Exp seiji $
# convert palette.h to generate color palette ID table
use POSIX;
use strict;
use warnings;
#-----------------------------------------------------------------------
my @palettes = ();
my $index    =  0;

&usage() if (@ARGV > 1);

# construct table of palette IDs from input file.
while (<>) {
    push(@palettes, $1)
	if (/^#define\s*(DS9_\w*)\s*\d*\s*$/ ||
	    /^#define\s*(IDL[12]_\w*)\s*\d*\s*$/);
}

# sort elements, and write out the results.
foreach (sort { lc $a cmp lc $b; } @palettes) {
    print ",\n" if ($index++ > 0);
    printf "\t{ %-30s, %-28s }", "\"$_\"", $_;
}

print "\n" if ($index > 0);
#-----------------------------------------------------------------------
sub usage()
{
    my    $cmd = `basename $0`;
    chomp $cmd;
    print STDERR "Usage:\t$cmd [palette.h]\n" .
		 "convert palette.h to generate color palette ID table.\n";
    exit;
}
