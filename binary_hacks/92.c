#include <stdio.h>
#include <signal.h>

int being_debugged=1;

void signal_handler(int signum)
{
  being_debugged=0;
}

int main(int argc, char *argv[])
{
  signal(SIGTRAP, signal_handler);
  __asm__ __volatile__("int3");
  if (being_debugged)
  {
    printf("begin debugged\n");
  }
  else
  {
    printf("not begin debugged\n");
  }
  return 0;
}
