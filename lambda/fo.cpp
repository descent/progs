#include <iostream>
using namespace std;

class aa
{
  public:
    aa(int x)
    {
      x_ = x;
    }
    int operator() (int y)
    {
      return x_+y;
    }
  private:
    int x_;
};

int main(int argc, char *argv[])
{
  aa aax(5); 

  cout << aax(6) << endl;
  return 0;
}
