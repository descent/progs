#include <iostream>
#include <tuple>
using namespace std;

auto f()                              
{
  return std::make_tuple(1,2.3,"456");
}

int main(int argc, char *argv[])
{
  auto [x,y,z] = f();

  cout << "x: " << x << endl;
  cout << "y: " << y << endl;
  cout << "z: " << z << endl;
  return 0;
}
