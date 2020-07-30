#!/usr/bin/env perl
# #!/usr/bin/perl -w
# $Id: window_consts.pl,v 1.1.1.1 2014/10/26 00:00:00 seiji Exp seiji $
# convert window.h to generate constant parameter list for FORTRAN
use POSIX;
use strict;
use warnings;
#-----------------------------------------------------------------------
my %device_ids  = ();
my %key_codes   = ();
my %mouse_codes = ();
my $index       =  0;

&usage() if (@ARGV > 1);

# construct hash tables from input file.
while (<>) {
    $device_ids {$1} = hex($2)
	if (/^#define\s*(WD_\w*)\s*(0x[0-9,a-f,A-F]*)/);
    $key_codes  {$1} = hex($2)
	if (/^#define\s*(WK_\w*)\s*(0x[0-9,a-f,A-F]*)/);
    $mouse_codes{$1} = hex($2)
	if (/^#define\s*(WM_\w*)\s*(0x[0-9,a-f,A-F]*)/);
}

# write out the results.
print "     & ";

foreach (sort { $device_ids {$a} <=> $device_ids {$b}; } keys(%device_ids )) {
    if ($index++ > 0) {
	print  ",";
	print  "  &\n     & "
	    if ($index % 3 == 1);
    }
    printf "%-16s=%3d", $_, $device_ids {$_};
}

foreach (sort { $key_codes  {$a} <=> $key_codes  {$b}; } keys(%key_codes  )) {
    if ($index++ > 0) {
	print  ",";
	print  "  &\n     & "
	    if ($index % 3 == 1);
    }
    printf "%-16s=%3d", $_, $key_codes  {$_};
}

foreach (sort { $mouse_codes{$a} <=> $mouse_codes{$b}; } keys(%mouse_codes)) {
    if ($index++ > 0) {
	print  ",";
	print  "  &\n     & "
	    if ($index % 3 == 1);
    }
    printf "%-16s=%3d", $_, $mouse_codes{$_};
}

print "\n";
#-----------------------------------------------------------------------
sub usage()
{
    my    $cmd = `basename $0`;
    chomp $cmd;
    print STDERR "Usage:\t$cmd [window.h]\n" .
		 "convert window.h to generate constant parameter list for FORTRAN\n";
    exit;
}
