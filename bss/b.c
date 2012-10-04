/*
 * bss section test
 *
 */ 


#include <stdio.h>

int ABCDEF;
extern int _end;
extern int __bss_start;

void fill_bss(int v)
{
  int *i=0;
  for (i = &__bss_start ; i != &_end ; ++i)
  {
    printf("i: %p\n", i);
    *i = v;
  }

}

int main(void)
{
  //fill_bss(0xabcd5678);
  //fill_bss(0);
  printf("&__bss_start: %p\n", &__bss_start);
  printf("&_end: %p\n", &_end);
  printf("ABCDEF address: %p\n", &ABCDEF);
  printf("ABCDEF: %x\n", ABCDEF);
  return 0;
}
