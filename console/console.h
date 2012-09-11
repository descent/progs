#ifndef CONSOLE_H
#define CONSOLE_H

#define BUF_H 5
#define PAGE 3


typedef struct Console_
{
  char buf[PAGE*BUF_H];
  int begin;
}Console;

int put(Console *console, int y, char ch);

#endif
