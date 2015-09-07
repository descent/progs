#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef X64
#include "my_setjmp.h"
#define setjmp my_setjmp
#define longjmp my_longjmp
#else
#include <setjmp.h>
#endif

// #define BACKUP_STACK

int backup_stack_size;
unsigned char *stack_ptr1;
unsigned char *stack_ptr2;

unsigned char *stack_backup=0;


jmp_buf callee;
jmp_buf caller;

char *callee_stack;
char *caller_stack;


int gi=1;

void f2()
{
  char arr[1024];

  for (int i=0 ; i < 1024 ; ++i)
    arr[i] = i+5;
}

void f1()
{
  f2();
}

void f()
{
  f1();
}

void backup_cur_stack()
{
  unsigned char* p=0xffaabbcc;
  //stack_ptr2 = (unsigned char*)&p - sizeof(unsigned char*) +8;
  stack_ptr2 = (unsigned char*)&p + sizeof(unsigned char*); // is ok
  // stack_ptr2 = (unsigned char*)&p; // not ok
  backup_stack_size = stack_ptr1 - stack_ptr2;
  stack_backup = malloc(backup_stack_size);
  if (stack_backup)
  {
    memcpy(stack_backup, stack_ptr2, backup_stack_size);
  }
  else
    stack_backup = 0;
}

void co1()
{
  // int arb[50];
  int i=2;
  // int are[50];

  printf("i (%p): %d\n", &i, i);
  // pause
  if (setjmp(callee) == 0)
  {
#ifdef BACKUP_STACK
    // backup current stack context
    backup_cur_stack();
#endif
    longjmp(caller, 1);
  }
  else
  {
#ifdef BACKUP_STACK
    // restore stack
    memcpy(stack_ptr2, stack_backup, backup_stack_size);
#endif
  }

  printf("xxx i (%p): %d\n", &i, i);
  i=3;

#if 1
  gi = i;
  // pause
  if (setjmp(callee) == 0)
    longjmp(caller, 1);

  i=4;
#endif
}


void co_top()
{
  unsigned char* p;
  //printf("sizeof: %d\n", sizeof(unsigned char*));
  stack_ptr1 = (unsigned char*)&p;
  co1();
}

int main(int argc, char *argv[])
{
  int a=1;

  callee_stack = (char *) malloc(1024);
  caller_stack = (char *) malloc(1024);

  a=3;

#if 0
  asm volatile ( 
                 "movl %0, %%esp"
                 :
                 :"r"(callee_stack)
               );
#endif
  // resume
  if (setjmp(caller) == 0)
    co_top();

  a=10;
  f();
  f();
  f();
  f();
  f();
  f();

  // resume
  if (setjmp(caller) == 0)
  {
    longjmp(callee, 1);
  }

  a=5;
#if 0

  // resume
  if (setjmp(caller) == 0)
    longjmp(callee, 1);

  a=6;
#endif  
  printf("gi: %d\n", gi);
  return 0;
}
