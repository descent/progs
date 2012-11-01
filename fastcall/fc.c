#include <stdio.h>

__attribute__((fastcall)) void foo1(char c, int i, int j, const char *ptr);
__attribute__((fastcall)) void foo1(char c, int i, int j, const char *ptr)
{
  printf("%c %d %d %p\n", c, i, j, ptr);
}

void foo2(char c, int i, int j, const char *ptr)
{
  printf("%c %d %d %p\n", c, i, j, ptr);
}

void bar1()
{
    foo1('a', 9, 7, (char*)(0x1234));
}

void bar2()
{
    foo2('a', 9, 7, (char*)(0x1234));
}

int main()
{
  bar1();
  bar2();
  return 0;
}
