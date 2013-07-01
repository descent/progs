#include <stdio.h>

int p=0x9876;
int i=0x1234;

void func(int *j)
{
  *j = 0x56ef;
#ifdef _MSC_VER
  printf("vc i: %x\n", i);
#else
  printf("gcc/linux i: %x\n", i);
#endif
  return;
}

void hello()
{
  //puts("hello");
  func(&i);
}

