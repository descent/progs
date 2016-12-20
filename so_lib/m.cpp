#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#include <dlfcn.h>


int main(int argc, char *argv[])
{
  
  void *f_handle;
  void (*func)(const char*);

  f_handle = dlopen("./libmylib.so.1.0.0", RTLD_LAZY);
  if (f_handle == NULL)
  {
    perror("dlopen fail\n");
    exit(1);
  }

  func = (void(*)(const char *))dlsym(f_handle,"print_str");

  if (func) 
  {
    func("abc");
  }
  dlclose(f_handle);

  return 0;
}
