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

#include <stdint.h>

struct Sequence {
  uint32_t length;
  uint32_t alloc;
  char *plains;
};
struct Object {
  uint8_t type;
  uint8_t inv;
  void *target;
};
struct Quantifier {
  uint8_t min;
  uint8_t max;
};
struct Quantified {
  struct Quantifier quant;
  struct Object object;
};
struct BranchArray {
  uint32_t length;
  uint32_t alloc;
  struct Branch *array;
};
struct ObjectArray {
  uint32_t length;
  uint32_t alloc;
  struct Object *array;
};
struct Regexp {
  struct BranchArray branches;
};
struct NumQuantifier {
  uint8_t min;
  uint8_t max;
};
struct CharsetUnit {
  uint8_t type;
  uint8_t inv;
  void *target;
};
struct Range {
  uint8_t min;
  uint8_t max;
};
struct Branch {
  struct ObjectArray objects;
};
struct Group {
  struct Regexp regexp;
};
struct CharsetUnitArray {
  uint32_t length;
  uint32_t alloc;
  struct CharsetUnit *array;
};
struct Charset {
  struct CharsetUnitArray units;
};

#include "allocator.h"

typedef void *fn_product(void * argv[], const Allocator *allocator);

extern fn_product * const PRODUCTS[];
extern fn_product * const EXTEND_PRODUCT;

#endif  // REGEX_TARGET_H
