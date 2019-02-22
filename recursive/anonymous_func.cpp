// ref: https://zhuanlan.zhihu.com/p/51856257 十分鐘速通 Y Combinator
// rewrite by c++
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
  // lf 是一個 anonymous function
  int s = [] (auto lf, int n) -> int 
  {

    if (n == 0) 
      return 0;
    else
      return (lf(lf, n-1) + n);


  }
  (
    // lf 是一個 anonymous function, 以下就是傳入一個 anonymous function
    [] (auto lf, int n) -> int 
    {
      if (n == 0) 
        return 0;
      else
        return (lf(lf, n-1) + n);
    }
    ,
    10 // 第二個參數 n
  );

  cout << s << endl;
  return 0;
}

