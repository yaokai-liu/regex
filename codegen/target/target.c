/**
 * Project Name: regex
 * Module Name: codegen/target
 * Filename: target.c
 * Creator: Yaokai Liu
 * Create Date: 2024-08-24
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "target.h"
#include "elf.h"

Target *Target_new(const Allocator * const allocator) {
  Target *target = allocator->calloc(1, sizeof(Target));
  target->allocator = allocator;
  target->instrBuffer = Array_new(sizeof(uint8_t), allocator);
  target->rodataBuffer = Array_new(sizeof(uint8_t), allocator);
  target->relocateBuffer = Array_new(sizeof(uint8_t), allocator);
  return target;
}

uint32_t Target_concat(const Target *dest, const Target *addend) {
  uint32_t inst_offset = Array_length(dest->instrBuffer);
  uint32_t data_offset = Array_length(dest->rodataBuffer);
  Array_concat(dest->instrBuffer, addend->instrBuffer);
  Array_concat(dest->rodataBuffer, addend->rodataBuffer);
  for (uint32_t i = 0; i < Array_length(addend->relocateBuffer); i++) {
    Elf32Rela rela = {};
    Elf32Rela *addend_rela = Array_get(addend->relocateBuffer, i);
    rela.r_offset = inst_offset + addend_rela->r_offset;
    rela.r_addend = (int32_t) data_offset + addend_rela->r_addend;
    rela.r_info = addend_rela->r_info;
    Array_append(dest->relocateBuffer, &rela, 1);
  }
  return 0;
}