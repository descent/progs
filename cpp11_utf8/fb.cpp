#include "fb.h"


Fb::Fb()
{
  int ret = fb_init();
}

Fb::~Fb()
{
  munmap(fbp, screensize);
  close(fbfd);
  printf("munmap\n");
}

int Fb::fb_init()
{
   int x = 0, y = 0;

   // Open the file for reading and writing
   fbfd = open("/dev/fb0", O_RDWR);
   if (fbfd == -1) {
       perror("Error: cannot open framebuffer device");
       exit(1);
   }
   printf("The framebuffer device was opened successfully.\n");

   // Get fixed screen information
   if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
       perror("Error reading fixed information");
       exit(2);
   }

   // Get variable screen information
   if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
       perror("Error reading variable information");
       exit(3);
   }

   printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

   // Figure out the size of the screen in bytes
   screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

   // Map the device to memory
   fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
                      fbfd, 0);
   if (fbp == (void *)-1) {
       perror("Error: failed to map framebuffer device to memory");
       exit(4);
   }
   printf("The framebuffer device was mapped to memory successfully.\n");
   return 0;
}

#if 0
 int main()
 {

     x = 300; y = 100;       // Where we are going to put the pixel

     // Figure out where in memory to put the pixel
     for (y = 100; y < 300; y++)
         for (x = 100; x < 300; x++) {


             if (vinfo.bits_per_pixel == 32) {
                 *(fbp + location) = 100;        // Some blue
                 *(fbp + location + 1) = 15+(x-100)/2;     // A little green
                 *(fbp + location + 2) = 200-(y-100)/5;    // A lot of red
                 *(fbp + location + 3) = 0;      // No transparency
             } else  { //assume 16bpp
                 int b = 10;
                 int g = (x-100)/6;     // A little green
                 int r = 31-(y-100)/16;    // A lot of red
                 unsigned short int t = r<<11 | g << 5 | b;
                 *((unsigned short int*)(fbp + location)) = t;
             }

         }
     return 0;
 }
#endif

void Fb::setpixelrgb(int x, int y, int r, int g, int b)
{
  long int location = 0;

  location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+vinfo.yoffset) * finfo.line_length;
  switch (vinfo.bits_per_pixel)
  {
    case 16:
    {
    #if 0
      int b = 10;
      int g = (x-100)/6;     // A little green
      int r = 31-(y-100)/16;    // A lot of red
    #endif
      unsigned short int t = r<<11 | g << 5 | b;
      *((unsigned short int*)(fbp + location)) = t;
      break;
    }
    case 32:
    {
      *(fbp + location) = b;        // Some blue
      *(fbp + location + 1) = g;     // A little green
      *(fbp + location + 2) = r;    // A lot of red
      *(fbp + location + 3) = 0;      // No transparency
      break;
    }
  }
}

void color2rgb(uint8_t color, uint8_t &r, uint8_t &g, uint8_t &b)
{
#ifdef LINUXFB
  switch (color)
  {
    case BLACK:
    {
      r = 0;
      g = 0;
      b = 0;
      break;
    }
    case BLUE:
    {
      r = 0;
      g = 0;
      b = 170;
      break;
    }
    case GREEN:
    {
      r = 0;
      g = 170;
      b = 0;
      break;
    }
    case CYAN:
    {
      r = 0;
      g = 170;
      b = 170;
      break;
    }
    case RED:
    {
      r = 170;
      g = 0;
      b = 0;
      break;
    }
    case MAGENTA:
    {
      r = 170;
      g = 0;
      b = 170;
      break;
    }
    case BROWN:
    {
      r = 170;
      g = 85;
      b = 0;
      break;
    }
    case GRAY:
    {
      r = 170;
      g = 170;
      b = 170;
      break;
    }
    case LIGHTBLACK:
    {
      r = 85;
      g = 85;
      b = 85;
      break;
    }
    case LIGHTBLUE:
    {
      r = 85;
      g = 85;
      b = 255;
      break;
    }
    case LIGHTGREEN:
    {
      r = 85;
      g = 255;
      b = 85;
      break;
    }
    case LIGHTCYAN:
    {
      r = 85;
      g = 255;
      b = 255;
      break;
    }
    case LIGHTRED:
    {
      r = 255;
      g = 85;
      b = 85;
      break;
    }
    case LIGHTMAGENTA:
    {
      r = 255;
      g = 85;
      b = 255;
      break;
    }
    case LIGHTBROWN:
    {
      r = 255;
      g = 255;
      b = 85;
      break;
    }
    case LIGHTWHITE:
    {
      r = 255;
      g = 255;
      b = 255;
      break;
    }
  }
#endif
}

#if 0
int main(int argc, char *argv[])
{
  uint8_t r=0, g=170, b=0;
  color2rgb(BLUE, r, g, b);
  Fb fb;
  int x=50, y=200;

  for (int j=0 ; j < 100 ; ++j)
    for (int i=0 ; i < 100 ; ++i)
      fb.setpixelrgb(x+i, y+j, r, g, b);
  
  return 0;
}
#endif
