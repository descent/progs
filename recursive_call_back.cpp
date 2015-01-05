// ref: http://www.scheme.com/tspl4/further.html#./further:h4
#include <string>
#include <iostream>

// use function object, virtual function.

using namespace std;

//typedef void (*Recv)(string &a, string &b);
class Recv
{
  public:
    virtual void operator() (const string &num, const string &str)=0;
};

class Recv1:public Recv
{
  public:
    virtual void operator() (const string &num, const string &str)
    {
      cout << "num: " << num << endl;
      cout << "str: " << str << endl;
    }
  private:
    char next_char_;
    Recv *recv_;
};

class Recv2:public Recv
{
  public:
    Recv2(Recv *recv, char nc)
    {
      next_char_ = nc;
      recv_ = recv;
    }
    virtual void operator() (const string &num, const string &str)
    {
      string tmp_str;
      tmp_str.push_back(next_char_); 
#ifdef MORE_INFO
      std::cout << "next_char_:" << next_char_ << endl;
      std::cout << "num: " << num << endl;
      std::cout << "str: " << str << endl;
#endif

      if ('0' <= next_char_ && next_char_ <= '9')
      {
        string new_str = num + tmp_str;
        (*recv_)(new_str, str);
      }
      else // non num
      {
        string new_str = str + tmp_str;
        (*recv_)(num, new_str);
      }
    }
  private:
    char next_char_;
    Recv *recv_;
};

void extract(const string &s, Recv *receive)
{
  if (s.length() == 0)
  {
    string e1, e2;
    (*receive)(e1, e2);
  }
  else
  {
    Recv2 recv2(receive, s[0]);
    extract(s.substr(1), &recv2);
  }
}

void assemble(string &str)
{
  Recv1 recv1;
  extract(str, &recv1);
}

int main(int argc, char *argv[])
{
  string str="x51ca2yz";  

  cout << str << endl;
  assemble(str);
  return 0;
}
