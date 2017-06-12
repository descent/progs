#include <cstdio>
using namespace std;

class A
{
  public:
    A()
    {
      k=1;
    }
    virtual void vf()
    {
      printf("k: %d\n", k);
    }
    int k;
  protected:
  private:
};

class B : public A
{
  public:
    B(): A()
    {
      h=2;
    }
    virtual void vf()
    {
      printf("h: %d\n", h);
    }
    int h;
  private:
};

int main(int argc, char *argv[])
{
  A *pa;  
  A a;
  B b;

  pa = &a;
  pa->vf();

  pa = &b;
  pa->vf();
  pa->h;
  return 0;
}
