#include "type.h"

#include <stdio.h>

using namespace std;

int main(int argc, char *argv[])
{
  u16 a = 0xffff;
  s16 a1 = 0xffff;
  u16 b = 1;

  u32 c = a+b;
  printf("a: %d\n", a);
  printf("a1: %d\n", a1);
  printf("%d\n", b);
  printf("%d\n", c);

  return 0;
}
