#include <stdio.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#include "smem.h"

int main(int argc, char *argv[])
{
  ShMem sm;  

  sm.get_shmem(SM_KEY, SM_SIZE);
  void *mem = sm.mem();
  ShFormt *sh_format = (ShFormt*)mem;
  sh_format->id_ = 3;
  printf("sh_format->id_: %d\n", sh_format->id_);
  while(1)
  {
    static int i=0;
    sleep(2);
    sh_format->id_ = i;
    ++i;
  }
  return 0;
}
