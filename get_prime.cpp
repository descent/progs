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
  if (i==0) return 2;
  int p=3;
  int c=1;
  while(1)
  { 
    if (is_prime(p) == true && c == i)
    {
      return p;
    }
    else
    {
      p = find_next_prime(p);
      ++c;
    }
  }
}


int main()
{
  for (int p=1 ; p < 20 ; ++p)
    cout << p << ": " << is_prime(p) << endl;
  int n=4;
  cout << "------" << endl;
  cout << n << ": " << get_prime(n) << endl;

  return 0;
}
