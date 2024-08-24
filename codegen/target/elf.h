/**
 * Project Name: regex
 * Module Name: codegen/target
 * Filename: elf.h
 * Creator: Yaokai Liu
 * Create Date: 2024-08-10
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_ELF_H
#define REGEX_ELF_H

#include <stdint.h>

typedef uint32_t Elf32_Addr, Elf32Addr;
typedef uint16_t Elf32_Half, Elf32Half;
typedef uint32_t Elf32_Off, Elf32Offset;
typedef int32_t Elf32_Sword, Elf32Sword;
typedef uint32_t Elf32_Word, Elf32Word;
typedef uint8_t Elf32_UChar, Elf32UChar;

enum E_TYPE {
  ET_NONE = 0,
  ET_REL = 1,
  ET_EXEC = 2,
  ET_DYN = 3,
  ET_CORE = 4,
  ET_LOPROC = 0xff00,
  ET_HIPROC = 0xffff
};

enum E_MACHINE {
  EM_NONE = ET_NONE,
  EM_M32 = 1,
  EM_SPARC = 2,
  EM_386 = 3,
  EM_68K = 4,
  EM_88K = 5,
  EM_860 = 7,
  EM_MIPS = 8,
  EM_MIP_RS4_BE = 10,
  EM_RESERVED_START = 11,
  EM_RESERVED_END = 16,
};

enum E_VERSION {
  EV_NONE = 0,
  EV_CURRENT = 1,
};

enum E_IDENT_OFFSET {
  EI_MAG0 = 0,
  EI_MAG1 = 1,
  EI_MAG2 = 2,
  EI_MAG3 = 3,
  EI_CLASS = 4,
  EI_DATA = 5,
  EI_VERSION = 6,
  EI_PAD = 7,
  EI_NIDENT = 16
};

enum EI_CLASS {
  ELFCLASSNONE = 0,
  ELFCLASS32 = 1,
  ELFCLASS64 = 2
};

enum EI_DATA {
  ELFDATANONE = 0,
  ELFDATA2LSB = 1,
  ELFDATA2MSB = 2
};

typedef struct {
  unsigned char e_ident[EI_NIDENT];
  Elf32_Half e_type;
  Elf32_Half e_machine;
  Elf32_Word e_version;
  Elf32_Addr e_entry;
  Elf32_Off e_phoff;
  Elf32_Off e_shoff;
  Elf32_Word e_flags;
  Elf32_Half e_ehsize;
  Elf32_Half e_phentsize;
  Elf32_Half e_phnum;
  Elf32_Half e_shentsize;
  Elf32_Half e_shnum;
  Elf32_Half e_shstrndx;
} Elf32_Ehdr, Elf32ElfHeader;

const uint8_t EI_MAGS[] = {0x7f, 'E', 'L', 'F'};

enum S_SPEC_NDX {
  SHN_UNDEF = 0,
  SHN_LORESERVE = 0xff00,
  SHN_LOPROC = 0xff00,
  SHN_HIPROC = 0xff1f,
  SHN_ABS = 0xfff1,
  SHN_COMMON = 0xfff2,
  SHN_HIRESERVE = 0xffff
};

enum SH_TYPE {
  SHT_NULL = 0,
  SHT_PROGBITS = 1,
  SHT_SYMTAB = 2,
  SHT_STRTAB = 3,
  SHT_RELA = 4,
  SHT_HASH = 5,
  SHT_DYNAMIC = 6,
  SHT_NOTE = 7,
  SHT_NOBITS = 8,
  SHT_REL = 9,
  SHT_SHLIB = 10,
  SHT_DYNSYM = 11,
  SHT_LOPROC = 0x70000000,
  SHT_HIPROC = 0x7fffffff,
  SHT_LOUSER = 0x80000000,
  SHT_HIUSER = 0xffffffff,
};

enum SH_FLAG {
  SHF_WRITE = 0x1,
  SHF_ALLOC = 0x2,
  SHF_EXECINSTR = 0x4,
  SHF_MASKPROC = 0xf0000000,
};

typedef struct {
  Elf32_Word sh_name;
  Elf32_Word sh_type;
  Elf32_Word sh_flags;
  Elf32_Addr sh_addr;
  Elf32_Off sh_offset;
  Elf32_Word sh_size;
  Elf32_Word sh_link;
  Elf32_Word sh_info;
  Elf32_Word sh_addralign;
  Elf32_Word sh_entsize;
} Elf32_Shdr, Elf32SecHeader;

enum sh_special_name {
  shn_bss,
  shn_comment,
  shn_data,
  shn_data1,
  shn_debug,
  shn_dynamic,
  shn_hash,
  shn_line,
  shn_note,
  shn_rodata,
  shn_rodata1,
  shn_shstrtab,
  shn_strtab,
  shn_symtab,
  shn_text,
};

const char *ELF32_SPEC_SEC_NAMES[] = {
  [shn_bss] = ".bss",       [shn_comment] = ".comment", [shn_data] = ".data",
  [shn_data1] = ".data1",   [shn_debug] = ".debug",     [shn_dynamic] = ".dynamic",
  [shn_hash] = ".hash",     [shn_line] = ".line",       [shn_note] = ".note",
  [shn_rodata] = ".rodata", [shn_rodata1] = ".rodata1", [shn_shstrtab] = ".shstrtab",
  [shn_strtab] = ".strtab", [shn_symtab] = ".symtab",   [shn_text] = ".text",
};

enum ST_BIND {
  STB_LOCAL = 0,
  STB_GLOBAL = 1,
  STB_WEAK = 2,
  STB_LOPROC = 13,
  STB_HIPROC = 15
};

enum ST_TYPE {
  STT_NOTYPE = 0,
  STT_OBJECT = 1,
  STT_FUNC = 2,
  STT_SECTION = 3,
  STT_FILE = 4,
  STT_LOPROC = 13,
  STT_HIPROC = 15
};

#define ELF32_ST_BIND(i)    ((i) >> 4)
#define ELF32_ST_TYPE(i)    ((i) & 0xf)
#define ELF32_ST_INFO(b, t) (((b) << 4) + ((t) & 0xf))

typedef struct {
  Elf32_Word st_name;
  Elf32_Addr st_value;
  Elf32_Word st_size;
  unsigned char st_info;
  unsigned char st_other;
  Elf32_Half st_shndx;
} Elf32_Sym, Elf32Sym;

#define ELF32_R_SYM(i)     ((i) >> 8)
#define ELF32_R_TYPE(i)    ((unsigned char) (i))
#define ELF32_R_INFO(s, t) (((s) << 8) + (unsigned char) (t))

typedef struct {
  Elf32_Addr r_offset;
  Elf32_Word r_info;
} Elf32_Rel, Elf32Rel;
typedef struct {
  Elf32_Addr r_offset;
  Elf32_Word r_info;
  Elf32_Sword r_addend;
} Elf32_Rela, Elf32Rela;

enum R_TYPE {
  R_386_NONE = 0,
  R_386_32 = 1,  // S + A
  R_386_PC32 = 2  // S + A - P
};

enum P_TYPE {
  PT_NULL = 0,
  PT_LOAD = 1,
  PT_DYNAMIC = 2,
  PT_INTERP = 3,
  PT_NOTE = 4,
  PT_SHLIB = 5,
  PT_PHDR = 6,
  PT_LOPROC = 0x70000000,
  PT_HIPROC = 0x7fffffff,
};

typedef struct {
  Elf32_Word p_type;
  Elf32_Off p_offset;
  Elf32_Addr p_vaddr;
  Elf32_Addr p_paddr;
  Elf32_Word p_filesz;
  Elf32_Word p_memsz;
  Elf32_Word p_flags;
  Elf32_Word p_align;
} Elf32_Phdr, Elf32ProgHeader;

enum P_FLAG {
  PF_X = 0x1,
  PF_W = 0x2,
  PF_R = 0x4,
  PF_MASKPROC = 0xf0000000
};

typedef struct {
  Elf32_Sword d_tag;
  union {
    Elf32_Word d_val;
    Elf32_Addr d_ptr;
  } d_un;
} Elf32_Dyn, Elf32Dynamic;
extern Elf32_Dyn _DYNAMIC[];  // NOLINT(*-reserved-identifier)

enum D_TAG {
  DT_NULL = 0,
  DT_NEEDED = 1,
  DT_PLTRELSZ = 2,
  DT_PLTGOT = 3,
  DT_HASH = 4,
  DT_STRTAB = 5,
  DT_SYMTAB = 6,
  DT_RELA = 7,
  DT_RELASZ = 8,
  DT_RELAENT = 9,
  DT_STRSZ = 10,
  DT_SYMENT = 11,
  DT_INIT = 12,
  DT_FINI = 13,
  DT_SONAME = 14,
  DT_RPATH = 15,
  DT_SYMBOLIC = 16,
  DT_REL = 17,
  DT_RELSZ = 18,
  DT_RELENT = 19,
  DT_PLTREL = 20,
  DT_DEBUG = 21,
  DT_TEXTREL = 22,
  DT_JMPREL = 23,
  DT_BIND_NOW = 24,
  DT_LOPROC = 0x70000000,
  DT_HIPROC = 0x7fffffff,
};

unsigned long elf_hash(const unsigned char *name);

#endif  // REGEX_ELF_H
