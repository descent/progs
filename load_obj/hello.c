#include <stdio.h>

int i=0x1234;

void func(int *j)
{
  *j = 0x5678;
  printf("j: %x\n", *j);
  return;
}

void hello()
{
  //puts("hello");
  func(&i);
}

