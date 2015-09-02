// ref: http://www.di.unipi.it/~nids/docs/longjump_try_trow_catch.html
#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

#define TRY do { switch((ex_code = setjmp(ex_buf__))) { case 0:
#define CATCH(x) break; case x : 
#define ETRY break; } } while(0);
#define THROW(x) longjmp(ex_buf__, x)

jmp_buf ex_buf__; 

void *mymalloc(size_t size)
{
  static int t;
  void *mem = malloc(size);
  if (t >= 2)
    mem = NULL;
  if (mem == NULL)
    longjmp(ex_buf__, 1); // THROW
  ++t;
  return mem;
}

int f1()
{
  int ex_code = 0;
  do
  { 
    switch((ex_code = setjmp(ex_buf__)))
    { 
      case 0: // TRY
      {
        printf("In Try Statement\n");
        
        char *mem = (char *)mymalloc(32);
        mem = (char *)mymalloc(32);
        mem = (char *)mymalloc(32);
        printf("I do not appear\n");
      }

      break; 
      case 1 : // CATCH(x)
      {
        printf("mem alloc fail! %d\n", ex_code);
      }

      break; 
      case 5 : // CATCH(x)
      {
        printf("Got Exception! %d\n", ex_code);
      }

      break; 
    }
  } while(0); // ETRY

  return 0;
}

int f2()
{
  int ex_code = 0;
      TRY
      {
        printf("In Try Statement\n");
        
        THROW(5);
        printf("I do not appear\n");
      }
      CATCH(1)
      {
        printf("Got Exception! %d\n", ex_code);
      }
      CATCH(5)
      {
        printf("Got Exception! %d\n", ex_code);
      }
      ETRY

  return 0;
}

int main(int argc, char *argv[])
{
  f1(); 
  f2(); 
  return 0;
}
