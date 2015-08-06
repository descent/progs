#ifndef DRAW_H
#define DRAW_H

#include "ft2.h"

#define LFB

#ifdef LFB
#include "fb.h"
#endif

#ifdef SVGALIB
#include "graphic.h"
#endif


void my_draw_bitmap_mono(FT_Bitmap *bitmap,int pen_x,int pen_y, int fg_c=LIGHTWHITE, int bg_c=RED);
void my_draw_bitmap_256(FT_Bitmap *bitmap,int pen_x,int pen_y);

#endif
