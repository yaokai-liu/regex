/**
 * Project Name: regex
 * Module Name: codegen/x64
 * Filename: mcode.h
 * Creator: Yaokai Liu
 * Create Date: 2024-07-27
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_MCODE_H
#define REGEX_MCODE_H

#include "array.h"
#include "char_t.h"
#include "target/target.h"

uint32_t mcode_ranges(uint32_t lower_bounds, uint32_t upper_bounds, uint32_t n_ranges,
                      const Target *target);
Array *mcode_char(char_t the_char);
Array *mcode_plains(char_t *plains, uint32_t n_plains);
Array *mcode_sequence(char_t *plains, uint32_t n_plains);

#endif  // REGEX_MCODE_H
