#include <cstdio>

using namespace std;

void func1(int i, int j)
{
  if (j > 9)
  {
    return;
  }
  else
  {
    printf("%2d *%2d = %2d\n",i, j, i*j);
    func1(i, j+1);
  }
}

void func(int i, int j)
{
  if (i > 9)
  {
    return;
  }
  else
  {
    printf("%2d *%2d = %2d\n",i, j, i*j);
    func1(i, j+1);
    func(i+1, j);
  }
}

int main(int argc, char *argv[])
{
  func(1, 1);
  return 0;
}
