/**
 * Project Name: regex
 * Module Name: grammar
 * Filename: target.c
 * Creator: Yaokai Liu
 * Create Date: 2024-07-13
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "target.h"
#include "allocator.h"
#include "enum.h"
#include "generated/tokens.gen.h"

const Range ESCAPE_RANGES[] = {
  {.min = 'a', .max = 'z'},
  {.min = 'A', .max = 'Z'},
  {.min = '0', .max = '9'},
};
const ConstCharset ESCAPE_CHARSETS[] = {
  {{[CT_NORMAL] = {.n_plains = 0, .plains = nullptr, .n_ranges = 1, .ranges = &ESCAPE_RANGES[1]},
    [CT_INVERSE] = {.n_plains = 0, .plains = nullptr, .n_ranges = 0, .ranges = nullptr}}},
  {{[CT_NORMAL] = {.n_plains = 0, .plains = nullptr, .n_ranges = 1, .ranges = &ESCAPE_RANGES[1]},
    [CT_INVERSE] = {.n_plains = 0, .plains = nullptr, .n_ranges = 0, .ranges = nullptr}}},
  {{[CT_NORMAL] = {.n_plains = 0, .plains = nullptr, .n_ranges = 1, .ranges = &ESCAPE_RANGES[2]},
    [CT_INVERSE] = {.n_plains = 0, .plains = nullptr, .n_ranges = 0, .ranges = nullptr}}},
  {{[CT_NORMAL] = {.n_plains = 0, .plains = nullptr, .n_ranges = 3, .ranges = &ESCAPE_RANGES[0]},
    [CT_INVERSE] = {.n_plains = 0, .plains = nullptr, .n_ranges = 0, .ranges = nullptr}}},
};

inline void releaseSequence(Sequence *sequence, const Allocator *) {
  Array_reset(sequence, nullptr);
}

inline void releaseCharset(Charset *charset, const Allocator *) {
  Set_destroy(charset->parts[0].plains);
  Set_destroy(charset->parts[0].ranges);
  Set_destroy(charset->parts[1].plains);
  Set_destroy(charset->parts[1].ranges);
}

inline void releaseGroup(Group *group, const Allocator *) {
  if (((uint64_t) group->regexp) <= enum_Regexp) { return; }
  Array_destroy(group->regexp);
}

inline void releaseBranch(Branch *branch, const Allocator *) {
  Array_reset(branch, (void (*)(void *, const Allocator *)) releaseObject);
}

inline void releaseQuantified(Quantified *quantified, const Allocator *allocator) {
  releaseObject(&quantified->object, allocator);
}

inline void releaseObject(Object *object, const Allocator *allocator) {
  switch (object->type) {
    case enum_CHAR: {
      return;
    }
    case enum_Sequence: {
      releaseSequence(object->target, allocator);
      Array_destroy(object->target);
      return;
    }
    case enum_Charset: {
      releaseCharset(object->target, allocator);
      allocator->free(object->target);
      break;
    }
    case enum_Group: {
      releaseGroup(object->target, allocator);
      allocator->free(object->target);
      break;
    }
    case enum_Quantified: {
      releaseQuantified(object->target, allocator);
      allocator->free(object->target);
      break;
    }
  }
}

inline void releaseUnitArray(UnitArray *unitArray, const Allocator *) {
  Array_reset(unitArray, (void (*)(void *, const Allocator *)) releaseUnit);
}

inline void releaseUnit(Unit *unit, const Allocator *allocator) {
  switch (unit->type) {
    case enum_CHAR: {
      break;
    }
    case enum_Range: {
      allocator->free(unit->target);
      break;
    }
    case enum_Charset: {
      releaseCharset(unit->target, allocator);
      allocator->free(unit->target);
      break;
    }
  }
}
