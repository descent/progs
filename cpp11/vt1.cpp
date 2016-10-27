#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <typeinfo>

using namespace std;

void f1(int val)
{
  cout << "last type: " << typeid(val).name() << ", val: " << val << endl;
}

template<typename T, typename... Args>
void f1(T val, Args... args)
{
  cout << "type: " << typeid(val).name() << ", val: " << val << endl;
  return f1(args...);
}

int main(int argc, char *argv[])
{

  f1("ab", 0, 1, 2);
#if 0
  f1("%d\n", 1);  
  f1("%d %d\n", 1, 2);  
  f1("%d %d %s\n", 1, 2, "str");  
#endif
  return 0;
}
