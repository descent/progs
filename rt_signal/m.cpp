/*
 kill -s SIGRTMIN 2519
 kill -s SIGRTMAX 2519

  sig : 34
  sig : 64
 */ 

#include <signal.h>
#include <stdio.h>

void sig_handler(int sig)
{
  printf("sig : %d\n", sig);
}

int main(int argc, char *argv[])
{
  signal(SIGRTMIN, sig_handler);
  signal(SIGRTMAX, sig_handler);

  while(1)
  {
  }
  return 0;
}
