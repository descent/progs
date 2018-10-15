/*
 * pass a function pointer and argument, then call the funciton pointer and pass the argument to it.
 */
#include <stdio.h>

int ret;

void *(myf) (void *arg)
{
  int *my_arg_L = (int *)arg;
  printf("myf arg: %p\n", arg);

  printf("my_arg_L: %d, %d\n", my_arg_L[0], my_arg_L[1]);
  ret = 99;
  return &ret;
}

int create(void *(*start_routine) (void *), void *arg)
{
  printf("arg: %p\n", arg);
  start_routine(arg);
  return 0;
}

int main(int argc, char *argv[])
{
  int p=2, q=100;
  int arg_L[2] = { p, q-1 };
  printf("arg_L: %p\n", arg_L);


  int r = create(myf, (void *)arg_L);

  printf("r: %d\n", r);

  return 0;
}
