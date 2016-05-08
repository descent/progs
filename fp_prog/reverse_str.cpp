#include <stdio.h>

void func(const char *str)
{
  if (*str == 0)
  {
    return;
  }
  else
  {
    func(str+1);
    printf("%c", *str);
  }
}

int main(int argc, char *argv[])
{
  const char *str="abcdefgh";  
  if (argc > 1)
  {
    str = argv[1];
  }
  printf("normal: %s\n", str);
  func(str);
  printf("\n");
  return 0;
}
