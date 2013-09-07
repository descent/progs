#include <iostream>
#include <cstdio>
 
using namespace std;
 
struct A 
{
  virtual void func() 
  {
    printf("i: %d\n", i_);
  }
  A()
  {
    i_=10; 
  }
  private:
    int i_;
};
 
struct B
{
  virtual void ff() 
  {
    printf("i: %d\n", i_);
  }
  B()
  {
    i_=10; 
  }
  private:
    int i_;
};

struct AB : public A, public B
{
  virtual void func() 
  {
    printf("i am ab\n");
  }
  virtual void ff() 
  {
    printf("i am ab ff\n");
  }
};
 
int main()
{
  void (AB::*p)() = &B::ff;
  AB ab;
  (ab.*p)();

  return 0;
}
