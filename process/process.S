.code16
.text
.global begin
begin:
  xchg %bx, %bx #bochs magic break point
  cli

  xor     %eax, %eax
  mov     %cs,%ax
  mov     %ax,%ds

  #rewrite int 0x30
  #shl  $4, %eax
  #addl $switch_proc, %eax

  movw    $0x0, %bx
  movw    %bx, %es
  #mov $0xc0, %esi
  #movw    $switch_proc, %es:(%esi)
  movw $switch_proc, %es:0xc0

  movw %ax, %es:0xc2


  movw    $0xb800, %ax
  movw    %ax, %gs

  movw $proc_a, stack_frame
  movw $proc_b, stack_frame+6

  movw %cs, %ax
  movw %ax, stack_frame+2
  movw %ax, stack_frame+8

  # get flag
  pushf
  movw (%esp), %ax
  popf
  movw %ax, stack_frame+4
  movw %ax, stack_frame+10


#  pushw %ax
#  pushw $proc_a
  movw $stack_frame, cur_proc
  movw cur_proc, %sp
  iret


  #call switch_proc
  int $0x30


  mov $0x4c00, %ax
  int $0x21           

#msg:.ascii "Hello GAS"
msg:
  .asciz "Hello GAS"
  #.asciz "Hello World"
cur_proc:
  .word 0x0

stack_frame:
  .word 0x0# eip
  .word 0x1# cs
  .word 0x2# flag

  .word 0x0# eip
  .word 0x1# cs
  .word 0x2# flag

.global proc_a
proc_a:
  #mov $0x1, %ax
  mov $'a', %al
1:
  mov $0, %edi
  movb %al, %gs:(%edi)
  movb $0x9, %gs:1(%edi)
  inc %al
  int $0x30
  jmp 1b

.global proc_b
proc_b:
  #mov $0x2, %bx
  #mov $0x3, %bx
  mov $'b', %bl
1:
  mov $160, %edi
  movb %bl, %gs:(%edi)
  movb $0xc, %gs:1(%edi)
  inc %bl
  int $0x30
  jmp 1b

.global switch_proc
switch_proc:
  movw cur_proc, %dx
  cmp $stack_frame, %dx
  je 1f
  movw $stack_frame, cur_proc
  jmp 2f
1:
  movw $stack_frame+6, cur_proc
2:
  movw cur_proc, %sp
  iret

#if 0
  xchg %bx, %bx #bochs magic break point
  mov    $0, %edi    /* Destination */
  mov    $msg, %esi   /* Source */

1:
  #cmp $0, %ecx
  cmpb $0, (%esi)
  jz 2f
  movb %ds:(%esi), %al
  inc %esi
  movb %al, %gs:(%edi)
  inc %edi
  movb $0xc, %gs:(%edi)
  inc %edi
  dec %ecx
  jmp 1b
2:
  movb $'E', %gs:(160)
  xchg %bx, %bx #bochs magic break point
  iret
#endif
