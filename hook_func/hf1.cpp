// ref: http://www.cnblogs.com/catch/p/3604516.html
// hook __gxx_personality_v0
#include <execinfo.h>
#include <dlfcn.h>
#include <cxxabi.h>
#include <unwind.h>

#include <iostream>
#include <cstdio>
using namespace std;

void test_func1();

typedef _Unwind_Reason_Code (*personality_func) (int version, _Unwind_Action actions, _Unwind_Exception_Class exception_class, struct _Unwind_Exception *ue_header, struct _Unwind_Context *context);
static personality_func gs_gcc_pf = NULL;


static void hook_personality_func()
{
    gs_gcc_pf = (personality_func)dlsym(RTLD_NEXT, "__gxx_personality_v0");
}

static int print_call_stack()
{
   printf("xxx\n");
}

extern "C" _Unwind_Reason_Code
__gxx_personality_v0 (int version,
              _Unwind_Action actions,
              _Unwind_Exception_Class exception_class,
              struct _Unwind_Exception *ue_header,
              struct _Unwind_Context *context)
{
  printf("my person\n");
    _Unwind_Reason_Code code = gs_gcc_pf(version, actions, exception_class, ue_header, context);

    if (_URC_HANDLER_FOUND == code)
    {
        //找到了catch所有的函数

        //当前函数内的指令的地址
        void* cur_ip = (void*)(_Unwind_GetIP(context));
      
        Dl_info info;
        if (dladdr(cur_ip, &info))
        {
             if (info.dli_saddr == &test_func1)
             {
                 // 当前函数是目标函数
                 print_call_stack();
             }
        }
    }

    return code;
}


void test_func3()
{
    char* p = new char[2222222222222];
    cout << "test func3" << endl;
}

void test_func2()
{
    cout << "test func2" << endl;
    try
    {
        test_func3();
    }
    catch (int)
    {
        cout << "catch 2" << endl;
    }
}

void test_func1()
{
    cout << "test func1" << endl;
    try
    {
        test_func2();
    }
    catch (...)
    {
        cout << "catch 1" << endl;
    }
}


int main()
{
    hook_personality_func();

    test_func1();

    return 0;
}
