#include <iostream>
#include <cstdio>
 
using namespace std;
 
struct A 
{
  virtual void func() 
  {
    printf("i: %d\n", i_);
  }
  virtual void abc() 
  {
    printf("abc i: %d\n", i_);
  }
  A()
  {
    i_=10; 
  }
  private:
    int i_;
};
 

int main()
{
  void (A::*p)() = &A::abc;
  A a;
  (a.*p)();

  return 0;
}
