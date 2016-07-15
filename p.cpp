#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  unsigned long ul=1234;
  long l=-12;
  unsigned int ui=5678;
  int i=-56;
  signed char c=0xf8;
  unsigned char uc=0xfa;

  printf("ul: %lu\n", ul); // unsigned long
  
  printf("x ul: %lx\n", ul); 

  printf("l: %ld\n", l); // long
  
  printf("x l: %lx\n", l);

  printf("ui: %u\n", ui);
  printf("i: %d\n", i);

  printf("uc: %x\n", uc);
  printf("x c: %x\n", c);
  printf("hhx c: %hhx\n", c); // signed char 負數時候要用 %hhx 印才正確

  cout << "cout ul: " << ul << endl;
  cout << "cout l: " << l << endl;

  cout << "cout ui: " << ui << endl;
  cout << "cout i: " << i << endl;

  cout << "cout uc: " << hex << +uc << endl;
  cout << "cout c: " << hex << +c << endl;

  return 0;
}
