/* License
 *
 * xRegex - a Kind of Regular Expression
 * Copyright (C) 2025 Yaokai Liu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *
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
#include "token.h"
#include <stdint.h>

typedef Array Regex;
typedef Array Branch;
typedef Array UnitArray;
typedef Array Sequence;

typedef struct Object {
  uint32_t type;
  uint16_t inverse;
  uint16_t assertion;
  uint32_t min_times;
  uint32_t max_times;
  void *target;
} Object, Assertion, Quantified, Affixed, Element;

typedef struct Quantifier {
  uint32_t min;
  uint32_t max;
} Quantifier;

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

#define Quantifier_toUint64(Q) (((uint64_t) (Q).max) << 32 | (Q).min)
#define Quantifier_getMaxFrom(iQ) ((uint32_t) ((iQ) >> 32))
#define Quantifier_getMinFrom(iQ) ((uint32_t) ((iQ) & 0xFFFFFFFF))
#define Quantifier_fromUint64(iQ) {.max = Range_getMaxFrom(iQ), .min = Range_getMinFrom(iQ)}

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
void releaseUnitArray(UnitArray *unitArray, const Allocator *);
void releaseUnit(Unit *unit, const Allocator *allocator);

void Charset_update(Charset *old, const Charset *new, bool inverse);
void Plain_set_update(Array *plain_array, uint32_t plain);
void Range_set_update(Array *range_array, Range range);

#endif  // REGEX_GRAMMAR_REGEX_TARGET_H
