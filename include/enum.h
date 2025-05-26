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
 * Module Name:
 * Filename: enum.h
 * Creator: Yaokai Liu
 * Create Date: 2025-05-04
 * Copyright (c) 2025 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_ENUM_H
#define REGEX_ENUM_H

#include "tokens.h"

enum REGEX_GRAMMAR_EXTEND_TYPE_ENUM {
  enum_Sequence = MAX_TOTAL_TOKEN + 1,
  enum_TOKEN
};

enum REGEX_ESCAPED_CHARSET_ENUM {
  // decimal number digital: [0-9]
  CHARSET_DEC_DIGITAL,
  // hexadecimal number digital: [0-9a-fA-F]
  CHARSET_HEX_DIGITAL,
  // identifier character: [a-zA-Z_]
  CHARSET_IDENT,
  // letter: [a-zA-Z]
  CHARSET_LETTER,
  // lower letter: [a-z]
  CHARSET_LOWER_LETTER,
  // upper letter: [A-Z]
  CHARSET_UPPER_LETTER,
};

#endif  // REGEX_ENUM_H
