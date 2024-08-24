/**
 * Project Name: regex
 * Module Name: codegen/target
 * Filename: elf.c
 * Creator: Yaokai Liu
 * Create Date: 2024-08-10
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "elf.h"
#include "array.h"

unsigned long elf_hash(const unsigned char *name) {
  unsigned long h = 0, g;
  while (*name) {
    h = (h << 4) + *name++;
    if ((g = h & 0xf0000000)) { h ^= g >> 24; }
    h &= ~g;
  }
  return h;
}

typedef struct {
  Array *text;
  Array *rodata;

} ElfBarebones;