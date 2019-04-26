#include "graphic.h"
#include <stdio.h>
#include <stdlib.h>

Graphic::Graphic()
{
#ifdef SVGALIB
  init_graph_mode();
  gl_fillbox(0,0,640,480, 200);
  //vga_getch();
#endif
}

Graphic::~Graphic()
{
#ifdef SVGALIB
  vga_getch();
  vga_setmode(TEXT);
#endif
}

void Graphic::init_graph_mode()
{
#ifdef SVGALIB
  vga_init();
  //int vga_mode=G640x480x16M;
  int vga_mode=34;

  if (!vga_hasmode(vga_mode)) 
  {
    printf("Mode not available.\n");
    exit(-1);
  }
  vga_setmode(vga_mode);
  gl_setcontextvga(vga_mode);
#endif

#if 0
  gl_setpalettecolor(BLUE, 0, 0, 63); // blue
  gl_setpalettecolor(BLACK, 0, 0, 0); // black
  gl_setpalettecolor(GREEN, 0, 63, 0);
  gl_setpalettecolor(RED, 63, 0, 0);
  gl_setpalettecolor(BROWN, 170/4, 85/4, 0);
  gl_setpalettecolor(MAGENTA, 170/4, 0, 170/4);
  gl_setpalettecolor(CYAN, 0, 170/4, 170/4);
  gl_setpalettecolor(GRAY, 48, 48, 48);

  gl_setpalettecolor(LIGHTBLACK, 85/4, 85/4, 85/4);
  gl_setpalettecolor(LIGHTBLUE, 85/4, 85/4, 255/4);
  gl_setpalettecolor(LIGHTGREEN, 85/4, 255/4, 85/4);
  gl_setpalettecolor(LIGHTCYAN, 85/4, 255/4, 255/4);
  gl_setpalettecolor(LIGHTRED, 25/45/4, 85/4, 85/4);
  gl_setpalettecolor(LIGHTMAGENTA, 255/4, 85/4, 255/4);
  gl_setpalettecolor(LIGHTBROWN, 255/4, 255/4, 85/4);
#endif
}
