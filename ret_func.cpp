#include <stdio.h>

int num;

typedef int (*fp)(int i);

int add_n(int i)
{
  return num + i;
}

fp get_fp(int n)
{
  num = n;
  return add_n;
}

int main(int argc, char *argv[])
{
  printf("%d\n", (*(get_fp(9)))(3));
  return 0;
}
