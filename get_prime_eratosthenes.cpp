#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define N 50

// int primes[N];

vector<int> primes;
vector<int> tmp;

int cap = 10;
int cur_div;

int get_prime(const vector<int> &vec, int n)
{
  int count=0;
  for (int i=0 ; i < vec.capacity() ; ++i)
  {
    if (vec[i] == 1)
    {
      if (n == count)
        return vec[i];
      ++count;
    }
  }
}

void resize_primes(vector<int> v, int set_cap)
{
  int old_cap = v.capacity();
  cap = set_cap;
  primes.reserve(set_cap);
  primes.resize(set_cap);
  for (int i=old_cap ; i < primes.capacity() ; ++i)
    primes[i] = 1;
}

void init_primes()
{
  primes.reserve(cap);
  primes.resize(cap);
  //memset(primes, 1, N*sizeof(int));

  for (int i=0 ; i < primes.capacity() ; ++i)
    primes[i] = 1;
 
#if 0
  for (int i=0 ; i < N ; ++i)
    primes[i] = 1;
#endif
}

void print_primes()
{
  for (int i=2 ; i < primes.capacity() ; ++i)
  {
    if (primes[i] == 1)
      cout << i << ", ";
  }
  cout << endl;
}

#if 0
// eratosthenes ref: http://openhome.cc/Gossip/AlgorithmGossip/EratosthenesPrime.htm
void eratosthenes(int *p, int len, int begin)
{
  if (begin > len-1)
    return;
  else
  {
    for (int i=2 ; begin*i < len-1 ; ++i)
    {
      primes[begin*i] = 0;
    }
    eratosthenes(primes, N, begin+1);
  }
}
#endif

void eratosthenes(vector<int> &vec, int begin)
{
  int len = vec.capacity();

  if (begin > len-1)
  {
    cur_div = begin;
    return;
  }
  else
  {
    for (int i=2 ; begin*i < len ; ++i)
    {
      vec[begin*i] = 0;
    }
    eratosthenes(primes, begin+1);
  }
}

bool is_prime(int p)
{
  if (p == 1) return false;
  if (p == 2 || p == 3)
    return true;
  for (int i=2 ; i <= (p/2+1) ; ++i)
  {
    if (p%i == 0)
      return false;
  } 
  return true;
}

int find_next_prime(int p)
{
  int next_p = p+1;
  while(is_prime(next_p) != true)
  {
    ++next_p;
  }
  return next_p;
}

int get_prime(int i)
{
  int p = 1;
  int c = -1;
  while(1)
  { 
    p = find_next_prime(p);
    ++c;
    if (c == i)
      return p;
  }
  return 1; // means fail
}


int main(int argc, char *argv[])
{
#if 1
  init_primes();
  print_primes();
  eratosthenes(primes, 2);
  //primes[2]=1;
  print_primes();
  cout << "cap: " << cap << ", cur_div: " << cur_div << endl;


  resize_primes(primes, 100);
  eratosthenes(primes, 2);

  print_primes();
  cout << "cap: " << cap << ", cur_div: " << cur_div << endl;
#endif

#if 0
  int n = 5;

  if (argc > 1)
  {
    n = strtol(argv[1], 0, 10);
  }
  for (int p=1 ; p < 20 ; ++p)
    cout << p << ": " << is_prime(p) << endl;
  cout << "------" << endl;
  cout << n << ": " << get_prime(n) << endl;
#endif
  return 0;
}
