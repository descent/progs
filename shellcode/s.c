#include <stdio.h>

#if 0
   0:   b8 01 00 00 00          mov    $0x1,%eax
   5:   bb 00 00 00 00          mov    $0x0,%ebx
   a:   cd 80                   int    $0x80

#endif
char __attribute__ ((section (".text"))) shellcode[] = "\xb8\x01\x00\x00\x00\xbb\x00\x00\x00\x00\xcd\x80";
typedef void (*FUNCPTR)();

int main() {
    printf("<< Shellcode begin >>\n");

#if 0
    FUNCPTR fp = (FUNCPTR)shellcode;
    fp();
#else
    goto *(char *)shellcode;
#endif
    printf("<< Shellcode end >>\n");
    return 0;
}
