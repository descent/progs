#include "ceh.h"

int main(void) 
{
// 外层的try catch块
try
{
// 内层的try catch块
try
{
throw(1, 15, "嵌套在try块中");
}
catch
{
printf("内层的catch块被执行\n");
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);

printf("外层的catch块被执行\n");
}
end_try

throw(2, 30, "再抛一个异常");
}
catch
{
printf("外层的catch块被执行\n");
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);
}
end_try
}
