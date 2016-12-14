#include <setjmp.h>
#include <string>
#include <map>

using namespace std;

map<string, jmp_buf> stack_frame;

void back_to_func(const string &fn)
{
  //jmp_buf frame =  stack_frame[fn];
  //stack_frame[fn];
  longjmp(stack_frame[fn], 5);
}

void f3()
{
  printf("in f3\n");
  back_to_func("f2");
}

void f2()
{
  jmp_buf frame; 
  int ret = setjmp(frame);
  if (ret == 0)
  {
    stack_frame.insert({"f2", frame});
    f3();
  }
  else
  {
    printf("back to f2\n");
    back_to_func("f1");
  }
}

void f1()
{
  jmp_buf frame; 
  int ret = setjmp(frame);
  if (ret == 0)
  {
    stack_frame.insert({"f1", frame});
    f2();
  }
  else
  {
    printf("back to f1\n");
    back_to_func("main");
  }
}

int main(int argc, char *argv[])
{
  jmp_buf frame; 
  int ret = setjmp(frame);
  if (ret == 0)
  {
    stack_frame.insert({"main", frame});
    f1(); 
  }
  else
  {
    printf("back to main\n");
  }
  printf("end main\n");
  return 0;
}
