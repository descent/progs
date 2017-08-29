#include <stdio.h>

int main(int argc, char *argv[])
{
  unsigned char a[5][4][6][8];

  printf("a: %p\n", a);
  printf("&a[3][3][2][7]: %p\n", &a[3][3][2][7]);
  printf("offset: %d\n", (&a[3][3][2][7]) - (&a[0][0][0][0]));
  return 0;
}
