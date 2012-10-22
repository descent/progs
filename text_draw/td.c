#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
#define SWIDTH 50
#define SHEIGHT 50
 
int f(x) {
  int p = (25 - x) / 3;
  int yd = 25;
  return p * p + yd;
}
 
int f2(x) {
  float p = (x - SWIDTH / 2.0) / SWIDTH * 4.0 * 3.14159;
  int yd = 25;
  return (int) (floor(sin(p) * 10) + yd);
}
 
void printscale_x() {
  int x;
 
  printf("   ");
  for(x = 0; x < SWIDTH; ++x) {
    if (x % 10 == 0)
      printf("%d", x / 10);
    else
      printf(" ");
  }
  printf("\n");
 
  printf("   ");
  for(x = 0; x < SWIDTH; ++x) {
    printf("%d", x%10);
  }
  printf("\n");
}
 
main()
{
  char scrn[SWIDTH][SHEIGHT];
  int x, y;
 
  for(x = 0; x < SWIDTH; ++x) {
    for (y = 0; y < SHEIGHT; ++y) {
      scrn[x][y] = ' ';
    }
  }
 
  for (x=0; x < SWIDTH; ++x) {
    /*printf("%d\n", f2(x));*/
    if (f2(x) < SHEIGHT) {
      scrn[x][f2(x)] = '$';
    }
    else {
      scrn[x][SHEIGHT - 1] = '+';
    }
  }
 
  printscale_x();
 
  for(y = SWIDTH - 1; y >= 0; --y) {
 
    printf("%02d ", y);
    for (x = 0; x < SWIDTH; ++x) {
      printf("%c", scrn[x][y]);
    }
    printf("\n");
  }
 
  printscale_x();
 
  return 0;
}
 
