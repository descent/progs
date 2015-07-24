#ifndef FB_H
#define FB_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <stdint.h>

#define LINUXFB 1

#define BLACK                   (0)
#define BLUE                    (1)
#define GREEN                   (2)
#define CYAN                    (3)
#define RED                     (4)
#define MAGENTA                 (5)
#define BROWN                   (6) // or YELLOW
#define GRAY                    (7)

#define LIGHTBLACK              (8)
#define LIGHTBLUE               (9)
#define LIGHTGREEN              (10)
#define LIGHTCYAN               (11)
#define LIGHTRED                (12)
#define LIGHTMAGENTA            (13)
#define LIGHTBROWN              (14)
#define LIGHTWHITE              (255)


void color2rgb(uint8_t color, uint8_t &r, uint8_t &g, uint8_t &b);

class Fb
{
  public:
    Fb();
    ~Fb();
    int fb_init();
    void setpixelrgb(int x, int y, int r, int g, int b);
  private:
   int fbfd;
   char *fbp;
   long int screensize;
   struct fb_var_screeninfo vinfo;
   struct fb_fix_screeninfo finfo;
};

#endif
