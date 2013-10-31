#include "ceh.h"

int main(void) 
{
try
{
int i,j;
printf("异常出现前\n\n");

throw(9, 15, "出现某某异常");

printf("异常出现后\n\n");
}
// 这里表示捕获异常类型从4到6的异常
catch_part(4, 6)
{
printf("catch_part(4, 6)块，被执行到\n");
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);
}
// 这里表示捕获异常类型从9到10的异常
catch_part(9, 10)
{
printf("catch_part(9, 10)块，被执行到\n");
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);
}
// 这里表示只捕获异常类型为1的异常
catch_one(1)
{
printf("catch_one(1)块，被执行到\n");
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);
}
// 这里表示捕获所有类型的异常
catch
{
printf("catch块，被执行到\n");
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);
}
end_try
}
