#include <stdio.h>
extern "C" int unlink(const char *pathname);
int unlink(const char *pathname)
{
  printf("my unlink\n");
  return 0;
}

