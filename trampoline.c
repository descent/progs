#include <stdio.h>

void other(void (*funcp)())
{
  (*funcp)();
}

void outer(void)
{
  int a=10;

  void inner(void)
  {
    printf("outer's a is %d\n", a);
  }
  other(inner);
}

int main(int argc, char *argv[])
{
  outer(); 
  return 0;
}
