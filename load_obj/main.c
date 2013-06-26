#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/mman.h>


#include "type.h"
#include "elf.h"

u8 *hello_addr;

int shstrndx;

typedef struct SymbolData_
{
  u32 offset;
  u32 addr;
  u32 section_index;
}SymbolData;

typedef struct StrTabData_
{
  char  *str_;
  u32 len_;
}StrTabData;

#define STR_NUM 30
StrTabData section_name[STR_NUM];
StrTabData symbol_name[STR_NUM];

u8 *section_string;
u8 *symbol_string;

int lookup_string_section(u8 *section_addr, u32 section_num)
{
  StrTabData *str_tab;
  Elf32_Shdr *shdr = (Elf32_Shdr*)(section_addr);
  for (int i=0 ; i < section_num ; ++i)
  {
    if (shdr->sh_type == 3) // string section
    {
      if (shstrndx == i) 
      {
        printf("section name string table\n");
        str_tab = section_name;
        section_string = hello_addr+shdr->sh_offset;
      }
      else
      {
        str_tab = symbol_name;
        symbol_string = hello_addr+shdr->sh_offset;
      }

      char *ptr = hello_addr+shdr->sh_offset;
      int ptr_index=0;
      int total_len=0;

      printf("found string section: %d\n", i);
      printf("shdr->sh_size: %#x\n", shdr->sh_size);
      printf("shdr->sh_offset: %#x\n", shdr->sh_offset);
      while(1)
      {
        int len = strlen(ptr);
        printf("ptr: %s ## ptr index: %x ## len: %u\n", ptr, total_len, len);
        total_len += len + 1;


        if (total_len >= shdr->sh_size)
          break;

        ptr += (len + 1);

      }
      //printf("shdr->sh_entsize: %#x\n", shdr->sh_entsize);

      //int ent_num = shdr->sh_size/shdr->sh_entsize;
    }
    ++shdr;
  }
}

int lookup_symbol(u8 *section_addr, u32 section_num, const char* symbol_name)
{
  Elf32_Shdr *shdr = (Elf32_Shdr*)(section_addr);
  for (int i=0 ; i < section_num ; ++i)
  {
    if (shdr->sh_type == 2) // symbol table
    {
      printf("found symbol section: %d\n", i);
      int ent_num = shdr->sh_size/shdr->sh_entsize;
      Elf32_Sym *sym = (Elf32_Sym*)(hello_addr + shdr->sh_offset);
      for (int j=0 ; j < ent_num ; ++j)
      {
        if (symbol_name != 0)
        {
          if (strcmp(symbol_name, symbol_string + sym->st_name) == 0)
          {
            return sym->st_value;
          }
        }
        printf("index: %d ", j);
        printf("name[%#x]: %s ", sym->st_name, symbol_string + sym->st_name);
        printf("val: %#x ", sym->st_value);
        printf("size: %#x\n", sym->st_size);

        ++sym;
      }
    }

    ++shdr;
  }
}


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


#define SECTION_NUM 100
u32 section_offset[SECTION_NUM];

