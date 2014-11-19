#include "queue.h"

#include <cstdio>

using namespace std;

#include <pthread.h>
#include <unistd.h>
#include <signal.h>

Queue q(30);

int push1_end=1;
int push2_end=1;
int pop1_end=1;
int pop2_end=1;

void *push1(void *arg)
{
  while(push1_end)
  {
    if (q.push('1') == false)
    {
      sleep(1);
    }
  }
}

void *push2(void *arg)
{
  while(push2_end)
  {
    if (q.push('2') == false)
    {
      sleep(1);
    }
  }
}

void *pop1(void *arg)
{
}

void *pop2(void *arg)
{
}


static void* sig_thread(void *arg)
{
  sigset_t *set = (sigset_t *)arg;
  int s, sig;

  //create_pid_file();
  for (;;)
  {
    s = sigwait(set, &sig);
    if (s != 0)
      printf("sigwait fail\n");

    printf("Signal handling thread got signal %d\n", sig);
    if (sig == SIGUSR1)
    {
      printf("===\n");
      q.print();
      printf("===\n");
    }
    if (sig == SIGTERM)
    {
      push1_end = push2_end = pop1_end = pop2_end = 0;
    }
  }
}

int main(int argc, char *argv[])
{

  sigset_t singlas_to_block;

  sigemptyset(&singlas_to_block);
  sigaddset(&singlas_to_block, SIGUSR1);
  sigaddset(&singlas_to_block, SIGTERM);
  if (pthread_sigmask(SIG_BLOCK, &singlas_to_block, NULL) != 0)
  {
    printf("pthread_sigmask fail!!\n");
    return -1;
  }

  pthread_t sig_th;

  pthread_create(&sig_th, NULL, &sig_thread, (void *) &singlas_to_block);
  pthread_t thread[4];

  pthread_create(&thread[0], NULL, push1, NULL);
  pthread_create(&thread[1], NULL, push2, NULL);
  //pthread_create(&thread[2], NULL, pop1, NULL);
  //pthread_create(&thread[3], NULL, pop2, NULL);

  pthread_join(thread[0], NULL);
  //pthread_join(thread[1], NULL);
  //pthread_join(thread[2], NULL);
  //pthread_join(thread[3], NULL);
  
  return 0;
}
