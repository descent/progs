#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>

#include "coroutine.h"

using namespace std;

#define W 10
#define H 5 

#define X(x) "\x1b[xA"
#define Y(y) "\x1b[yC"

void x(int x)
{
  cout << "\x1b[" << x << "A";
}

void y(int y)
{
  cout << "\x1b["<< y << "C";
}

void xy(int x, int y)
{
  cout << "\x1b[" << x << ";" << y << "H";
}

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

static int count;
int task2();

int task1()
{
  xy(1,1);
  cout << "*" << endl;
  task2();
  usleep(100000);
  xy(1,1);
  cout << " " << endl;
  usleep(100000);
}

int task2()
{
  scrBegin;

  xy(3,3);
  cout << "*" << endl;

  scrReturnV;

  xy(3,3);
  cout << " " << endl;


  scrLine=0;
  scrFinishV(-1);

}

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
  system("clear");
#if 1
  int i;
  while(1)
  {
  //task2();
  //cin >> i;
    task1();
    //task2();
  }
#endif
#if 0
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
