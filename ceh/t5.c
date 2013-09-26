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
test();
}
catch
{
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);
}
end_try

try
{
try
{
throw(1, 15, "嵌套在try块中");
}
catch
{
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);
}
end_try

throw(2, 30, "再抛一个异常");
}
catch
{
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);

try
{
throw(0, 20, "嵌套在catch块中");
}
catch
{
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);
}
end_try
}
end_try
}
