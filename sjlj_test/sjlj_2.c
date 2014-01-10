#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf mark;

int ret;

void f(void)
{
  longjmp(mark, 5);
}

int main(int argc, char *argv[])
{
  ret = setjmp(mark);
  printf("yy ret: %d\n", ret);
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
  f();
  return 0;
}

