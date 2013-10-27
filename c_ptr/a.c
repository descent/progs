#include <stdio.h>

int main(int argc, const char *argv[])
{
  int op[3][4]={1,2,3,4, 5,6,7,8, 11,22,33,44};
  int (*pop)[4]=op;
  int (*pop1)[4]=&op[0];
  int (*pop2)[4]=&op[1];
  int (*pop3)[4]=&op[2];

  pop2++;
  for (int i=0 ; i < 4; ++i)
    printf("(*pop2)[%d]: %d\n", i, (*pop2)[i]);

    ++pop;
  for (int i=0 ; i < 4; ++i)
  {
    printf("(*pop)[%d]: %d\n", i, (*pop)[i]);
  }
        
  return 0;
}
