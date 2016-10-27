// ref: http://www.cnblogs.com/catch/p/3604516.html
#include <execinfo.h>
#include <dlfcn.h>
#include <cxxabi.h>
#include <unwind.h>

#include <iostream>
using namespace std;

void test_func1();
//static personality_func gs_gcc_pf = NULL;
static _Unwind_Personality_Fn gs_gcc_pf = NULL;

#if 0
/usr/lib/gcc/x86_64-linux-gnu/5/include/unwind.h
typedef _Unwind_Reason_Code (*_Unwind_Personality_Fn)
     (int, _Unwind_Action, _Unwind_Exception_Class,
      struct _Unwind_Exception *, struct _Unwind_Context *);
#endif

static void hook_personality_func()
{
    gs_gcc_pf = (_Unwind_Personality_Fn)dlsym(RTLD_NEXT, "__gxx_personality_v0");
}

static int print_call_stack()
{
  cout << "dump stack" << endl;
   //to do.
}

extern "C" _Unwind_Reason_Code
__gxx_personality_v0 (int version,
              _Unwind_Action actions,
              _Unwind_Exception_Class exception_class,
              struct _Unwind_Exception *ue_header,
              struct _Unwind_Context *context)
{
  cout << "bb" << endl;
    _Unwind_Reason_Code code = gs_gcc_pf(version, actions, exception_class, ue_header, context);

    if (_URC_HANDLER_FOUND == code)
    {
      cout << "aa" << endl;
        //找到了catch所有的函數

        //當前函數內的指令的地址
        void* cur_ip = (void*)(_Unwind_GetIP(context));
      
        Dl_info info;
        if (dladdr(cur_ip, &info))
        {
      cout << "info.dli_saddr: " << info.dli_saddr << endl;
        
             if (info.dli_saddr == &test_func1)
             {
      cout << "dd" << endl;
                 // 當前函數是目標函數
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
