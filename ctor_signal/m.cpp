#include "c.h"

#include <signal.h>

#include <stdlib.h>
#include <stdio.h>

Res *res;

void signal_handler(int sig)
{
  printf("sig: %d\n", sig);
  delete res;
  exit(-1);
}


int main(int argc, char *argv[])
{
  res = new Res();
  signal(SIGTERM, signal_handler);
  while(1);

  return 0;
}
