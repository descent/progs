#include "spinlock.h"

#include <stdio.h>

static inline void atomic_add(int i, Atomic *v)
{
        unsigned long tmp;
        int result;

        __asm__ __volatile__("@ atomic_add\n"
"1:     ldrex   %0, [%3]\n"
"       add     %0, %0, %4\n"
"       strex   %1, %0, [%3]\n"
"       teq     %1, #0\n"
"       bne     1b\n"
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
  spinlock->val_ = 0;
}

int spin_lock(Spinlock *spinlock)
{
        unsigned long tmp;
        int result;

        __asm__ __volatile__("@ atomic_add\n"
"1:     ldrex   %0, [%3]\n"
"       cmp     %0, #1\n"
       "beq 1b\n"
       "mov %0, #1\n"
"       strex   %1, %0, [%3]\n"
"       teq     %1, #0\n"
"       bne     1b\n"
"dmb\n"
        : "=&r" (result), "=&r" (tmp), "+Qo"(spinlock->val_)
        : "r" (&spinlock->val_)
        : "cc");
}

int spin_unlock(Spinlock *spinlock)
{
  __asm__ __volatile__("dmb\n");
  spinlock->val_ = 0;
  __asm__ __volatile__("dsb\n");
}

#ifdef TEST
#include <pthread.h>
#include <signal.h>

FILE *fs;
Spinlock sp;
pthread_spinlock_t spinlock;

int run=1;

void* write_file_1(void *p)
{
  int time=0;
  pthread_t tid = pthread_self();

  while(run)
  {
#ifdef PTHREAD_FUNC
    pthread_spin_lock(&spinlock);
#else
    spin_lock(&sp);
#endif
    //printf("111\n");
    fprintf(fs, "%d ## thread 1 ## %d\n", time, tid);
    fprintf(fs, "%d ## thread 11\n", time);
    fprintf(fs, "%d ## thread 111\n", time);
#if 1
#ifdef PTHREAD_FUNC
    pthread_spin_unlock(&spinlock);
#else
    spin_unlock(&sp);
#endif
#endif
    ++time;
  }
  // printf("thread 1 exit\n");
}

void* write_file_2(void *p)
{
  int time = 0;
  pthread_t tid = pthread_self();

  while(run)
  {
#ifdef PTHREAD_FUNC
    pthread_spin_lock(&spinlock);
#else
    spin_lock(&sp);
#endif
    //printf("222\n");
    fprintf(fs, "%d ## thread 2 long string 0123456789 ## %d\n", time, tid);
    fprintf(fs, "%d ## thread 22 long string 0123456789\n", time);
    fprintf(fs, "%d ## thread 222 long string 0123456789\n", time);
#ifdef PTHREAD_FUNC
    pthread_spin_unlock(&spinlock);
#else
    spin_unlock(&sp);
#endif
    ++time;
  }
  // printf("thread 2 exit\n");
}

void* write_file_3(void *p)
{
  int time = 0;
  pthread_t tid = pthread_self();
  int i;

  while(run)
  {
#ifdef PTHREAD_FUNC
    pthread_spin_lock(&spinlock);
#else
    spin_lock(&sp);
#endif
    fprintf(fs, "%d ## thread 3 long string ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~ ## %d\n", time, tid);
    fprintf(fs, "%d ## thread 33 long string ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~\n", time);
    fprintf(fs, "%d ## thread 333 long string ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()~\n", time);
#ifdef PTHREAD_FUNC
    pthread_spin_unlock(&spinlock);
#else
    spin_unlock(&sp);
#endif
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
        //break;
      }
    }
  }
}

int ret1, ret2, ret3;

int main(int argc, char *argv[])
{
  pthread_t thread0, thread1, thread2, thread;
  sigset_t set;

#ifdef PTHREAD_FUNC
  pthread_spin_init(&spinlock, 0);
  printf("init pthread spinlock\n");
#else
  spinlock_init(&sp);
  printf("init my spinlock\n");
#endif

  sigemptyset (&set);
  sigaddset (&set, SIGQUIT);
  sigaddset (&set, SIGINT);
  int s = pthread_sigmask (SIG_BLOCK, &set, NULL);
  if (s != 0)
  {
    perror("pthread_sigmask");
    return -1;
  }


  printf("open %s to write\n", FN);
  fs = fopen(FN, "w");
  if (fs == NULL) 
  {
    perror("open fail");
    return -1;
  }

  pthread_create (&thread, NULL, &sig_thread, (void *) &set);
  pthread_create(&thread0, NULL, write_file_1, NULL);
  pthread_create(&thread1, NULL, write_file_2, NULL);
  pthread_create(&thread2, NULL, write_file_3, NULL);

  pthread_join(thread0, (void **)&ret1);
  pthread_join(thread1, (void **)&ret2);
  pthread_join(thread2, (void **)&ret3);

  fclose(fs);
  printf("test end\n");
  
  return 0;
}
#endif
