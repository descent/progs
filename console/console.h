#ifndef CONSOLE_H
#define CONSOLE_H

#define BUF_W 2
#define BUF_H 3
#define PAGE 3


typedef struct Console_
{
  char buf[BUF_W][PAGE*BUF_H];
  int begin;
  int scroll_h;
  int warp;
}Console;

int put_ch(Console *console, int x, int y, char ch);
int scroll(Console *console, int h);

#endif
