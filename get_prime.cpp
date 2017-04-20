#include <cstdlib>
#include <iostream>
using namespace std;

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
  int n = 5;

  if (argc > 1)
  {
    n = strtol(argv[1], 0, 10);
  }
  for (int p=1 ; p < 20 ; ++p)
    cout << p << ": " << is_prime(p) << endl;
  cout << "------" << endl;
  cout << n << ": " << get_prime(n) << endl;

  return 0;
}
