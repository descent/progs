#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <vga.h>
#include <vgagl.h>

#define BLACK			(0)
#define BLUE			(1)
#define GREEN			(2)
#define CYAN			(3)
#define RED			(4)
#define MAGENTA			(5)
#define BROWN			(6) // or YELLOW
#define GRAY		        (7)

#define LIGHTBLACK      	(8)
#define LIGHTBLUE       	(9)
#define LIGHTGREEN      	(10)
#define LIGHTCYAN       	(11)
#define LIGHTRED        	(12)
#define LIGHTMAGENTA    	(13)
#define LIGHTBROWN      	(14)

#ifdef VGALIB
#define LIGHTWHITE      	(vga_white())
#else
#define LIGHTWHITE      	(255)
#endif

class Graphic
{
  public:
    Graphic();
    ~Graphic();
    void init_graph_mode();
  private:
};

#endif
