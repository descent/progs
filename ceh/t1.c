#include "ceh.h"

void test1()
{
throw(0, 20, "hahaha");
}

void test()
{
test1();
}

int main(void) 
{
try
{
int i,j;
printf("异常出现前\n\n");

// 注意，这个函数的内部会抛出一个异常。
test();

throw(9, 15, "出现某某异常");

printf("异常出现后\n\n");
}
catch
{
printf("catch块，被执行到\n");
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);
}
end_try
}
