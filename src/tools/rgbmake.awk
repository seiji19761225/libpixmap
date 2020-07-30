#
# Usage: awk -f rgbmake.awk < rgb.txt > rgb.html
# $Id: rgbmake.awk,v 1.1.1.1 2014/10/26 00:00:00 seiji Exp seiji $
#

BEGIN{
	print "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">"
	print "<HTML>"
	print "<HEAD><TITLE>rgb.txt color index</TITLE></HEAD>"
	print "<BODY BGCOLOR=\"#FFFFFF\" TEXT=\"#000000\">"
	print "<H1>Index of rgb.txt</H1>"
	print "<P>rgb.txt converted with <A HREF=\"rgbmake.awk\">rgbmake.awk</A>.</P>"
	print "<HR>"
	print "<TABLE>"
}

/^#/{next}
/^$/{next}
/^!/{next}
{
	hrgb = sprintf("#%02X%02X%02X",$1,$2,$3)
	coln = sprintf("%s%s%s%s",$4,$5,$6,$7)
	drgb = sprintf("%03d %03d %03d",$1,$2,$3)
	if( hrgb != ohrgb ){ print outtbl}

	outtbl = sprintf("<TR>\n\
	<TD BGCOLOR=\"%s\">%s</TD>\n\
	<TD BGCOLOR=\"%s\"><FONT COLOR=\"#ffffff\">%s</FONT></TD>\n\
	<TD><FONT COLOR=\"%s\">%s</FONT></TD>\n\
	<TD>%s</TD>\n\
	<TD>%s</TD>\n\
	<TD>%s</TD>\n</TR>",
	hrgb,hrgb,
	hrgb,drgb,
	hrgb,coln,
	hrgb,
	drgb,
	coln);
	ohrgb = hrgb
}

END{
	print outtbl
	print "</TABLE>"
	print "<HR>"
	print "</BODY>"
	print "</HTML>"

}
