#include <stdio.h>

int i=0x1234;
//int p=0x9876;

void func(int *j)
{
  *j = 0x5678;
  printf("i: %x\n", i);
  return;
}

void hello()
{
  //puts("hello");
  func(&i);
}

