.\" $Id: palette_intro.l,v 1.1.1.4 2015/01/14 00:00:00 seiji Exp seiji $
.TH palette_intro l

.SH NAME
.B palette
\- color palette module for libpixmap.

.SH SYNTAX
#include <libpixmap/palette.h>

.SH DESCRIPTION
This module provides color palette feature for libpixmap.

Following API functions are provided through the
.B palette.h
header file:

.B palette
\- color palette function.
.br
.B palette_search_id
\- search color palette ID by name.
.br
.B palette_search_name
\- search color palette name by ID.

.SH CONSTANTS
PALETTE_NTYPES            59
.br
// IDs
.br
DS9_GREY                   0 ,	DS9_GRAY                     0
.br
DS9_RED                    1 ,	DS9_GREEN                    2
.br
DS9_BLUE                   3 ,	DS9_A                        4
.br
DS9_B                      5 ,	DS9_BB                       6
.br
DS9_HE                     7 ,	DS9_I8                       8
.br
DS9_AIPS0                  9 ,	DS9_SLS                      10
.br
DS9_HEAT                   11,	DS9_COOL                     12
.br
DS9_RAINBOW                13,	DS9_STANDARD                 14
.br
DS9_STAIRCASE              15,	DS9_COLOR                    16
.br
IDL1_B_W_LINEAR            17,	IDL1_BLUE_WHITE              18
.br
IDL1_GRN_RED_BLU_WHT       19,	IDL1_RED_TEMPERATURE         20
.br
IDL1_BLUE_GREEN_RED_YELLOW 21,	IDL1_STD_GAMMA_II            22
.br
IDL1_PRISM                 23,	IDL1_RED_PURPLE              24
.br
IDL1_GREEN_WHITE_LINEAR    25,	IDL1_GRN_WHT_EXPONENTIAL     26
.br
IDL1_GREEN_PINK            27,	IDL1_BLUE_RED                28
.br
IDL1_16_LEVEL              29,	IDL1_RAINBOW                 30
.br
IDL1_STEPS                 31,	IDL1_STERN_SPECIAL           32
.br
IDL2_HAZE                  33,	IDL2_BLUE_PASTEL_RED         34
.br
IDL2_PASTELS               35,	IDL2_HUE_SAT_LIGHTNESS_1     36
.br
IDL2_HUE_SAT_LIGHTNESS_2   37,	IDL2_HUE_SAT_VALUE_1         38
.br
IDL2_HUE_SAT_VALUE_2       39,	IDL2_PURPLE_RED_WITH_STRIPES 40
.br
IDL2_BEACH                 41,	IDL2_MAC_STYLE               42
.br
IDL2_EOS_A                 43,	IDL2_EOS_B                   44
.br
IDL2_HARDCANDY             45,	IDL2_NATURE                  46
.br
IDL2_OCEAN                 47,	IDL2_PEPPERMINT              48
.br
IDL2_PLASMA                49,	IDL2_BLUE_RED                50
.br
IDL2_RAINBOW               51,	IDL2_BLUE_WAVES              52
.br
IDL2_VALCANO               53,	IDL2_WAVES                   54
.br
IDL2_RAINBOW18             55,	IDL2__RAINBOW                56
.br
IDL2_ORBIT_VIEWER_COLOR    57,	IDL2_ORBIT_VIEWER_GREY       58
.br
IDL2_ORBIT_VIEWER_GRAY     58

.SH SEE ALSO
.BR pixmap_intro (l)
.\" .BR palette (l),
.\" .BR palette_search_id (l),
.\" .BR palette_search_name (l)

.SH COPYRIGHT
 (c)2010-2015 Seiji Nishimura, All rights reserved.
