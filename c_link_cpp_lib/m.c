#include <stdio.h>

#include "cpp_interface.h"

int main(int argc, char *argv[])
{
  printf("c main begin\n");
  int v = get_hello_val();
  printf("v: %d\n", v);
  printf("c main end\n");
  return 0;
}
