#include "spinlock.h"


static inline void atomic_add(int i, Atomic *v)
{
        unsigned long tmp;
        int result;

        __asm__ __volatile__("@ atomic_add\n"
"1:     ldrex   %0, [%3]\n"
"       add     %0, %0, %4\n"
"       strex   %1, %0, [%3]\n"
"       teq     %1, #0\n"
"       bne     1b"
        : "=&r" (result), "=&r" (tmp), "+Qo" (v->val_)
        : "r" (&v->val_), "Ir" (i)
        : "cc");
}

static inline void atomic_sub(int i, Atomic *v)
{
        unsigned long tmp;
        int result;

        __asm__ __volatile__("@ atomic_sub\n"
"1:     ldrex   %0, [%3]\n"
"       sub     %0, %0, %4\n"
"       strex   %1, %0, [%3]\n"
"       teq     %1, #0\n"
"       bne     1b"
        : "=&r" (result), "=&r" (tmp), "+Qo" (v->val_)
        : "r" (&v->val_), "Ir" (i)
        : "cc");
}


void spinlock_init(Spinlock *spinlock)
{
  spinlock->val_ = 1;
}

int spin_lock(Spinlock *spinlock)
{
  atomic_sub(1, spinlock);
  while(spinlock->val_ < 0);
}

int spin_unlock(Spinlock *spinlock)
{
  spinlock->val_ = 1;
}

#ifdef TEST
#include <stdio.h>
#include <pthread.h>
#include <signal.h>

FILE *fs;
Spinlock sp;

int run=1;

void* write_file_1(void *p)
{
  int time=0;

  while(run)
  {
    spin_lock(&sp);
    fprintf(fs, "%d ## thread 1\n", time);
    spin_unlock(&sp);
    ++time;
  }
  // printf("thread 1 exit\n");
}

void* write_file_2(void *p)
{
  int time = 0;

  while(run)
  {
    spin_lock(&sp);
    fprintf(fs, "%d ## thread 2 long string 0123456789\n", time);
    spin_unlock(&sp);
    ++time;
  }
  // printf("thread 2 exit\n");
}

static void* sig_thread (void *arg)
{
  sigset_t *set = arg;
  int s, sig;

  printf("sig thread pid: %d\n", getpid());

  for (;;)
  {
    s = sigwait (set, &sig);
    if (s == 0)
    {
      printf ("Signal handling thread got signal %d\n", sig);
      if (sig == SIGINT)
      {
        run = 0;
         break;
      }
    }
  }
}

int ret1, ret2;

int main(int argc, char *argv[])
{
  pthread_t thread0, thread1, thread;
  sigset_t set;

  sigemptyset (&set);
  sigaddset (&set, SIGQUIT);
  sigaddset (&set, SIGINT);
  int s = pthread_sigmask (SIG_BLOCK, &set, NULL);
  if (s != 0)
  {
    perror("pthread_sigmask");
    return -1;
  }

  spinlock_init(&sp);

  fs = fopen("/tmp/xyz1", "w");
  if (fs == NULL) 
  {
    perror("open fail");
    return -1;
  }

  pthread_create (&thread, NULL, &sig_thread, (void *) &set);
  pthread_create(&thread0, NULL, write_file_1, NULL);
  pthread_create(&thread1, NULL, write_file_2, NULL);

  pthread_join(thread0, &ret1);
  pthread_join(thread1, &ret2);
  fclose(fs);
  printf("test end\n");
  
  return 0;
}
#endif
