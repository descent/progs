#include <stdio.h>
#include <stdlib.h>

int cal_n(int n, int p)
{
  if (n == 1)
    return p;
  else
    return cal_n(n-1, p*(n-1));
}

int fact(int n)
{
  return cal_n(n, n);
}

int main(int argc, char *argv[])
{
  int n = 5;
  if (argc > 1)
    n = strtol(argv[1], 0, 10);
  printf("fact(%d): %d\n", n, fact(n));
  return 0;
}
