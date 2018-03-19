#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <cstring>

#include <stdint.h>

#include <unistd.h>
#include <sys/mman.h>

void f1()
{
  printf("xx f1\n");
}

void f2()
{
  printf("xx f2\n");
}

int main(int argc, char *argv[])
{
  f1();
  f2();

  auto len = ((char *)f2-(char *)f1);
  auto pagesize = getpagesize();
  printf("pagesize: %d\n", pagesize);

  uintptr_t b = (((uintptr_t)f1)+4095 & (~4095));
  b = (uintptr_t)f1 - (uintptr_t)f1 % pagesize;

  printf("f1: %p\n", f1);
  printf("b: %p\n", b);

  if (0 == mprotect((void*)b, pagesize, PROT_WRITE|PROT_READ|PROT_EXEC))
  {
    printf("set to write|read|exec\n");
  }
  else
  {
    perror("mprotect fail\n");
  }

  memset((void*)f1, 0, len);
  f2();
  f1();

  //printf("len: %p\n", len);

  return 0;
}
