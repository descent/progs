#include <string>
#include <cstdio>

using namespace std;

class Mystring
{
  public:
    friend Mystring operator+(const Mystring&, const Mystring&);
    Mystring(const char *s)
    {
      sprintf(str_, "%s", s);
    }
    ~Mystring()
    {
      printf("~Mystring: %s\n", str_);
      str_[0]='1';
      str_[1]=0x0;
    }
    operator const char*()
    {
      return str_;
    }
  private:
    char str_[100];
};

Mystring operator+(const Mystring &s1, const Mystring &s2)
{
  char str[100];
  sprintf(str,"%s%s", s1.str_, s2.str_);
  return Mystring(str);
}

int main(int argc, char *argv[])
{
  Mystring s1("123"), s2("abc"); 
  const char *p = s1+s2;
  printf("%s\n", p);
  return 0;
}
