#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf mark;

int ret;

void f1(void)
{
  char arr[1000];
  int i=0;
  for (i=0 ; i < 1000; ++i)
    arr[i] = 0xff;
}

void f(void)
{
  ret = setjmp(mark);
}

int main(int argc, char *argv[])
{
  f();
  printf("xx ret: %d\n", ret);
  if (ret == 0)
  {
     printf("init setjmp\n");
  }
  else
  {
    printf("exit\n");
    exit(0);
  }
  printf("xxx\n");
  longjmp(mark, 5);
  return 0;
}

