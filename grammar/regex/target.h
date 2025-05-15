/**
 * Project Name: regex
 * Module Name: grammar
 * Filename: target.h
 * Creator: Yaokai Liu
 * Create Date: 24-6-29
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_GRAMMAR_REGEX_TARGET_H
#define REGEX_GRAMMAR_REGEX_TARGET_H

#include "allocator.h"
#include "array.h"
#include "char_t.h"
#include "set.h"
#include "terminal.h"
#include <stdint.h>

typedef Array Regex;
typedef Array Branch;
typedef Array UnitArray;
typedef Array Sequence;

typedef struct Object {
  uint32_t type;
  uint16_t inverse;
  uint16_t assertion;
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

typedef struct Unit {
  uint8_t type;
  bool inverse;
  void *target;
} Unit;

typedef struct Range {
  uint32_t min;
  uint32_t max;
} Range;

typedef struct Group {
  Regex *regexp;
} Group;

typedef struct ConstCharset {
  struct {
    const uint32_t n_plains;
    const uint32_t n_ranges;
    const char_t * plains;
    const Range *ranges;
  } parts[2];
} ConstCharset;
extern const ConstCharset ESCAPE_CHARSETS[];

enum PART_ENUM : bool {
  CT_NORMAL = false,
  CT_INVERSE = true
};
typedef struct Charset {
  struct CharsetPart {
    Array *plains;  // Array<uint32_t>
    Array *ranges;  // Array<Range>
  } parts[2];
} Charset;

#define Range_toUint64(R)    (((uint64_t) (R).max) << 32 | (R).min)
#define Range_getMaxFrom(iR) ((uint32_t) ((iR) >> 32))
#define Range_getMinFrom(iR) ((uint32_t) ((iR) & 0xFFFFFFFF))
#define Range_fromUint64(iR) {.max = Range_getMaxFrom(iR), .min = Range_getMinFrom(iR)}
#define Range_cover(R, chr) ((R).min <= chr && chr <= (R).max)
#define Range_intersect(R1, R2) (Range_cover(R1, (R2).min) || Range_cover(R1, (R2).max))

void releaseBranch(Branch *branch, const Allocator *allocator);
void releaseGroup(Group *group, const Allocator *allocator);
void releaseObject(Object *object, const Allocator *allocator);
void releaseCharset(Charset *charset, const Allocator *allocator);
void releaseSequence(Sequence *sequence, const Allocator *allocator);
void releaseQuantified(Quantified *quantified, const Allocator *allocator);
void releaseUnitArray(UnitArray *unitArray, const Allocator *);
void releaseUnit(Unit *unit, const Allocator *allocator);

void Charset_update(Charset *old, const Charset *new, bool inverse);
void Plain_set_update(Array *plain_array, uint32_t plain);
void Range_set_update(Array *range_array, Range range);

#endif  // REGEX_GRAMMAR_REGEX_TARGET_H
