/*
 *
 * $Author: descent $
 * $Date: 2002/06/20 02:55:23 $
 * $Id: jpeg.cpp,v 1.2 2002/06/20 02:55:23 descent Exp descent $
 * $Revision: 1.2 $
 * 程式功能：用 jpeg library 來讀取 jpeg 圖檔，用 svgalib 來秀圖
 * 	     並加入透明效果。
 */

#include <cstdio>
#include <cstdlib>

#include <jpeglib.h>
#include <jerror.h>

#include "init.h"

#include <vector>
#include <iostream>
#include <string>


#include <unistd.h>

using namespace SVGA;

//#include <vga.h>
//#include <vgagl.h>

struct Color
{
  Color (unsigned char r, unsigned char g, unsigned char b):r_ (r), g_ (g),
    b_ (b)
  {
  }
  int r () const
  {
    return r_;
  }
  int g () const
  {
    return g_;
  }
  int b () const
  {
    return b_;
  }
private:
  unsigned char r_, g_, b_;
};

class Bitmap
{
public:
  Bitmap (int width, int height):width_ (width), height_ (height)
  {
  }
  void set_color (const std::vector < Color > &color)
  {
    color_ = color;
  }
  const std::vector < Color > &color_pixel () const
  {
    return color_;
  }
  int w () const
  {
    return width_;
  }
  int h () const
  {
    return height_;
  }
private:
  int width_, height_;
  std::vector < Color > color_;
};

int r = 127;
int g = 78;
int b = 50;
int color_value;

void
show (const Bitmap & bitmap, int x, int y, int level = 256)
{
  //bitmap.color_pixel();
  std::vector < Color >::const_iterator it = bitmap.color_pixel ().begin ();
  //gl_getpalettecolor(color_value,&r,&g,&b);
  for (int i = 0; i < bitmap.h (); ++i)
  {
    for (int j = 0; j < bitmap.w (); ++j)
    {
      //gl_setpixelrgb(x+j,y+i,(*it).r()*level/256,(*it).g()*level/256,(*it).b()*level/256);
      int pix_r = (*it).r ();
      int pix_g = (*it).g ();
      int pix_b = (*it).b ();
      //gl_setpixelrgb(x+j,y+i,r +(pix_r - r)*level/256, g +(pix_g - g)*level/256, b + (pix_b - b)*level/256);
      //gl_setpixelrgb(x+j,y+i,pix_r*level+r*(1-level),pix_g*level+g*(1-level),pix_b*level+b*(level));
      if (i <= 120)
	gl_setpixelrgb (x + j, y + i, (*it).r (), (*it).g (), (*it).b ());
      else
	gl_setpixelrgb (x + j, y + i,
			(*it).r () + (r - (*it).r ()) * level / 256,
			(*it).g () + (g - (*it).g ()) * level / 256,
			(*it).b () + (b - (*it).b ()) * level / 256);
      ++it;
    }
  }
  //for ( ; it !=bitmap.color_pixel().end() ; ++it)

}

int
get_hex (char c, char hex[])
{
  char ascii[] = "0123456789abcdef";
  int low = (c & 0x0f);
  int high = ((c >> 4) & 0x0f);
  hex[0] = ascii[high];
  hex[1] = ascii[low];
}


