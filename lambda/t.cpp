// ref: http://kheresy.wordpress.com/2010/05/27/c0x%EF%BC%9Alambda-expression/
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <typeinfo>
#include<functional>

using namespace std;

typedef void (*Recv)(const string &n, const string &s);

//template<typename Func>
//void extract(const string &str, Func receive)
void extract(const string &str, std::function<void(const string&, const string&)> receive)
{
  if (str.length() == 0)
  { 
    string e1, e2;
    receive(e1, e2);
  }
  else
  {
    // ref: http://www.cnblogs.com/ttss/p/4100917.html
    // std::function<int(int ,int)>func=add;
    //   <int(int,int)>是实例化模板参数,表示返回值为int,函数参数为2个,(int,int),
    //   即int(*pfunc)(int ,int )类型的函数
    std::function<void(const string&, const string&)> f1 = [&](const string &n, const string &s)
    { 
      char next_ch = str[0];
      string tmp_str;

      tmp_str.push_back(next_ch);

#ifdef MORE_INFO
      cout << "n: " << n << endl;
      cout << "s: " << s << endl;
      cout << "next_ch: " << next_ch << endl;
#endif

      if ('0' <= next_ch && next_ch <= '9')
      {
        string new_str = n + tmp_str;
#ifdef MORE_INFO
        cout << "new_str: " << new_str << endl;
        cout << "===========" << endl;
#endif
        receive(new_str, s);
      }
      else
      {
        string new_str = s + tmp_str;
#ifdef MORE_INFO
        cout << "new_str: " << new_str << endl;
        cout << "===========" << endl;
#endif
        receive(n, new_str);
      }
    };

    extract(str.substr(1), f1);
  }
}

void assemble(string &str)
{
  extract(str, 
          [] (const string &n, const string &s) 
          { 
            cout << n << endl;
            cout << s << endl;
          }
         );
}

int main(int argc, char *argv[])
{
  auto func = [&] (const string &n, const string &s) 
  { 
    cout << n << endl;
    cout << s << endl;
  };

  string str="x51ca2yz";
  cout << str << endl;
  //extract(str, func);
  assemble(str); 
  return 0;
}
