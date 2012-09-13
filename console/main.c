#include <stdio.h>

#include "console.h"

void init_buf(Console *console)
{
  for (int i=0 ; i < PAGE*BUF_H ; ++i)
    for (int j=0 ; j < BUF_W ; ++j)
      console->buf[j][i] = 'z';
}

void print_screen(Console *console)
{
  //int index = console->begin;
  int index = console->scroll_h;


  for (int i=0 ; i < BUF_H ; ++i)
  {
    for (int j=0 ; j < BUF_W ; ++j)
    {
      printf("%c ", console->buf[j][index]);
    }
    index = (index+1) % (PAGE*BUF_H);
    printf("\n");
  }
  printf("\n");
}

void print_buf(Console *console)
{
  for (int i=0 ; i < PAGE*BUF_H ; ++i)
  {
    for (int j=0 ; j < BUF_W ; ++j)
    {
      printf("%c ", console->buf[j][i]);
    }
    printf("\n");
  }
  printf("\n");
}

int main(int argc, const char *argv[])
{
  Console console;
  console.begin = 0;

  init_buf(&console);
  printf("init buf:\n");
  print_buf(&console);
  int y = 0;
  char ch = '0';
  int warp = 0;
  for (y=0 ; y < 20; ++y)
  {
    for (int x=0 ; x < BUF_W; ++x)
    {
      put_ch(&console, x, y, ch);
      printf("(%d, %d)\t\t", x, y);
      printf("input: %c\t\t", ch);
      printf("begin: %d\t\t", console.begin);
      if (y >= PAGE*BUF_H)
      {
        //printf("warp!!\n");
        warp = 1;
      }
      printf("scroll: ");
#if 1
      if (warp == 1)
      {
        int index_y = (console.begin + BUF_H) % (PAGE*BUF_H);

        //for (int i = 0 ; i < (PAGE-1)*BUF_H ; ++i)
        // begin 往下加上 BUF_H, 再往下加 (PAGE-1)*BUF_H 個 (一次加一)
        // ex: begin = 5, (5+3) % 9 = 8
        // 8, 9%9 = 0, 10%9 = 1, 11%9 = 2 , 12%9 = 3 , 13%9 = 4
        for (int i = 0 ; i < (PAGE-1)*BUF_H ; ++i)
        {
          printf("%d ", (index_y+ (PAGE-1)*BUF_H - 1- i)%(PAGE*BUF_H) );
        }
      }
      else
#endif
      {
        for (int i = console.begin-1 ; i >= 0 ; --i)
          printf("%d ", i);
      }
      printf("\n");
    }
    ++ch;
    if (ch==':') 
      ch = '0';
    printf("print buf:\n");
    print_buf(&console);

    printf("print screen (%dX%d):\n", BUF_W, BUF_H);
    print_screen(&console);

    printf("scroll screen\n");
    scroll(&console, -1);
    print_screen(&console);
  }

  return 0;
}
