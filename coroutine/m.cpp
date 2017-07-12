#include <cstdio>
#include <algorithm>

#include "coroutine.h"

using namespace std;

#define W 10
#define H 5 

int result[100]{0,1,1};

int fibonacci(int max)
{
  int n, i, n_2=0, n_1=1, fib;

  while (n < max)
  {
    printf("%d\n", fib);
  }
  if (n == 0)
            fib = n_2;
 
        else if (n == 1)
            fib = n_1;
 
        else{
 
            for (i=2; i<=n; i++) {
                fib = n_2 + n_1;
                n_2 = n_1;
                n_1 = fib;
            }
 
            n_2 = 0;
            n_1 = 1;
 
        }

}

#if 0
int fibonacci(int n)
{
  if (1 == n)
    return 1;
  if (2 == n)
    return 1;
  for (int i=3 ; i <= n; ++i)
  {
    result[i] = result[i-1] + result[i-2];
  }
  return result[n];
}
#endif

int func()
{
  static int j=0;
  static int i=0;
  scrBegin;
  //usleep(us);
  //system("clear");
  //printf("\n\n");
  for ( ; j < H ; ++j)
  {
    for ( ; i < W ; ++i)
    {
    }
    printf("aa i: %d, j: %d\n", i, j);
    scrReturnV;
    printf("zz i: %d, j: %d\n", i, j);
  }
  printf("00 i: %d, j: %d\n", i, j);
  scrFinishV(-1);
  printf("11 i: %d, j: %d\n", i, j);
}

int main(int argc, char *argv[])
{
#if 1
  int ret;
  for (int i=0 ; i < 10 ; ++i)
  {
    ret = func();
    printf("%d, ret: %d ============\n", i, ret);
  }
#endif  

#if 0
  int n=6;
  int r = fibonacci(n);
  //printf("fib(%d): %d\n", n, r);
#endif
  return 0;
}