int main()
{

  FILE *fs;
  fs = fopen("./hello.o", "r");
  fseek(fs, 0, SEEK_END);
  int size = ftell(fs);
  fseek(fs, 0, SEEK_SET);

  u32 align_addr;

  hello_addr = (u8*)malloc(size);
  printf("hello addr: %p\n", hello_addr);
  align_addr = (u32)hello_addr;
  printf("align addr: %x\n", align_addr);

  align_addr &= 0xfffff000;
  align_addr += 0x1000;
  hello_addr = align_addr;
  printf("align 0x1000 hello addr: %p\n", hello_addr);
  fread(hello_addr, 1, size, fs);
  fclose(fs);

  u8 *ptr = hello_addr;

  Elf32Ehdr *elf_hdr = (Elf32Ehdr*)ptr;

  printf("shoff: %x\n", elf_hdr->e_shoff);
  printf("shnum: %x\n", elf_hdr->e_shnum);
  printf("e_shstrndx: %d\n", elf_hdr->e_shstrndx);

  shstrndx = elf_hdr->e_shstrndx;

  Elf32_Shdr *shdr = (Elf32_Shdr*)(hello_addr + elf_hdr->e_shoff);
  Elf32_Shdr *shdr_addr = (Elf32_Shdr*)(hello_addr + elf_hdr->e_shoff);

  lookup_string_section((u8*)shdr_addr, elf_hdr->e_shnum);
  lookup_symbol((u8*)shdr_addr, elf_hdr->e_shnum, 0);

  u32 hello_val = lookup_symbol((u8*)shdr_addr, elf_hdr->e_shnum, "hello");
  printf("hello_val: %#x\n", hello_val);

  u32 text_offset;
  for (int i=0 ; i < elf_hdr->e_shnum ; ++i)
  {
    printf("#%d section_name[%#x]: %s\n", i, shdr->sh_name, section_string+(shdr->sh_name));
    section_offset[i] = shdr->sh_offset;
    //printf("section_offset[%d]: %#x\n", i, section_offset[i]);
    ++shdr;
  }

  shdr = (Elf32_Shdr*)(hello_addr + elf_hdr->e_shoff);

  for (int i=0 ; i < elf_hdr->e_shnum ; ++i)
  {
    //printf("#%d shdr : %p\n", i, (u8*)shdr-hello_addr);
    if (i == 1) // .text section
    {
      printf("text offset: %#x\n", shdr->sh_offset);
      text_offset = shdr->sh_offset;
    }

    if (i==2 && shdr->sh_type == 9)
    {
      printf("section_offset[1]: %#x\n", section_offset[1]);
      printf("section_offset[3]: %#x\n", section_offset[3]);
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

	printf("section_offset[1]: %x\n", section_offset[1]);
	printf("section_offset[3]: %x\n", section_offset[3]);

	printf("symbol_data.section_index: %x\n", symbol_data.section_index);
	printf("modify addr: %#x\n", text_offset + symbol_data.offset);
        printf("modify value: %#x\n", section_offset[symbol_data.section_index] + symbol_data.addr);
	switch (class)
	{
          case 1:
	  {
            *(u32*)(hello_addr + text_offset + symbol_data.offset) += hello_addr + section_offset[symbol_data.section_index] + symbol_data.addr;
            break;
	  }
          case 2:
	  {
            s32 org_val = *(u32*)(hello_addr + text_offset + symbol_data.offset);
	    printf("org val: %d\n", org_val);
            *(u32*)(hello_addr + text_offset + symbol_data.offset) = hello_addr + section_offset[symbol_data.section_index] + symbol_data.addr + org_val - (u32)(hello_addr + text_offset + symbol_data.offset);
            //*(s32*)(hello_addr + text_offset + symbol_data.offset) = 0xffffffde;
            printf("1 %#x\n", (u32)(hello_addr + text_offset + symbol_data.offset));
            printf("func addr %#x\n", hello_addr + section_offset[symbol_data.section_index] + symbol_data.addr);
            printf("val %#x\n", hello_addr + section_offset[symbol_data.section_index] + symbol_data.addr + org_val - (u32)(hello_addr + text_offset + symbol_data.offset));
            //*(u32*)(hello_addr + text_offset + symbol_data.offset) = 0xdeffffff;
            break;
	  }


          
	}


        ++rel;
      }
      #if 0
        SymbolData symbol_data = lookup_symbol_data((u8*)shdr_addr, elf_hdr->e_shnum, 9);
	printf("sym9 symbol_data.addr: %x\n", symbol_data.addr);
	printf("sym9 symbol_data.section_index: %x\n", symbol_data.section_index);
        #endif
    }
    ++shdr;
  }

  //unsigned int addr = 0;

#if 1
  errno = 0;
  if (mprotect(hello_addr, size, PROT_EXEC|PROT_READ|PROT_WRITE) == 0)
  {
    goto *(hello_addr + text_offset + hello_val);
  }
  else
  {
    switch (errno)
    {
      case EACCES:
      {
        printf("1\n");
        break;
      }
      case EINVAL:
      {
        printf("2\n");
        break;
      }
      case ENOMEM:
      {
        printf("3\n");
        break;
      }
    }
    perror("mprotect err\n");
  }
#endif
  return 0;
  
}

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
