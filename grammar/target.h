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
#include "char_t.h"
#include <stdint.h>

typedef Array Sequence;

typedef struct Object {
  uint8_t type;
  uint8_t inv;
  char_t *regex;
  uint32_t start;
  uint32_t length;
  void *target;
} Object;

typedef struct Quantifier {
  uint16_t min;
  uint16_t max;
} Quantifier;

typedef struct Quantified {
  struct Quantifier quant;
  struct Object object;
} Quantified;

typedef Array Regexp;

typedef struct Unit {
  uint8_t type;
  bool inv;
  void *target;
} Unit;

typedef Array UnitArray;

typedef struct Range {
  char_t min;
  char_t max;
} Range;

typedef Array Branch;

typedef struct Group {
  Regexp *regexp;
} Group;

enum TAP_TYPE : bool {
  CT_NORMAL = false,
  CT_INVERSE = true
};
typedef struct Charset {
  struct charset_part {
    Array *plains;
    Array *ranges;
  } parts[2];
} Charset;

#include "allocator.h"

typedef void *fn_product(void *argv[], const Allocator *allocator);

extern fn_product * const PRODUCTS[];

void releaseRegexp(Regexp *regexp, const Allocator *allocator);
void releaseBranch(Branch *branch, const Allocator *allocator);
void releaseGroup(Group *group, const Allocator *allocator);
void releaseObject(Object *object, const Allocator *allocator);
void releaseCharset(Charset *charset, const Allocator *allocator);
void releaseSequence(Sequence *sequence, const Allocator *allocator);
void releaseQuantified(Quantified *quantified, const Allocator *allocator);
void releaseUnitArray(UnitArray *unitArray, const Allocator *);
void releaseUnit(Unit *unit, const Allocator *allocator);

#endif  // REGEX_TARGET_H
