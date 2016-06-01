#include "smem.h"

ShMem::ShMem()
{
}

ShMem::~ShMem()
{
}

int ShMem::get_shmem(key_t key, size_t size)
{
  int shmid_ = shmget(SM_KEY, size, 0666|IPC_CREAT);
  if (shmid_ == -1)
    return -1;

  sh_mem_ = shmat(shmid_, 0, 0);

  if ((void*)-1 == sh_mem_)
    return -1;
}


int ShMem::free_shmem()
{
  if (shmdt(sh_mem_) == -1)
  {
    return -1;
  }
  if (shmctl(shmid_, IPC_RMID, 0) == -1)
    return -1;
}
