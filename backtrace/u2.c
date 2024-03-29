#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unwind.h>

// 回调函数，用于处理每个栈帧的信息
_Unwind_Reason_Code trace_callback(struct _Unwind_Context *context, void *ref) {
    // 获取当前栈帧的指令地址
    uintptr_t ip = _Unwind_GetIP(context);
    // 输出当前栈帧的指令地址
    printf("Instruction Pointer: 0x%lx\n", (unsigned long)ip);
    return _URC_NO_REASON;
}

// 获取调用栈信息的函数
void get_backtrace() {
    // 使用 _Unwind_Backtrace 函数遍历调用栈，并指定回调函数
    _Unwind_Backtrace(trace_callback, NULL);
}

int main() {
    printf("Starting backtrace:\n");
    get_backtrace();
    return 0;
}
