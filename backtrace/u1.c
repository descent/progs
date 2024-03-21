#include <stdio.h>
#include <stdlib.h>
#define UNW_LOCAL_ONLY
#include <libunwind.h>



void print_backtrace() {
    unw_cursor_t cursor;
    unw_context_t context;

    // 获取当前线程的上下文
    unw_getcontext(&context);
    // 初始化游标以便从当前位置开始遍历堆栈帧
    unw_init_local(&cursor, &context);

    // 遍历堆栈帧
    while (unw_step(&cursor) > 0) {
        unw_word_t offset, pc;
        char sym[256];

        // 获取指令指针位置
        unw_get_reg(&cursor, UNW_REG_IP, &pc);
        // 获取调用指令的偏移量
        unw_get_proc_name(&cursor, sym, sizeof(sym), &offset);

        printf("  0x%lx: (%s+0x%lx)\n", (long)pc, sym, offset);
    }
}

void foo() {
    print_backtrace();
}

void bar() {
    foo();
}

int main() {
    bar();
    return 0;
}
