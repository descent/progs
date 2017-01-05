#include <functional>
#include <iostream>
using namespace std;

#if 0
// http://matt.might.net/articles/by-example-continuation-passing-style/
function fact(n,ret) {
  if (n == 0)
    ret(1) ;
  else
    fact(n-1, function (t0) {
     ret(n * t0) }) ;
}


fact (5, function (n) { 
  console.log(n) ; // Prints 120 in Firebug.
})
#endif
int fact(int n, function<int(int)> ret)
{
  if (n == 0)
    return ret(1) ;
  else
  {
    return fact(n-1, [&] (int t0) -> int {return ret(n*t0);}) ;
  }
}

int main(int argc, char *argv[])
{
  int val=5;
  cout << "cps fact: " << val << endl;
  fact(val, [](int n) -> int {cout << n << endl;return 0;});
   
  return 0;
}
