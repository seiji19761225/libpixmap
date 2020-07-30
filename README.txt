
    #          #    #####   #####      #    #    #  #    #    ##    #####
    #          #    #    #  #    #     #     #  #   ##  ##   #  #   #    #
    #          #    #####   #    #     #      ##    # ## #  #    #  #    #
    #          #    #    #  #####      #      ##    #    #  ######  #####
    #          #    #    #  #          #     #  #   #    #  #    #  #
    ######     #    #####   #          #    #    #  #    #  #    #  #

Copyright (c) 2010-2015
     Seiji Nishimura,  All rights reserved.
E-Mail: seiji1976@gmail.com

$Id: README.txt,v 1.1.1.4 2020/07/29 00:00:00 seiji Exp seiji $

1. Introduction
Simple pixmap library, libpixmap, provides portable 24bit full color graphics functionality.
It is consisted of following modules:
- Pixmap module (core module)
- Palette module
- Window module (optional)

2. License
The libpixmap library is released under GPL Version 2.0.
Refer to doc/LICENSE.txt for the license information.

THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS'' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.

3. Installation
Refer to doc/INSTALL.txt for the detail installation procedures.

4. Data types
Following pixel_t and pixmap_t data types are defined in pixmap.h.

    typedef struct {        // pixel
    #if SIZEOF_PIXEL_T == 4
        unsigned char pad;  // padding element
    #endif
        unsigned char r, g, b;
    } pixel_t;

    typedef struct {        // pixmap
        int width, height;
        pixel_t *data;
    } pixmap_t;

Following window_t data type is defined in window.h:

    typedef struct {        // graphics window
        pixmap_t pixmap;    // internal pixmap data
        void *be;           // hook to the system dependent components.
    } window_t;

5. API functions
Each module provides API functions.
Refer to man page of each API function for the detail information (usage, feature, arguments, and known limitations).

5-1. Pixmap module
Following API functions are provided through the pixmap.h header file:
   pixel_blend - blend two pixels (=alpha blending).
   pixel_get_r, pixel_get_g, pixel_get_b - get the R, G, B value of a pixel.
   pixel_invert - invert a pixel value.
   pixel_set_named_color - specify a pixel value by name.
   pixel_set_rgb - specify a pixel value by RGB.
   pixmap_blend_image - blend entire image of two pixmaps (=alpha blending).
   pixmap_blend_subimage - blend subimages of two pixmaps (=alpha blending).
   pixmap_clear_image - clear entire image of a pixmap.
   pixmap_clear_subimage - clear subimage of a pixmap.
   pixmap_copy_image - copy entire image of a pixmap.
   pixmap_copy_subimage - copy subimage of a pixmap.
   pixmap_create - create a pixmap.
   pixmap_destroy - destroy a pixmap.
   pixmap_draw_arc - draw an arc.
   pixmap_draw_arrow - draw an arrow.
   pixmap_draw_ellipse - draw an ellipse.
   pixmap_draw_line - draw a line.
   pixmap_draw_polygon - draw a polygon.
   pixmap_draw_string -  draw a string.
   pixmap_fill_arc - draw a filled arc (pie slice or chord).
   pixmap_fill_ellipse - draw a filled ellipse.
   pixmap_fill_polygon - draw a filled polygon.
   pixmap_fill_triangle - draw a filled triangle.
   pixmap_get_pixel - get a pixel information.
   pixmap_get_pointer - get pointer to the pixel buffer of a pixmap.
   pixmap_get_size - get the size information of a pixmap.
   pixmap_invert_image - invert entire image of a pixmap.
   pixmap_invert_subimage - invert subimage of a pixmap.
   pixmap_load_pnmfp, pixmap_load_pnmfile - load a PNM image and create the pixmap data.
   pixmap_put_pixel - put a pixel (=draw a point).
   pixmap_write_pnmfp, pixmap_write_pnmfile - write out a pixmap in PNM image format.

5-2. Palette module
Following API functions are provided through the palette.h header file:
   palette - color palette function.
   palette_search_id - search color palette ID by name.
   palette_search_name - search color palette name by ID.

5-3. Window module
Following API functions are provided through the window.h header file:
   window_clear_image - clear entire image of an window.
   window_clear_subimage - clear subimage of an window.
   window_close - close an window.
   window_discard_inputs - discard all user input events.
   window_draw_arc - draw an arc.
   window_draw_arrow - draw an arrow.
   window_draw_ellipse - draw an ellipse.
   window_draw_line - draw a line.
   window_draw_polygon - draw a polygon.
   window_draw_string - draw a string.
   window_fill_arc - draw a filled arc.
   window_fill_ellipse - draw a filled ellipse.
   window_fill_polygon - draw a filled polygon.
   window_fill_triangle - draw a filled triangle.
   window_get_image - dump entire image of an window and create the pixmap data.
   window_get_input - get a user input event.
   window_get_pixel - get a pixel information.
   window_get_pointer - get pointer to the pixel buffer of an window.
   window_get_size - get the size information of an window.
   window_get_subimage - dump subimage of an window and create the pixmap data.
   window_invert_image - invert entire image of an window.
   window_invert_subimage - invert subimage of an window.
   window_load_pnmfp, window_load_pnmfile - load a PNM image and open the window.
   window_open - open an window.
   window_put_image - copy entire image of a pixmap onto an window.
   window_put_pixel - put a pixel (=draw a point).
   window_put_subimage - copy subimage of a pixmap onto an window.
   window_query_pointer - query mouse pointer position on the window.
   window_rename - rename an window.
   window_update_image - update entire image on an window.
   window_update_subimage - update subimage on an window.
   window_write_pnmfp, window_write_pnmfile - write out an window in PNM image format.

EOF.
