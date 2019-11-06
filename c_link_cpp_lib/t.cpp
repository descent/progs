#include "t.h"

#include <cstdio>
using namespace std;

Hello::Hello()
{
  val_ = 5;
  printf("ctor hello\n");
}

Hello::~Hello()
{
  printf("dtor hello\n");
}


