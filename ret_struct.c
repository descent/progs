#include <stdio.h>

typedef struct Data_
{
  int a;
  int b;
  char ch;
}Data;

Data ret_data()
{
  Data d;

  d.a=100;
  d.b=200;
  d.ch = 'a';

  return d;
}

int main(int argc, char *argv[])
{
  Data da = ret_data(); 
  da.a=101;
  return 0;
}
