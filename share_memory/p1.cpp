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
  sh_format->id_ = 5;
  printf("sh_format->id_: %d\n", sh_format->id_);
  while(1)
  {
    sleep(3);
    printf("sh_format->id_: %d\n", sh_format->id_);
  }
  return 0;
}
