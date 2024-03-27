#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <execinfo.h>

#define BT_BUF_SIZE 100

void print_backtrace() 
{
    void *buffer[BT_BUF_SIZE];
    char **strings;
    int nptrs;

    nptrs = backtrace(buffer, BT_BUF_SIZE);
    printf("backtrace() returned %d addresses\n", nptrs);

    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL) {
        perror("backtrace_symbols");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nptrs; i++) {
        printf("xx %s\n", strings[i]);
    }

    free(strings);
}

void f5()
{
  printf("in f5\n");
  print_backtrace();
}


#include <stdio.h>

uintptr_t get_rip_value() 
{
  //uintptr_t rip_value;
  //asm volatile("movq $0, %%rax; movq (%%rsp), %%rax" : "=a" (rip_value));
  //asm("mov %%rip, %0" : "=r" (rip_value));
  uintptr_t current_address;
  asm("lea (%%rip), %0" : "=r" (current_address));
  return current_address;
}

unsigned long get_rbp()
{
  unsigned long rbp_value;
  asm("movq %%rbp, %0" : "=r" (rbp_value));
  printf("The value of RBP register is: %#lx\n", rbp_value);
  return rbp_value;
}

int addr2func(uintptr_t addr)
{
  char cmd[128] = {0};
  sprintf(cmd, "addr2line -f -e t2 %#lx\n", addr);
  printf("cmd: %s\n", cmd);
  system(cmd);
  return 0;
}

void f3()
{
  print_backtrace();
  #if 1
  int level = 0;
  printf("in f3\n");
  //while(1)
  {
    {
      uintptr_t current_address;
      asm("lea (%%rip), %0" : "=r" (current_address));
      printf("current_address : %#lx\n", current_address);
      addr2func(current_address);

      printf("======\n");

      unsigned long rbp_value, previous_rbp;
      asm("movq %%rbp, %0" : "=r" (rbp_value));
      printf("%d ## The value of RBP register is: %#lx\n", level, rbp_value);
      ++level;

      uintptr_t ret_addr = *(uintptr_t*)(rbp_value + sizeof(uintptr_t));
      printf("ret_addr : %#lx\n", ret_addr);

      addr2func(ret_addr);

      printf("======\n");

      rbp_value = *(uintptr_t*)(rbp_value);
      printf("%d ## The value of RBP register is: %#lx\n", level, rbp_value);
      ++level;

      ret_addr = *(uintptr_t*)(rbp_value + sizeof(uintptr_t));
      addr2func(ret_addr);


      printf("======\n");

      rbp_value = *(uintptr_t*)(rbp_value);
      printf("%d ## The value of RBP register is: %#lx\n", level, rbp_value);
      ++level;

      ret_addr = *(uintptr_t*)(rbp_value + sizeof(uintptr_t));
      addr2func(ret_addr);

      printf("======\n");

      rbp_value = *(uintptr_t*)(rbp_value);
      printf("%d ## The value of RBP register is: %#lx\n", level, rbp_value);
      ++level;

      ret_addr = *(uintptr_t*)(rbp_value + sizeof(uintptr_t));
      addr2func(ret_addr);

      printf("======\n");

      previous_rbp = rbp_value;
      
      rbp_value = *(uintptr_t*)(rbp_value);
      printf("%d ## The value of RBP register is: %#lx, previous_rbp: %#lx\n", level, rbp_value, previous_rbp);
      ++level;

      if (rbp_value > previous_rbp)
      {
        ret_addr = *(uintptr_t*)(rbp_value + sizeof(uintptr_t));
        addr2func(ret_addr);
      }
      else
      {
        printf("top stack frame\n");
      }

      printf("======\n");


    void* frame_address = __builtin_frame_address(0);
    if (frame_address)
      printf("Frame 0 address of f3: %p\n", frame_address);

    void* return_address = __builtin_return_address(0);
    if (return_address)
      printf("Return 0 address of f3: %p\n", return_address);
    }

#if 1
    {
    void* frame_address = __builtin_frame_address(1);
    if (frame_address)
      printf("Frame 1 address of f3: %p\n", frame_address);

    void* return_address = __builtin_return_address(1);
    if (return_address)
      printf("Return 1 address of f3: %p\n", return_address);
    }

    {
    void* frame_address = __builtin_frame_address(2);
    if (frame_address)
      printf("Frame 2 address of f3: %p\n", frame_address);

    void* return_address = __builtin_return_address(2);
    if (return_address)
      printf("Return 2 address of f3: %p\n", return_address);
    }
#endif
#if 0
    {
    void* frame_address = __builtin_frame_address(3);
    if (frame_address)
      printf("Frame 3 address of f2: %p\n", frame_address);

    void* return_address = __builtin_return_address(3);
    if (return_address)
      printf("Return 3 address of f2: %p\n", return_address);
    }
#endif

  }
#endif

#if 0
  printf("in f2\n");
  f3();
#endif
}

void f2()
{
  printf("in f2\n");
  f3();
}

void f1()
{
  printf("in f1\n");
  f2();
}

int main(int argc, char *argv[])
{
  f1(); 
  printf("main: %p\n", main);
  printf("f1: %p\n", f1);
  printf("f2: %p\n", f2);
  #if 0
  printf("f3: %p\n", f3);
  printf("f5: %p\n", f5);
  #endif
  return 0;
}
