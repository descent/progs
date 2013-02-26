/*
 * the kernel loader will initialize c runtime and enter x86 protected mode 
 */


#define BIG_REAL_MODE

.data

LABEL_STACK:
.space 1024, 0
.set top_of_stack, (. - LABEL_STACK)



.code16
.extern __bss_start__
.extern __bss_end__

.text
.global _start
_start:
  xchg %bx, %bx
  mov %cs, %ax
  #mov $0xa00, %ax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs

  mov %ax, %ss
# setup stack
  mov $0xfff0, %sp # why not setting 0xffff to %sp, in ms dos, 0xfff0 is ok, 0xffb will get core dump

  call init_bss_asm
  call start_c

#disp_str: 
#    mov     $BootMessage, %ax
#    mov     %ax,%bp 
#    mov     $16,%cx
#    mov     $0x1301,%ax
#    mov     $0x00c,%bx
#    mov     $0,%dl
#    int     $0x10
#    ret
#BootMessage:.ascii "Hello, c-env world!"
#disp_str2: 
#    mov     $str2, %ax
#    mov     %ax,%bp 
#    mov     $5,%cx
#    mov     $0x1301,%ax
#    mov     $0x00c,%bx
#    mov     $0,%dl
#    int     $0x10
#    ret
#str2:.ascii "after"


#if 0
  __asm__ __volatile__
    (
      "movw  $0, %0\n"
      "int $0x13\n"
      "setcb %0"
      :"=m"(failed), "=a"(num_blocks_transferred)
      :"a"(0x0200|blocks), "b"(buff), "c"(track_no << 8 | sector_no), "d"(head_no << 8 | disk_no)
    );
#endif


# use big real mode copy to 4g range
# use %fs for segment register, %fs points to 4g memory space
.globl asm_4g_memcpy
# ex: 
# asm_absolute_memcpy((u8*)0x100, (u8 *)IMAGE_LMA, 512*3);
# copy IMAGE_LMA to 0x100
asm_4g_memcpy:
    pushl   %ebp
    mov     %esp, %ebp

    pushl   %esi
    pushl   %edi
    pushl   %ecx

    mov     8(%ebp), %edi    /* Destination */
    mov     12(%ebp), %esi   /* Source */
    mov     16(%ebp), %ecx   /* Counter */
1:
    cmp     $0, %ecx  /* Loop counter */
    jz      2f
    movb    %ds:(%esi), %al
    inc     %esi
    movb    %al, %fs:(%edi)
    inc     %edi
    dec     %ecx
    jmp     1b
2:
    mov     8(%ebp), %eax
    pop     %ecx
    pop     %edi
    pop     %esi
    mov     %ebp, %esp
    pop     %ebp
    retl

# init bss
init_bss_asm:
  movw $__bss_end__, %di    /* Destination */
  movw $__bss_start__, %si   /* Source */
#  movw $0x0, %ax
#  movw %ax, %gs
  jmp 2f
1:
  mov $0, %eax
  movw %si, %ax
  movb $0x1, (%eax)
#  movb $0x1, %ds:(%eax)
  add $1, %si
  
2:
  cmpw %di, %si
  jne 1b
  ret

