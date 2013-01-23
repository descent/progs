//#include <stdio.h>

void printf(const char *format, ...)
{
  puts("interposition printf");
}
int main(int argc, const char *argv[])
{
  printf("a\n");
  return 0;
}
