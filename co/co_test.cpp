#include "gcc/coroutine.h"
#include <stdlib.h>
#include <stdio.h>

#define N 100

void function2(void* p)
{
   int i = 0;
   int a[ N ];
   for(i=0; i<N; ++i) a[ i ] = i*2;
   printf("      %s come...\n",p);
   printf("      %s pause...\n",p);
   co_pause();
   printf("      %s back...\n",p);
   printf("      %s has array\n",p);
   for(i=0; i<N; ++i)  printf("%d ",a[ i ]);
   printf("\n");
   printf("      %s terminated\n",p);
   co_terminate();
}


int printf(int a)
{
  a=1;
  return a;
}


void function1(void* p)
{
  char para[] = "Function2";
   Coroutine* co = co_create(function2, para);
   int i = 0;
   int a[ N ];
   for(i=0; i<N; ++i) a[ i ] = i;
   printf("   %s come...\n",p);
   printf("   %s pause...\n",p);
   co_pause();
   printf("   %s back...\n",p);
   co_resume( co );
   printf("   %s resume Function2...\n",p);
   co_resume( co );
   printf("   %s has array\n",p);
   for(i=0; i<N; ++i)  printf("%d ",a[ i ]);
   printf("\n");
   printf("   %s terminated\n",p);
   co_delete( co );
   co_terminate();
}

void MainCo(void* p)
{
  printf("MainCo para: %s\n", (char *)p);
  char para[] = "Function1";
   Coroutine* co = co_create(function1, para);
   int i = 0;
   int a[ N ];
   for(i=0; i<N; ++i) a[ i ] = 5*i;
   printf("%s come...\n",p);
   printf("%s pause...\n",p);
   co_pause();
   printf("%s back...\n",p);
   co_resume( co );
   printf("%s resume Function1...\n",p);
   co_resume( co );
   printf("%s has array\n",p);
   for(i=0; i<N; ++i)  printf("%d ",a[ i ]);
   printf("\n");
   printf("%s terminated\n",p);
   co_delete( co );
   co_terminate();
}

int main(){
  char para[] = "MainCo";
   Coroutine* co = co_create(MainCo, para);
   co_resume( co );
   co_resume( co );
   co_delete( co );
   return 0;
}
 
