#include <stdio.h>
#include <stdlib.h>

#include "type.h"
#include "elf.h"

u8 *hello_addr;

typedef struct SymbolData_
{
  u32 offset;
  u32 addr;
  u32 section_index;
}SymbolData;

SymbolData lookup_symbol_data(u8 *section_addr, u32 section_num, u32 symbol_index)
{
  // find symbol section first.

  Elf32_Shdr *shdr = (Elf32_Shdr*)(section_addr) + symbol_index;
  for (int i=0 ; i < section_num ; ++i)
  {
    if (shdr->sh_type == 2) // symbol table
    {
#if 0
    printf("#%d type : %x\n", i, shdr->sh_type);
    printf("#%d shoff: %x\n", i, shdr->sh_offset);
    printf("#%d size: %x\n", i, shdr->sh_size);
    printf("#%d entsize: %x\n", i, shdr->sh_entsize);
#endif
      int ent_num = shdr->sh_size/shdr->sh_entsize;
      Elf32_Sym *sym = (Elf32_Sym*)(hello_addr + shdr->sh_offset) + symbol_index;
      SymbolData symbol_data;

      symbol_data.addr = sym->st_value;
      symbol_data.section_index = sym->st_shndx;
      return symbol_data;

#if 0
      for (int j=0 ; j < ent_num ; ++j)
      {
	printf("#%d st_value: %x\n", j, sym->st_value);
	printf("st_size: %x\n", sym->st_size);
	printf("st_shndx: %x\n", sym->st_shndx);
        ++sym;
      }
#endif
    }
    ++shdr;
  }


}

int main()
{

  FILE *fs;
  fs = fopen("./hello.o", "r");
  fseek(fs, 0, SEEK_END);
  int size = ftell(fs);
  fseek(fs, 0, SEEK_SET);

  hello_addr = (u8*)malloc(size);
  fread(hello_addr, 1, size, fs);
  fclose(fs);

  u8 *ptr = hello_addr;

  Elf32Ehdr *elf_hdr = (Elf32Ehdr*)ptr;

  printf("shoff: %x\n", elf_hdr->e_shoff);
  printf("shnum: %x\n", elf_hdr->e_shnum);

  Elf32_Shdr *shdr = (Elf32_Shdr*)(hello_addr + elf_hdr->e_shoff);
  Elf32_Shdr *shdr_addr = (Elf32_Shdr*)(hello_addr + elf_hdr->e_shoff);


  for (int i=0 ; i < elf_hdr->e_shnum ; ++i)
  {
    //printf("#%d shdr : %p\n", i, (u8*)shdr-hello_addr);
    if (shdr->sh_type == 9)
    {
    printf("#%d name : %x\n", i, shdr->sh_name);
    printf("#%d type : %x\n", i, shdr->sh_type);
    printf("#%d shoff: %x\n", i, shdr->sh_offset);
    printf("#%d size: %x\n", i, shdr->sh_size);
    printf("#%d entsize: %x\n", i, shdr->sh_entsize);


      int ent_num = shdr->sh_size/shdr->sh_entsize;
      Elf32_Rel *rel = (Elf32_Rel*)(hello_addr + shdr->sh_offset);
      for (int j=0 ; j < ent_num ; ++j)
      {
	printf("r_offset: %x\n", rel->r_offset);
	printf("r_info: %x\n", rel->r_info);
	u8 class = rel->r_info & 0xff;
	u8 symbo_index = ((rel->r_info >> 8 ) & 0xffffff);
        SymbolData symbol_data = lookup_symbol_data((u8*)shdr_addr, elf_hdr->e_shnum, symbo_index);
	symbol_data.offset = rel->r_offset;
	printf("class: %x\n", class);
	printf("symbo_index: %x\n", symbo_index);
	printf("symbol_data.offset: %x\n", symbol_data.offset);
	printf("symbol_data.addr: %x\n", symbol_data.addr);
	printf("symbol_data.section_index: %x\n", symbol_data.section_index);
        ++rel;
      }
    }
    ++shdr;
  }

  return 0;
  

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

}
