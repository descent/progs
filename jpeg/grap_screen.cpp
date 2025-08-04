/*
 *
 *
 *
 * function : use svgalib draw to screen and use jpeglib to 
 *     save this screen to a jpg file.
 */

#include <cstdio>
#include <cstdlib>

#include <jpeglib.h>
#include <jerror.h>
#include <vga.h>
#include <vgagl.h>

#include "init.h"

#include <iostream>
#include <fstream>

using namespace SVGA;
using namespace std;


// hex[] is a char array which size is 2 byte
int get_hex(char c,char hex[])
{
  char ascii[]="0123456789abcdef";
  int low=(c & 0x0f);
  int high= ((c >> 4) & 0x0f);
  hex[0]=ascii[high];
  hex[1]=ascii[low];
}


GraphicsContext *physicalscreen, *virtualscreen;



int main()
{

  int mode=init_svga();
  // init gc

  physicalscreen=gl_allocatecontext();
  gl_getcontext(physicalscreen);

  //gl_setcontextvgavirtual (mode);

  unsigned char *virtual_screen, *screen_pos;

  virtual_screen = (unsigned char *)malloc(WIDTH * HEIGHT*1 * BYTESPERPIXEL);
  screen_pos=virtual_screen;

  gl_setcontextvirtual(WIDTH, HEIGHT, BYTESPERPIXEL, BITSPERPIXEL, virtual_screen);

  virtualscreen=gl_allocatecontext();
  gl_getcontext(virtualscreen);
  // end init gv

  int gray=gl_rgbcolor(100,100,100);
  //gl_clearscreen(gray);

  //gl_setclippingwindow(0,0,200,200);
  gl_circle(200,200,100,gl_rgbcolor(50,200,100));
  for (int i=0 ; i < 200 ; ++i)
    gl_setpixelrgb(10+i,200,100,100,100);  
  gl_line(0,0,100,0, gl_rgbcolor(255,1,2));
  gl_line(0,1,100,1, gl_rgbcolor(255,1,2));
  gl_line(0,2,100,2, gl_rgbcolor(255,1,2));
  gl_line(20,20,100,100,gl_rgbcolor(1,255,9));
  gl_copyscreen(physicalscreen);

  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;

  cinfo.err = jpeg_std_error (&jerr);
  jpeg_create_compress (&cinfo);
  FILE * outfile;

  vga_modeinfo *info=vga_getmodeinfo(mode);

  outfile=fopen("t.jpg","wb");
  if (outfile!=0) // save screen to jpeg file
  {
    jpeg_stdio_dest(&cinfo, outfile);
    cinfo.image_width=WIDTH;
    cinfo.image_height=HEIGHT;
    cinfo.input_components=3;
    cinfo.in_color_space=JCS_RGB;
    jpeg_set_defaults(&cinfo);
    jpeg_start_compress(&cinfo, true);

    JSAMPROW row_pointer[1];
    int row_stride = WIDTH * BYTESPERPIXEL;
    unsigned char *line = (unsigned char *)malloc(3*WIDTH);
    unsigned char *line_ptr = line;

    ofstream log_file ("log");

    ostream &ofs=log_file;


    while (cinfo.next_scanline < cinfo.image_height)
    {

      unsigned char *scanline_ptr = &screen_pos[cinfo.next_scanline * row_stride];
      // dump screen line
      for (int i=0 ; i < WIDTH ; ++i)
      {
        unsigned char *ptr = &screen_pos[cinfo.next_scanline * row_stride];
	for (int j=0 ; j < BYTESPERPIXEL ; ++j)
	{
	  char h[2];
	  get_hex(*ptr++, h);
	  ofs << h[0] << h[1] << " " ;
	}
      }

      ofs << endl;

      // intel is little endian
      // so rgb => bgr
      for (int i=0 ; i < WIDTH ; i++)
      {
        int idx=0;
        *line++ = scanline_ptr[idx+2]; // r
        *line++ = scanline_ptr[idx+1]; // g
        *line++ = scanline_ptr[idx];   // b
        scanline_ptr+=BYTESPERPIXEL;  // if BYTESPERPIXEL is 4 skip the 4st byte
      }


      row_pointer[0]= line_ptr;
      jpeg_write_scanlines(&cinfo, row_pointer,1);
      line=line_ptr;
    }
    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
  }  // end if (outfile!=0) // save screen to jpeg file




  cout << "bytesperpixel : " << info->bytesperpixel << endl;
  cout << "colors : " << info->colors << endl;
  if (info->flags & RGB_MISORDERED)
    cout << "RGB_MISORDERED" << endl;
  cout << "BYTESPERPIXEL : " << BYTESPERPIXEL << endl;

  vga_getch();
  vga_setmode(TEXT);
  return 0;
}
