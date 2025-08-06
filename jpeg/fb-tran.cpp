/*
 *
 * $Author: descent $
 * $Date: 2002/06/20 02:55:23 $
 * $Id: jpeg.cpp,v 1.2 2002/06/20 02:55:23 descent Exp descent $
 * $Revision: 1.2 $
 * 程式功能：用 jpeg library 來讀取 jpeg 圖檔，改用 framebuffer 來秀圖
 * 	     並加入透明效果。
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#include <vector>
#include <iostream>
#include <string>

#include <jpeglib.h>
#include <jerror.h>

using namespace std;

uint8_t *fbp;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;

struct Color
{
  Color (unsigned char r, unsigned char g, unsigned char b):r_ (r), g_ (g),
    b_ (b)
  {
  }
  unsigned char r () const
  {
    return r_;
  }
  unsigned char g () const
  {
    return g_;
  }
  unsigned char b () const
  {
    return b_;
  }
private:
  unsigned char r_, g_, b_;
};

class Bitmap
{
public:
  Bitmap(int width, int height):width_ (width), height_ (height)
  {
  }
  Bitmap():width_ (0), height_ (0)
  {
  }
  void set_w_h(int w, int h)
  {
    width_ = w;
    height_ = h;
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

//final = src_color * alpha + background_color * (1 - alpha);

uint8_t alpha_blend(uint8_t fg, uint8_t bg, uint8_t alpha) {
    // alpha: 0~255, fg 前景, bg 背景
    return (fg * alpha + bg * (255 - alpha)) / 255;
}

void show(const Bitmap& bitmap, int x, int y, int level, const Bitmap& bg_bitmap)
{
  //bitmap.color_pixel();
  std::vector < Color >::const_iterator it = bitmap.color_pixel ().begin ();

  std::vector < Color >::const_iterator bg_it = bg_bitmap.color_pixel ().begin ();
  printf("bitmap.h(): %d, bitmap.w(): %d\n", bitmap.h(), bitmap.w());
  printf("bg_bitmap.h(): %d, bg_bitmap.w(): %d\n", bg_bitmap.h(), bg_bitmap.w());

  //gl_getpalettecolor(color_value,&r,&g,&b);
  
  for (int i = 0; i < bitmap.h (); ++i)
  {
    //usleep(1000);
    for (int j = 0; j < bitmap.w (); ++j)
    {
      //gl_setpixelrgb(x+j,y+i,(*it).r()*level/256,(*it).g()*level/256,(*it).b()*level/256);
      int pix_r = (*it).r ();
      int pix_g = (*it).g ();
      int pix_b = (*it).b ();


      

      //gl_setpixelrgb(x+j,y+i,r +(pix_r - r)*level/256, g +(pix_g - g)*level/256, b + (pix_b - b)*level/256);
      //gl_setpixelrgb(x+j,y+i,pix_r*level+r*(1-level),pix_g*level+g*(1-level),pix_b*level+b*(level));
      long location = (y+i)*finfo.line_length + (x+j) * 4; // 4 bytes per pixel
      uint32_t *pixel = (uint32_t *)(fbp + location);
      //printf("i: %d, j: %d, pixel: %p, fbp: %p\n", i, j, pixel, fbp);
	//gl_setpixelrgb (x + j, y + i, (*it).r (), (*it).g (), (*it).b ());
            // 32-bit ARGB，alpha=0xFF (不透明)，紅色R=0xFF, G=0x00, B=0x00
            // 寫法是 0xAARRGGBB
        unsigned int val = 0x00000000;
        unsigned char new_r, new_g, new_b;

        //double alpha = 0.8;
        unsigned char alpha = 100;
        #if 0
        new_r = (unsigned char)((*it).r() * alpha + (*bg_it).r() *(255-alpha))/255;
        new_b = (unsigned char)((*it).b() * alpha + (*bg_it).b() *(255-alpha))/255;
        new_g = (unsigned char)((*it).g() * alpha + (*bg_it).g() *(255-alpha))/255;
        #endif

        new_r = alpha_blend((*it).r(), (*bg_it).r(), alpha);
        new_g = alpha_blend((*it).g(), (*bg_it).g(), alpha);
        new_b = alpha_blend((*it).b(), (*bg_it).b(), alpha);


        #if 0
        new_r =  (*bg_it).r();
        new_g =  (*bg_it).g();
        new_b =  (*bg_it).b();
        #endif


        val |= ((*it).r() << 16);
        val |= ((*it).g() << 8);
        val |= (*it).b();

        unsigned int bg_val = 0x00000000;
        bg_val |= ((*bg_it).r() << 16);
        bg_val |= ((*bg_it).g() << 8);
        bg_val |= (*bg_it).b();

        unsigned int final_val = 0xff000000;

        //final_val |= 0xff << 24;
        final_val |= new_r << 16;
        final_val |= new_g << 8;
        final_val |= new_b;

	*pixel = final_val;
      #if 0
      if (i <= 120)
      {
	//gl_setpixelrgb (x + j, y + i, (*it).r (), (*it).g (), (*it).b ());
            // 32-bit ARGB，alpha=0xFF (不透明)，紅色R=0xFF, G=0x00, B=0x00
            // 寫法是 0xAARRGGBB
        unsigned int val = 0xff000000;
        val |= ((*it).r() << 16);
        val |= ((*it).g() << 8);
        val |= (*it).b();
	*pixel = val;
            //*pixel = 0xFFFF0000;
      }
      else
      {
        unsigned int val = 0xff000000;
        val |= (((*it).r () + (r - (*it).r ()) * level / 256) << 16);
        val |= (((*it).g () + (g - (*it).g ()) * level / 256) << 8);
        val |= ((*it).b () + (b - (*it).b ()) * level / 256);
	*pixel = val;
            //*pixel = 0xFFFF0000;
        #if 0
	gl_setpixelrgb (x + j, y + i,
			(*it).r () + (r - (*it).r ()) * level / 256,
			(*it).g () + (g - (*it).g ()) * level / 256,
			(*it).b () + (b - (*it).b ()) * level / 256);
        #endif
      }
      #endif
      ++it;
      if (i < bg_bitmap.h ())
        ++bg_it;
    }
  }
  //for ( ; it !=bitmap.color_pixel().end() ; ++it)

}

void get_hex (char c, char hex[])
{
  char ascii[] = "0123456789abcdef";
  int low = (c & 0x0f);
  int high = ((c >> 4) & 0x0f);
  hex[0] = ascii[high];
  hex[1] = ascii[low];
}

int jpeg_to_bitmap(const string &filename, Bitmap &bitmap)
{
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;

  cinfo.err = jpeg_std_error (&jerr);
  jpeg_create_decompress (&cinfo);

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

  std::vector < Color > color;
  bitmap.set_w_h(cinfo.output_width, cinfo.output_height);
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
  return 0;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "Enter 2 file name" << endl;
    return -1;
  }

  //string filename = argv[1];

  Bitmap fg_bitmap;
  jpeg_to_bitmap(argv[1], fg_bitmap);

  Bitmap bg_bitmap;
  jpeg_to_bitmap(argv[2], bg_bitmap);



    int fb_fd = open("/dev/fb0", O_RDWR);
    if (fb_fd == -1) {
        perror("open fail");
        return 1;
    }


    if (ioctl(fb_fd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("FBIOGET_FSCREENINFO");
        close(fb_fd);
        return 1;
    }

    if (ioctl(fb_fd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("FBIOGET_VSCREENINFO");
        close(fb_fd);
        return 1;
    }

    printf("Resolution: %dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    if (vinfo.bits_per_pixel != 32) {
        fprintf(stderr, "This program only supports 32-bit framebuffer.\n");
        close(fb_fd);
        return 1;
    }

    long screensize = vinfo.yres * finfo.line_length;
    fbp = (uint8_t *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, 0);
    if (fbp == MAP_FAILED) {
        perror("mmap");
        close(fb_fd);
        return 1;
    }

    printf("load jpg\n");

    int square_x = 300;
    int square_y = 300;
    int size = 80;

    #if 0
    show(bg_bitmap, 300, 200, 100, );
    sleep(2);
    #endif

    show(fg_bitmap, 300, 200, 100, bg_bitmap);
    sleep(2);


#if 0
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            int px = square_x + x;
            int py = square_y + y;

            long location = py * finfo.line_length + px * 4; // 4 bytes per pixel

            // 32-bit ARGB，alpha=0xFF (不透明)，紅色R=0xFF, G=0x00, B=0x00
            // 寫法是 0xAARRGGBB
            uint32_t *pixel = (uint32_t *)(fbp + location);
            *pixel = 0xFFFF0000;
        }
    }
    #endif

    munmap(fbp, screensize);
    close(fb_fd);

    return 0;
}
