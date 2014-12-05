/*
 * observe return a struct
 */
typedef struct Str_
{
  char c;
  int a;
}Str;

Str ret_str()
{
  Str str;

  str.c='a';
  str.a=1;

  return str;
}

int main(int argc, char *argv[])
{
  Str s;

  s = ret_str();

  s.c='c';
  s.a=5;
  
  return 0;
}
