#include "console.h"

int put(Console *console, int y, char ch)
{
  console->buf[y%(PAGE*BUF_H)] = ch;
  if (y <= (BUF_H-1))
    console->begin = 0;
  else
    console->begin = (y - (BUF_H-1))%(PAGE*BUF_H);
}
