/**
 * Project Name: regex
 * Module Name: codegen/target
 * Filename: target.h
 * Creator: Yaokai Liu
 * Create Date: 2024-08-24
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_CODEGEN_TARGET_H
#define REGEX_CODEGEN_TARGET_H

#include "array.h"

typedef struct Target {
  const Allocator *allocator;
  Array *instrBuffer;  // Array<unsigned char>
  Array *rodataBuffer;  // Array<unsigned char>
  Array *relocateBuffer;  // Array<Elf32Rela>
} Target;

Target *Target_new(const Allocator *allocator);

uint32_t Target_concat(const Target *dest, const Target *addend);

#endif  // REGEX_CODEGEN_TARGET_H
