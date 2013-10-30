#include <stdio.h>
#include <math.h>

float magic_sqrt(float x)
{
  float xhalf = 0.5*x;
  int i=*(int*)&x;
  i = 0x5f375a86 - (i >> 1);
  x = *(float*)&i;
  x = x*(1.5f - xhalf*x*x);
  x = x*(1.5f - xhalf*x*x);
  x = x*(1.5f - xhalf*x*x);

  return 1/x;
}

float inv_sqrt(float x)
{
  float xhalf = 0.5*x;
  int i=*(int*)&x;
  i = 0x5f3759df - (i >> 1);
  x = *(float*)&i;
  x = x*(1.5f - xhalf*x*x);
  return x;
}

int main(int argc, char *argv[])
{
  printf("%f\n", inv_sqrt(2)); 
  printf("%f\n", 1/sqrt(2)); 
  printf("%g\n", magic_sqrt(65535)); 
  return 0;
}
