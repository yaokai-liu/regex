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
  uint32_t post_state;
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
struct Regexp {
  uint32_t length;
  uint32_t alloc;
  struct Branch *branches;
};
struct NumQuantifier {
  uint8_t min;
  uint8_t max;
};
struct Unit {
  uint8_t type;
  uint8_t inv;
  void *target;
};
struct Range {
  uint8_t min;
  uint8_t max;
};
struct Branch {
  uint32_t length;
  uint32_t alloc;
  uint32_t post_state;
  struct Object *objects;
};
struct Group {
  struct Regexp regexp;
};
struct UnitArray {
  uint32_t length;
  uint32_t alloc;
  struct Unit *array;
};
struct Charset {
  struct UnitArray units;
};

#include "allocator.h"

typedef void *fn_product(void *argv[], const Allocator *allocator);

extern fn_product * const PRODUCTS[];

#endif  // REGEX_TARGET_H
