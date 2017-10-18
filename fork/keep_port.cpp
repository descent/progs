#include <unistd.h>

int main(int argc, char *argv[])
{
  daemon(0, 0);
  while(1)
  {
    sleep(1);
  }
  return 0;
}
