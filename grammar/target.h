/**
 * Project Name: regex
 * Module Name: grammar
 * Filename: target.h
 * Creator: Yaokai Liu
 * Create Date: 24-6-29
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_TARGET_H
#define REGEX_TARGET_H

#include "array.h"
#include <stdint.h>

typedef struct Sequence {
  uint32_t length;
  uint32_t alloc;
  uint8_t *plains;
} Sequence;

typedef struct Object {
  uint8_t type;
  uint8_t inv;
  uint32_t post_state;
  void *target;
} Object;

typedef struct Quantifier {
  uint8_t min;
  uint8_t max;
} Quantifier;

typedef struct Quantified {
  struct Quantifier quant;
  struct Object object;
} Quantified;

typedef struct Regexp {
  uint32_t length;
  uint32_t alloc;
  struct Branch *branches;
} Regexp;

typedef struct Unit {
  uint8_t type;
  uint8_t inv;
  void *target;
} Unit;

typedef Array UnitArray;

typedef struct Range {
  uint8_t min;
  uint8_t max;
} Range;

typedef Array Branch;

typedef struct Group {
  struct Regexp regexp;
} Group;

typedef struct Charset {
  Array * pos_plains;
  Array * pos_ranges;
  Array * neg_plains;
  Array * neg_ranges;
} Charset;

#include "allocator.h"

typedef void *fn_product(void *argv[], const Allocator *allocator);

extern fn_product * const PRODUCTS[];

#endif  // REGEX_TARGET_H
