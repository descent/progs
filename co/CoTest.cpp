// Coroutine.cpp : 定義主控台應用程式的進入點。
//
#pragma warning( disable : 4611 4530 4311)
#include "Coroutine.h"
#include <stdlib.h>
#include <stdio.h>

#define N 100

void __stdcall function2(void* p)
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

void __stdcall function1(void* p)
{
   Coroutine* co = co_create(function2,"Function2");
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

void __stdcall MainCo(void* p)
{
   Coroutine* co = co_create(function1,"Function1");
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
   Coroutine* co = co_create(MainCo,"MainCo");
   co_resume( co );
   co_resume( co );
   co_delete( co );
   return 0;
}
 