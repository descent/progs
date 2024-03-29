#include <signal.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdint.h>

//#define _GNU_SOURCE
#include <unistd.h>

#include <unistd.h>
#include <sys/syscall.h>

#ifndef SYS_gettid
#error "SYS_gettid unavailable on this system"
#endif

#define gettid() ((pid_t)syscall(SYS_gettid))

/* Simple error handling functions */

#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#include <execinfo.h>

#if 1
#define BT_BUF_SIZE 100

int addr2func(uintptr_t addr)
{
  char cmd[128] = {0};
  sprintf(cmd, "addr2line -f -e ./t1 %#lx\n", addr);
  printf("cmd: %s\n", cmd);
  system(cmd);
  return 0;
}

#if 1
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

#endif

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

    for (int i = 0; i < nptrs; i++) 
    {
      char cmd[128]={0};
      printf("nn %s\n", strings[i]);
      addr2func( (uintptr_t)buffer[i]);
      #if 0
      //printf("aa %#x\n", buffer[i]);
      sprintf(cmd, "/usr/bin/addr2line -f -e ./t123 %p\n", buffer[i]);
      //printf("cmd: %s\n", cmd);
      FILE *fs = popen(cmd, "r");
      if (fs)
      {
        char data[128];
        fread(data, 1, 128, fs);
        printf("data: %s\n", data);
      }
      pclose(fs);
      #endif
      

    }

    free(strings);
}
#else


#if 0
#define UNW_LOCAL_ONLY
#include <libunwind.h>
#endif



void print_backtrace() {
    unw_cursor_t cursor;
    unw_context_t context;

    // 获取当前线程的上下文
    unw_getcontext(&context);
    // 初始化游标以便从当前位置开始遍历堆栈帧
    unw_init_local(&cursor, &context);

    // 遍历堆栈帧
    while (unw_step(&cursor) > 0) {
        unw_word_t offset, pc;
        char sym[256];

        // 获取指令指针位置
        unw_get_reg(&cursor, UNW_REG_IP, &pc);
        // 获取调用指令的偏移量
        unw_get_proc_name(&cursor, sym, sizeof(sym), &offset);

        printf("  0x%lx: (%s+0x%lx)\n", (long)pc, sym, offset);
    }
}

#endif

void sig_handler(int signo) 
{
  int level = 0;
  printf("in sig_handler\n");
  #if 1

  //printf ("Caller name: %p\n", __builtin_return_address(0));
  print_backtrace();

  #if 1
  printf("in sig_handler pid: %d\n", getpid());
  printf("in sig_handler tid: %d\n", gettid());
  if (signo == SIGINT)
    printf("Received SIGINT\n");
  #endif
  #endif
  #if 1
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
    #endif
}

static void * sig_thread (void *arg)
{
  sigset_t *set = arg;
  int s, sig;

  printf("sig thread pid: %d\n", getpid());

  for (;;)
    {
      s = sigwait (set, &sig);
      if (s != 0)
 handle_error_en (s, "sigwait");
      printf ("Signal handling thread got signal %d\n", sig);
    }
    return 0;
}

static void fun_123(void *arg)
{
  sigset_t *set = arg;
  int s, sig;
  printf("123 thread pid: %d\n", getpid());
  printf("123 thread tid: %d\n", gettid());

  while(1)
  {
    //printf("123\n");
    
 
#if 0 
   for (;;)
     {
       s = sigwait (set, &sig);
       if (s != 0)
         handle_error_en (s, "sigwait");
       printf ("Signal handling thread got signal %d\n", sig);
       print_backtrace();
     }
#endif
  }
}

static void fun_12(void *arg)
{
  fun_123(arg);
}

static void * fun_1(void *arg)
{
  //for (;;)
  {
    fun_12(arg);
  #if 0
    printf("11 sig thread pid: %d\n", getpid());
    printf("11 sig thread tid: %d\n", gettid());
  #endif
  }
  return 0;
}

static void fun_223()
{
  while(1)
  {
    //printf("223\n");
  }
}

static void fun_22()
{
  fun_223();
}

static void * fun_2(void *arg)
{
  struct sched_param schedp;

  memset(&schedp, 0, sizeof(schedp));
  schedp.sched_priority = 39;
  sched_setscheduler(0, SCHED_RR, &schedp);

  for (;;)
  {
    fun_22();
  #if 0
    printf("22 sig thread pid: %d\n", getpid());
    printf("22 sig thread tid: %d\n", gettid());
  #endif
  }
  return 0;
}

int main(int argc, char *argv[])
{
  //pthread_t thread;
  pthread_t thread_1;
  //pthread_t thread_2;

  //printf ("Caller name: %p\n", __builtin_return_address(0));
  printf("main: %p, fun_1: %p, fun_2: %p\n", main, fun_1, fun_2);


  struct sigaction sa;
  sa.sa_handler = sig_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;

  //signal(SIGUSR1, sig_handler);


#if 1
    //if (sigaction(SIGINT, &sa, NULL) == -1) {
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
#endif
  sigset_t set;
  int s;

  /* Block SIGQUIT and SIGUSR1; other threads created by main()
     will inherit a copy of the signal mask. */

  printf("pid: %d\n", getpid());

#if 0
  sigemptyset (&set);
  //sigaddset (&set, SIGQUIT);
  sigaddset (&set, SIGUSR1);
  s = pthread_sigmask (SIG_BLOCK, &set, NULL);
  if (s != 0)
    handle_error_en (s, "pthread_sigmask");
#endif

#if 0
  s = pthread_create (&thread, NULL, &sig_thread, (void *) &set);
  if (s != 0)
    handle_error_en (s, "pthread_create");
#endif

  s = pthread_create (&thread_1, NULL, &fun_1, (void *) &set);
  if (s != 0)
    handle_error_en (s, "pthread_create 1");

#if 0
  s = pthread_create (&thread_2, NULL, &fun_2, (void *) &set);
  if (s != 0)
    handle_error_en (s, "pthread_create 2");

  /* Main thread carries on to create other threads and/or do
     other work */
#endif
  //pause();
  while(1)
  {
    printf("main thread pid: %d\n", getpid());
    printf("main thread tid: %d\n", gettid());
    fun_22();
    #if 0
    printf("main thread pid: %d\n", getpid());
    printf("main thread tid: %d\n", gettid());
    #endif
  }
  //pause ();   /* Dummy pause so we can test program */
}
