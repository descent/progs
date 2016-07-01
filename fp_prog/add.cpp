#include <stdio.h>


int add_help(int x, int y)
{
  if (x>=10)
    return y;
  else
    return add_help(x+1, y+ x+1);
}

int add_tail(int x)
{
  return add_help(1, 1);
}

int add (int x)
{
  if (x >= 10)
    return x;
  else
    return x+add(x+1);
}

int main(int argc, char *argv[])
{
  printf("add: 1 + ... + 10 = %d\n", add(1));
  printf("add_tail: 1 + ... + 10 = %d\n", add_tail(1));
  return 0;
}
