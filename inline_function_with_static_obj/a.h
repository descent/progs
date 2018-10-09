#ifndef A_H
#define A_H

#include <cstdio>

using namespace std;

class A
{
  public:
    A()
    {
      printf("A\n");
    }
  private:
};

inline A *get_obj()
{
  static A a; 
  
  return &a;
}
#endif
