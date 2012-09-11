#include <stdio.h>

#include "console.h"

void init_buf(Console *console)
{
  for (int i=0 ; i < PAGE*BUF_H ; ++i)
    console->buf[i] = 'z';
}

void print_screen(Console *console)
{
  int index = console->begin;
  for (int i=0 ; i < BUF_H ; ++i)
  {
    printf("%c ", console->buf[index]);
    index = (index+1) % (PAGE*BUF_H);
  }
  printf("\n");
}

void print_buf(Console *console)
{
  for (int i=0 ; i < PAGE*BUF_H ; ++i)
    printf("%c ", console->buf[i]);
  printf("\n");
}

int main(int argc, const char *argv[])
{
  Console console;
  console.begin = 0;

  init_buf(&console);
  print_buf(&console);
  int y = 0;
  char ch = '0';
  for (y=0 ; y < 50; ++y)
  {
    put(&console, y, ch);
    printf("y: %d\t\t", y);
    printf("input: %c\t\t", ch);
    printf("begin: %d\n", console.begin);
    print_buf(&console);
    print_screen(&console);
    ++ch;
    if (ch==':') 
      ch = '0';
  }

  return 0;
}
