# practice x86 machine code
#.code16
.code32
.text
.global begin
begin:
#  add 0x12345678(%eax, %esi, 4), %esi
#  add 0x12(%bx, %si, 2), %si
#  mov  0x1234,%esi 
#  movl  $5, (%ebx)
#  movb  $5, (%ebx)
  mov  $5, %ebx
