#include "ceh.h"
#include <stdio.h>

int main(void) 
{
  //定义try block块
  try
  {
    int i,j;
    printf("异常出现前\n\n");

    // 抛出一个异常
    // 其中第一个参数，表示异常类型；第二个参数表示错误代码
    // 第三个参数表示错误信息
    throw(9, 15, "出现某某异常");

    printf("异常出现后\n\n");
  }
  //定义catch block块
  catch
  {
    printf("catch块，被执行到\n");
    printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
    ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);
  }
  // 这里稍有不同，需要定义一个表示当前的try block结束语句
  // 它主要是清除相应的资源
  end_try
}
