/*
 * observe return a struct
 */

#include <stdio.h>

struct Str
{
  Str(char cc, int aa)
  {
    c = cc;
    a = aa;
    printf("str\n");
  }
  Str(const Str &s)
  {
    //c = s.c;
    //a = s.a;
    printf("cc\n");
  }
#if 0
  Str operator=(const Str &s)
  {
    c = s.c;
    a = s.a;
    printf("dd\n");
    return *this;
  }
#endif
  char c;
  int a;
};

Str ret_str()
{
  Str str('q', 2);

  //str.c='a';
  //str.a=1;
  printf("1\n");

  return str;
}

int main(int argc, char *argv[])
{
  //Str s(ret_str());
  Str s = ret_str();
  printf("s.c: %c\n", s.c);
  //ret_str();

  //s.c='c';
  //s.a=5;
  
  return 0;
}
