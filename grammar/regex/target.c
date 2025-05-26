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
 * Filename: target.c
 * Creator: Yaokai Liu
 * Create Date: 2024-07-13
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "target.h"
#include "allocator.h"
#include "enum.h"
#include "tokens.h"

inline void releaseSequence(Sequence *sequence, const Allocator *) {
  Array_reset(sequence, nullptr);
}

inline void releaseCharset(Charset *charset, const Allocator *) {
  Array_destroy(charset->parts[0].plains);
  Array_destroy(charset->parts[0].ranges);
  Array_destroy(charset->parts[1].plains);
  Array_destroy(charset->parts[1].ranges);
}

inline void releaseGroup(Group *group, const Allocator *) {
  if (((uint64_t) group->regexp) <= enum_Regex) { return; }
  Array_destroy(group->regexp);
}

inline void releaseBranch(Branch *branch, const Allocator *) {
  Array_reset(branch, (void (*)(void *, const Allocator *)) releaseObject);
}

inline void releaseObject(Object *object, const Allocator *allocator) {
  switch (object->type) {
    case enum_SYMBOL: {
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
  }
}

inline void releaseUnitArray(UnitArray *unitArray, const Allocator *) {
  Array_reset(unitArray, (void (*)(void *, const Allocator *)) releaseUnit);
}

inline void releaseUnit(Unit *unit, const Allocator *allocator) {
  switch (unit->type) {
    case enum_SYMBOL: {
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



#define max(a, b) ((a) >= (b) ? (a) : (b))
#define min(a, b) ((a) <= (b) ? (a) : (b))

void Charset_update(Charset *old, const Charset *new, bool inverse) {
  auto normal_part  = &new->parts[ inverse];
  auto inverse_part = &new->parts[!inverse];
  uint32_t n_normal_plains = Array_length(normal_part->plains);
  uint32_t *normal_plains = Array_first_real(normal_part->plains);
  for (uint32_t i = 0; i < n_normal_plains; i++) {
    Plain_set_update(old->parts[CT_NORMAL].plains, normal_plains[i]);
  }
  uint32_t n_inverse_plains = Array_length(inverse_part->plains);
  uint32_t *inverse_plains = Array_first_real(inverse_part->plains);
  for (uint32_t i = 0; i < n_inverse_plains; i++) {
    Plain_set_update(old->parts[CT_INVERSE].plains, inverse_plains[i]);
  }
  uint32_t n_normal_ranges = Array_length(normal_part->ranges);
  Range *normal_ranges = Array_first_real(normal_part->ranges);
  for (uint32_t i = 0; i < n_normal_ranges; i++) {
    Range_set_update(old->parts[CT_NORMAL].ranges, normal_ranges[i]);
  }
  uint32_t n_inverse_ranges = Array_length(inverse_part->ranges);
  Range *inverse_ranges = Array_first_real(inverse_part->ranges);
  for (uint32_t i = 0; i < n_inverse_ranges; i++) {
    Range_set_update(old->parts[CT_INVERSE].ranges, inverse_ranges[i]);
  }
}

bool regular_range(const Range *range) {
  return range->min <= range->max;
}

void Range_set_update(Array *range_array, Range range) {
  uint32_t n_ranges = Array_length(range_array);
  Range *ranges = Array_first_real(range_array);
  for (uint32_t i = 0; i < n_ranges; i++) {
    if (Range_intersect(range, ranges[i])) {
      range.min = min(range.min, ranges[i].min);
      range.max = max(range.max, ranges[i].max);
      ranges[i].min = UINT32_MAX;
      ranges[i].max = 0;
    }
  }
  Array_filter(range_array, (bool (*)(const void *)) regular_range);
  Array_append(range_array, &range, 1);
}

void Plain_set_update(Array *plain_array, uint32_t plain) {
  uint32_t n_plains = Array_length(plain_array);
  uint32_t *plains = Array_first_real(plain_array);
  for (uint32_t i = 0; i < n_plains; i++) {
    if (plains[i] == plain) { return; }
  }
  Array_append(plain_array, &plain, 1);
}
