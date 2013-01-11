/*
 *  modify pointer
 */
#include <stdio.h>

void mp(char *ptr, int addr)
{
  ptr = addr;
  printf("ptr: %p\n", ptr);
}

void mp1(char **ptrptr, int addr)
{
  *ptrptr = addr;
  printf("*ptrptr: %p\n", *ptrptr);
}

int main(int argc, const char *argv[])
{
  char *p=1;
  printf("p: %p\n", p);
  mp(p, 5);       
  printf("p: %p\n", p);
  mp1(&p, 5);       
  printf("p: %p\n", p);
  return 0;
}

