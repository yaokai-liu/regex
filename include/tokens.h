/**
 * License
 *
 * x-regex - A light regular expression and its compiler
 * Copyright (C) 2024 Yaokai Liu
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
 * Project Name: regex
 * Module Name: grammar
 * Filename: tokens.h
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/


#ifndef REGEX_TOKENS_H
#define REGEX_TOKENS_H

#include "char_t.h"
#include <stdint.h>

enum TOKEN_TYPE_ENUM: uint32_t {
  enum_ASSIGNER = 1,
  enum_Affixed = 2,
  enum_Assertion = 3,
  enum_Branch = 4,
  enum_CHARSET_ESCAPE = 5,
  enum_COMMA = 6,
  enum_Charset = 7,
  enum_EXCLAIMA = 8,
  enum_Element = 9,
  enum_Group = 10,
  enum_INVERSE = 11,
  enum_LEFT_PARENTHESIS = 12,
  enum_LEFT_SQUARE_BRACKET = 13,
  enum_MINUS = 14,
  enum_Object = 15,
  enum_QUANTIFIER = 16,
  enum_Quantified = 17,
  enum_RIGHT_PARENTHESIS = 18,
  enum_RIGHT_SQUARE_BRACKET = 19,
  enum_Range = 20,
  enum_Regex = 21,
  enum_SPLIT = 22,
  enum_SYMBOL = 23,
  enum_TERMINATOR = 24,
  enum_Unit = 25,
  enum_UnitArray = 26,
  MAX_REAL_TOKEN = 27,
  enum_PLACE_HOLDER,
  MAX_TOTAL_TOKEN,
  enum_BAD_TOKEN = UINT32_MAX
};
extern const char_t *TOKEN_NAMES[];
#endif  // REGEX_TOKENS_H
