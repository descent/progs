#include "console.h"

int init(Console *console)
{
  console->warp = 0;
}

int put_ch(Console *console, int x, int y, char ch)
{
  if (y >= PAGE*BUF_H)
    console->warp = 1;
  console->buf[x][y%(PAGE*BUF_H)] = ch;
  if (y <= (BUF_H-1))
    console->begin = 0;
  else
    console->begin = (y - (BUF_H-1))%(PAGE*BUF_H);
  console->scroll_h = console->begin;
}

// h < 0 scroll up 
// h > 0 scroll down
int scroll(Console *console, int h)
{
  int scroll_h;
  if (h < 0)
  {
    scroll_h = -h;
  }

  if ((console->scroll_h + h) > console->begin)
    return -1;

  if (console->begin >= 1)
  {
    console->scroll_h = console->begin + h;
  }
}
