#!/usr/bin/env perl
# #!/usr/bin/perl -w
# $Id: arrow_heads.pl,v 1.1.1.1 2014/10/26 00:00:00 seiji Exp seiji $
# convert pixmap.h to generate arrow head parameters for FORTRAN
use POSIX;
use strict;
use warnings;
#-----------------------------------------------------------------------
my %arrow_heads = ();
my $index       =  0;

&usage() if (@ARGV > 1);

# construct arrow head hash table from input file.
while (<>) {
    $arrow_heads{$1} = hex($2)
	if (/^#define\s*(AH_\w*)\s*(0x\d*)\s*$/);
}

# write out the results.
print "     & ";

foreach (sort { $arrow_heads{$a} <=> $arrow_heads{$b}; } keys(%arrow_heads)) {
    if ($index++ > 0) {
	print  ",";
	print  "                 &\n     & "
	    if ($index % 4 == 1);
    }
    printf "%-8s=%2d", $_, $arrow_heads{$_};
}

print "\n";
#-----------------------------------------------------------------------
sub usage()
{
    my    $cmd = `basename $0`;
    chomp $cmd;
    print STDERR "Usage:\t$cmd [pixmap.h]\n" .
		 "convert pixmap.h to generate arrow head parameters for FORTRAN\n";
    exit;
}
