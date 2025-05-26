/* License
 *
 * ${PROJ_DESCRIPTION}
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
 * Module Name:
 * Filename: common.h
 * Creator: Yaokai Liu
 * Create Date: 2025-05-26
 * Copyright (c) 2025 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_COMMON_H
#define REGEX_COMMON_H

#include "allocator.h"
#include "array.h"
#include <stdint.h>

typedef Array Regex;
typedef Array Branch;
typedef Array Sequence;

typedef struct Object {
  uint32_t type;
  bool     inverse;
  bool     assertion;
  uint32_t min_times;
  uint32_t max_times;
  void *target;
} Object;

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

#endif //REGEX_COMMON_H