int
main (int argc, char **argv)
{
  using namespace std;
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;

  cinfo.err = jpeg_std_error (&jerr);
  jpeg_create_decompress (&cinfo);

  if (argc < 2)
  {
    cout << "Enter a file name" << endl;
    return -1;
  }

  string filename = argv[1];
  FILE *infile;
  if ((infile = fopen (filename.c_str (), "rb")) == NULL)
  {
    fprintf (stderr, "cann't open file");
    return -1;
  }
  //int level=255;
  //if (argc>=3)
  //level=atoi(argv[2]);
  jpeg_stdio_src (&cinfo, infile);
  jpeg_read_header (&cinfo, true);
  // set parameters fro decompress
  //cinfo.scale_num=1;
  //cinfo.scale_denom=2;
  //cinfo.output_width=640;
  //cinfo.output_height=480;
  //cinfo.image_height=480;
  jpeg_start_decompress (&cinfo);

  JSAMPARRAY buffer;
  int row_stride = cinfo.output_width * cinfo.output_components;
  int jpeg_width = cinfo.output_width;
  buffer =
    (*cinfo.mem->alloc_sarray) ((j_common_ptr) & cinfo, JPOOL_IMAGE,
				row_stride, 1);
  JSAMPROW ptr = NULL;
  int i = 0;
  //vector<JSAMPLE> bitmap;


  //vga_init();
  //int vga_mode=G640x480x16M32;
  //vga_setmode(vga_mode);
  //gl_setcontextvga(vga_mode);
  std::vector < Color > color;
  Bitmap bitmap (cinfo.output_width, cinfo.output_height);
  while (cinfo.output_scanline < cinfo.output_height)
  {
    jpeg_read_scanlines (&cinfo, buffer, 1);
    ptr = buffer[0];
    //cout << "line " << ++i << " : " << endl;
    int index = 0;
    // scanline 是圖檔的寬度 * 顏色的數目，在 full color 一個 pixel 要三個 byte
    //for (int col=0 ; col < cinfo.image_width * cinfo.output_components ; col++)
    for (int col = 0; col < cinfo.image_width; col++)
    {
      //cout << index++ << " : GETJSAMPLE(*ptr++) : " << GETJSAMPLE(*ptr++) << endl;
      //bitmap.push_back(GETJSAMPLE(*ptr++));
      //gl_setpixelrgb(x+dx,y,GETJSAMPLE(*ptr)*level/256,GETJSAMPLE(*(ptr+1))*level/256,GETJSAMPLE(*(ptr+2))*level/256);
      color.
	push_back (Color
		   (GETJSAMPLE (*ptr), GETJSAMPLE (*(ptr + 1)),
		    GETJSAMPLE (*(ptr + 2))));

#ifdef DUMP_BITMAP_DATA
      char h[2];
      get_hex(GETJSAMPLE(*ptr), h);
      cout << h[0] << h[1] << " ";
      get_hex(GETJSAMPLE(*(ptr+1)), h);
      cout << h[0] << h[1] << " ";
      get_hex(GETJSAMPLE(*(ptr+2)), h);
      cout << h[0] << h[1] << " ";
    cout << endl;
#endif
      //gl_setpixelrgb(x+dx,y,GETJSAMPLE(*ptr),GETJSAMPLE(*(ptr+1)),GETJSAMPLE(*(ptr+2)));
      //dx++;
      ptr += 3;
    }
    //dx=0;
    //y++;
#ifdef DUMP_BITMAP_DATA
    cout << endl;
#endif
  }
  bitmap.set_color (color);
  //vga_setmode(TEXT);
  int color_components = cinfo.output_components;
  //cout << "cinfo.output_components : " << cinfo.output_components << endl;
  jpeg_finish_decompress (&cinfo);
  jpeg_destroy_decompress (&cinfo);

  fclose (infile);

  init_svga ();

  //gl_setpalettecolor(color_value,r,g,b);
#if 0
  for (int h = 0; h < HEIGHT; ++h)
    for (int w = 0; w < WIDTH; ++w)
      //for (int h=0 ; h < 480 ; ++h)
      //for (int w=0 ; w < 640 ; ++w)
      gl_setpixelrgb (w, h, r, g, b);
#endif

  int x = 100, y = 100;
  int dx = 0, dy = 0;

  show (bitmap, 100, 100, 100);
  //show(bitmap,100,100);
  for (int i = 0; i <= 256; i += 8)
  {
    show (bitmap, 100, 100, i);
    sleep (1);
  }
  /*
     for (int i=256 ; i >=0 ; i-=8)
     {
     show(bitmap,0,0,i);
     sleep(1);
     }
   */
  vga_getch ();
  vga_setmode (TEXT);
  return 0;
}
