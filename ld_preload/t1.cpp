#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  const char *fn ="/tmp/a";
  printf("rm %s\n", fn);
  int ret = unlink(fn);
  printf("ret: %d\n", ret);
  if (ret == -1)
  {
    perror("unlink fail\n");
  }
  system("rm /tmp/a");
    
  return 0;
}
