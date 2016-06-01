#ifndef SMEM_H
#define SMEM_H

#include <sys/ipc.h>
#include <sys/shm.h>


#define SM_SIZE 1024*1024
#define SM_KEY 1234

struct ShFormt
{
  int id_;
};

class ShMem
{
  public:
    int get_shmem(key_t key, size_t size);
    int free_shmem();
    ShMem();
    ~ShMem();
    void *mem(){return sh_mem_;}
  private:
    void *sh_mem_;
    int shmid_;
};

#endif
