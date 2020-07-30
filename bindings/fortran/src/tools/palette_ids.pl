#!/usr/bin/env perl
# #!/usr/bin/perl -w
# $Id: palette_ids.pl,v 1.1.1.2 2014/12/04 00:00:00 seiji Exp seiji $
# convert palette.h to generate palette ID parameters for FORTRAN
use POSIX;
use strict;
use warnings;
#-----------------------------------------------------------------------
my %palettes = ();
my $index    =  0;

&usage() if (@ARGV > 1);

# construct palette ID hash table from input file.
while (<>) {
    $palettes{$1} = $2
	if (/^#define\s*(PALETTE_NTYPES)\s*(\d*)\s*$/ ||
	    /^#define\s*(IDL[12]_\w*)\s*(\d*)\s*$/    ||
	    /^#define\s*(DS9_\w*)\s*(\d*)\s*$/);
}

# write out the results.
print "     & ";

foreach (sort { $palettes{$a} <=> $palettes{$b}; } keys(%palettes)) {
    if ($index++ > 0) {
	print  ",";
	print  " &\n     & "
	    if ($index % 2 == 1);
    }
    printf "%-28s=%2d", $_, $palettes{$_};
}

print "\n";
#-----------------------------------------------------------------------
sub usage()
{
    my    $cmd = `basename $0`;
    chomp $cmd;
    print STDERR "Usage:\t$cmd [palette.h]\n" .
		 "convert palette.h to generate palette ID parameters for FORTRAN\n";
    exit;
}
