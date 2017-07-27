#include <signal.h>
#include <pthread.h>

#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

volatile int i=5;

void thread_safe_func()
{
  pthread_mutex_lock(&mutex);

  for (int i=0 ; i < 200000 ; ++i)
    for (int i=0 ; i < 10000 ; ++i)
    {
    }
  i = 1;

  pthread_mutex_unlock(&mutex);
}

void sig_handle(int sig)
{
  thread_safe_func();
}

int main(int argc, char *argv[])
{
  signal(SIGINT, sig_handle);
  thread_safe_func();
  #if 0
  time_point<steady_clock> tp1 = steady_clock::now();


  time_point<steady_clock> tp2 = steady_clock::now();

  typedef duration<unsigned long long, ratio<1,1000000>> unit;
  unit d = duration_cast<unit>(tp2 - tp1);
  cout << d.count() << endl;
  #endif
  return 0;
}
