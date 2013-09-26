#include "ceh.h"

int main(void) 
{
try
{
try
{
throw(1, 15, "嵌套在try块中");
}
catch_part(4, 6)
{
printf("catch_part(4, 6)块，被执行到\n");
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);
}
end_try

printf("这里将不会被执行到\n");
}
catch_part(2, 3)
{
printf("catch_part(2, 3)块，被执行到\n");
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);
}
// 找到了对应的catch block
catch_one(1)
{
printf("catch_one(1)块，被执行到\n");
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);
}
catch
{
printf("catch块，被执行到\n");
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);
}
end_try

}


