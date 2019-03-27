#include "draw.h"

#include <iostream>

using namespace std;

int graphic_mode=1;
const char *c_fg = "*";
const char *c_bg = "|";

#ifdef LFB
Fb fb;
#endif

void my_draw_bitmap_mono(FT_Bitmap *bitmap,int pen_x,int pen_y, int fg_c, int bg_c)
{
  uint8_t r=0, g=170, b=0;

#ifdef PRINT_INFO
  cout << "bitmap rows : " << bitmap->rows << endl;
  cout << "bitmap width : " << bitmap->width << endl;
  cout << "bitmap pitch : " << bitmap->pitch << endl;
  if (bitmap->pixel_mode==ft_pixel_mode_mono)
    cout << "bitmap pixel mode : mono" << endl;
   if (bitmap->pixel_mode==ft_pixel_mode_grays)
   {
    cout << "bitmap pixel mode : grays" << endl;
    cout << "bitmap grays level : " << bitmap->num_grays << endl;
   }
#endif

  int startx = pen_x;
  int starty = pen_y;
  int cx=0, cy=0;

  unsigned char *tmp = bitmap->buffer;
  for (int i=0 ; i < bitmap->rows ; i++)
  {
    unsigned char c = *tmp;
    
    int font_w = 0;
    for (int j=0 ; j < bitmap->pitch ; j++)
    {
      #ifdef PRINT_INFO
      printf("%x, ", ch); 
      ++tmp;
      ch = *tmp;
      #endif



      for (int i=7 ; i>=0 ; --i)
      {
        if (font_w < bitmap->width)
        {

        if (((c >> i) & 0x1) == 1)
        {
          if (graphic_mode == '0')
            printf(c_fg);
#ifdef SVGALIB
          else
            gl_setpixel(startx+cx, starty+cy, vga_white());
#endif
#ifdef LFB
          else
          {
            color2rgb(fg_c, r, g, b);
            // color2rgb(BLUE, r, g, b);
            fb.setpixelrgb(startx+cx, starty+cy, r, g, b);
          }
#endif
        }
        else
        {
          if (graphic_mode == '0')
            printf(c_bg);
#ifdef SVGALIB
          else
            gl_setpixelrgb(startx+cx, starty+cy, 180, 0, 0);
#endif
#ifdef LFB
          else
          {
            color2rgb(bg_c, r, g, b);
            fb.setpixelrgb(startx+cx, starty+cy, r, g, b);
          }
#endif

        }

        }
        //++cur_x;
        ++cx;
        ++font_w;
      }
      ++tmp;
      c = *tmp;

    }
    cx=0;
    ++cy;
#ifdef PRINT_INFO
    printf("\n");
#endif
    #if 0
    for (int j=0 ; j < bitmap->width ; j++)
    {
      for (int k=7 ; k >= 0 ; --k)
      {
      }
    }
    ++tmp;
    #endif
  }
}

void my_draw_bitmap_256(FT_Bitmap *bitmap,int pen_x,int pen_y)
{
  cout << "bitmap rows : " << bitmap->rows << endl;
  cout << "bitmap width : " << bitmap->width << endl;
  cout << "bitmap pitch : " << bitmap->pitch << endl;
  if (bitmap->pixel_mode==ft_pixel_mode_mono)
    cout << "bitmap pixel mode : mono" << endl;
   if (bitmap->pixel_mode==ft_pixel_mode_grays)
   {
    cout << "bitmap pixel mode : grays" << endl;
    cout << "bitmap grays level : " << bitmap->num_grays << endl;
   }
  if (graphic_mode == '0')
  {
    cout << "anti-alias mode only support graphic mode" << endl;
    return;
  }

#ifdef SVGALIB
  int startx = pen_x;
  int starty = pen_y;
  int cx=0, cy=0;
  unsigned char *tmp = bitmap->buffer;
  for (int i=0 ; i < bitmap->rows ; i++)
  {
    unsigned char c = *tmp;
    
    for (int j=0 ; j < bitmap->pitch ; j++)
    {
      //gl_setpixel(startx+cx, starty+cy, c);
      if (c==0)
        gl_setpixelrgb(startx+cx, starty+cy, 0, 120, 0);
      else
        gl_setpixelrgb(startx+cx, starty+cy, c, 0, 0);
      printf("%x, ", c); 
      ++tmp;
      c = *tmp;
      ++cx;
    }
    cx=0;
    ++cy;
    //usleep(50000);
  }
#endif
}
