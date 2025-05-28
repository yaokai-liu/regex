/* License
 *
 * x-regex - A light regular expression and its compiler
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
 * Filename: token.h
 * Creator: Yaokai Liu
 * Create Date: 24-6-29
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_TOKEN_H
#define REGEX_TOKEN_H

#include "allocator.h"
#include "char_t.h"
#include <stdint.h>

/// location of a Token in a file
typedef struct Location {
  /// Offset in src string
  uint32_t offset;
  /// line number in src file
  uint32_t lineno;
  /// column offset in the line in src file
  uint32_t column;
  /// length of the token (size in bytes)
  uint32_t length;
} Location;

typedef struct Terminal {
  Location location;
  /// Token Type
  uint32_t type;
  /// Version in standard: [0] enable; [1] deprecated.
  uint16_t mark[2];
  /// value of the token
  void *value;
} Terminal, Token;

const char_t *get_name(uint16_t type);

#endif  // REGEX_TOKEN_H
