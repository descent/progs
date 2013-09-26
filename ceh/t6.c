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
// 这里表示程序中将捕获浮点数计算异常
CEH_init();

try
{
try
{
try
{
double i,j;
j = 0;
// 这里出现浮点数计算异常
i = 1/j ;

test();

throw(9, 15, "出现某某异常");
}
end_try
}
catch_part(4, 6)
{
printf("catch_part(4, 6)块，被执行到\n");
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);
}
catch_part(2, 3)
{
printf("catch_part(2, 3)块，被执行到\n");
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);
}
// 捕获到上面的异常
catch
{
printf("内层的catch块，被执行到\n");
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);

// 这里再次把上面的异常重新抛出
rethrow;

printf("这里将不会被执行到\n");
}
end_try
}
catch_part(7, 9)
{
printf("catch_part(7, 9)块，被执行到\n");
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);

throw(2, 15, "出现某某异常");
}
// 再次捕获到上面的异常
catch
{
printf("外层的catch块，被执行到\n");
printf("捕获到一个异常，错误原因是：%s! err_type:%d err_code:%d\n",
ceh_ex_info->err_msg, ceh_ex_info->err_type, ceh_ex_info->err_code);

// 最后又抛出了一个异常，
// 但是这个异常没有对应的catch block处理，所以系统中处理了
throw(2, 15, "出现某某异常");
}
end_try
}
