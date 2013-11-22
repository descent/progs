JUMP MACRO selector, offsetv
  DB 0eah
  DW offsetv
  DW selector
  ENDM

ECHOCH MACRO ascii
  mov ah, 2
  mov dl, ascii
  int 21h
  endm

DESCRIPTOR STRUC
LIMITL DW 0
BASEL DW 0
BASEM DB 0
ATTRIBUTES DW 0
BASEH DB 0
DESCRIPTOR ENDS

PDESC STRUC
LIMIT DW 0
BASE DD 0
PDESC ENDS

ATDW = 92H
ATCE = 98H
.386P

DSEG SEGMENT USE16
GDT LABEL BYTE
DUMMY DESCRIPTOR <>
CODE DESCRIPTOR <0FFFFH,,,ATCE,>
CODE_SEL = CODE - GDT
DATAS DESCRIPTOR <0FFFFH,0H,11H,ATDW,0>
DATAS_SEL = DATAS - GDT
DATAD DESCRIPTOR<0FFFFH,,,ATDW,>
DATAD_SEL = DATAD - GDT
GDTLEN = $ - GDT
VGDTR PDESC <GDTLEN-1>
BUFFERLEN = 256
BUFFER DB BUFFERLEN DUP(0)
DSEG ENDS

CSEG SEGMENT USE16
  ASSUME CS:CSEG, DS:DSEG
START:
  xchg bx, bx
  mov ax, dseg
  mov ds, ax
  mov bx, 16
  mul bx
  add ax, offset gdt
  adc dx, 0
  mov word ptr vgdtr.base, ax
  mov word ptr vgdtr.base+2, dx
  mov ax, cs
  mul bx
  mov code.basel, ax
  mov code.basem, dl
  mov code.baseh, dh
  mov ax, ds
  mul bx
  add ax, offset buffer
  adc dx, 0
  mov datad.basel, ax
  mov datad.basem, dl
  mov datad.baseh, dh

  lgdt qword ptr vgdtr

  cli
  call ea20

  mov eax, cr0
  or eax, 1
  mov cr0, eax

  JUMP <CODE_SEL>, <OFFSET VIRTUAL>

VIRTUAL:
  mov ax, datas_sel
  mov ds, ax
  mov ax, datad_sel
  mov es, ax
  cld
  xor si, si
  xor di, di
  mov cx, bufferlen/4
  repz movsd

  mov eax, cr0
  and eax, 0fffffffeh
  mov cr0, eax

  JUMP <SEG REAL>,<OFFSET REAL>

REAL:
  call da20
  sti
  mov ax, dseg
  mov ds, ax
  mov si, offset buffer
  cld
  mov bp, bufferlen/16
NEXTLINE:
  mov cx, 16
NEXTCH:
  lodsb
  push ax
  shr al, 4
  call toascii
  ECHOCH al
  pop ax
  call toascii
  echoch al
  echoch ' '
  loop nextch
  echoch 0dh
  echoch 0ah
  dec bp
  jnz nextline

  mov ax, 4c00h
  int 21h

TOASCII PROC
        and    al, 0fh
        cmp     al, 9
        ja      EN
        add    al, 030h
        jmp     EX
EN:
        sub     al, 0ah
        add     al, 041h
EX:
        ret
TOASCII ENDP

EA20 PROC
  push ax
  in al, 92h
  or al, 2
  out 92h, al
  pop ax
  ret
EA20 ENDP

DA20 PROC
  push ax
  in al, 92h
  and al, 0fdh
  out 92h, al
  pop ax
  ret
DA20 ENDP





CSEG ENDS
  END START

