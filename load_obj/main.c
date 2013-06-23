
int main()
{
// find rel.text and rel.data
// inf rel.text/rel.data offset in object file.
// from 0x3d4, size: 0x10
// 16 00 00 00  r_offset
// 01 08 00 00  r_info
// 1e 00 00 00
// 02 09 00 00 

#if 0
I need know i, func symbol offset in hello.o
RELOCATION RECORDS FOR [.text]:
OFFSET   TYPE              VALUE 
00000016 R_386_32          i
0000001e R_386_PC32        func

     8: 00000000     4 OBJECT  GLOBAL DEFAULT    3 i
     9: 00000000    15 FUNC    GLOBAL DEFAULT    1 func

  [ 3] .data             PROGBITS        00000000 000058 000004 00  WA  0   0  4
  [ 1] .text             PROGBITS        00000000 000034 000024 00  AX  0   0  4


#endif

  hello();
}
