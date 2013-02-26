__asm__(".code16gcc\n");

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef unsigned long long u64;


void asm_4g_memcpy(u32 dest, u32 src, int n);
void start_c()
{
  u16 buff=0;
  u32 kernel_addr=100;
  asm_4g_memcpy(kernel_addr, (u16)buff, 512);
}
