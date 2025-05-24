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
 * Filename: error.h
 * Creator: Yaokai Liu
 * Create Date: 2025-05-15
 * Copyright (c) 2025 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_GRAMMAR_ERROR_H
#define REGEX_GRAMMAR_ERROR_H

#include "token.h"

enum ERROR_TYPE_ENUM {
  SUCCESS = 0,
  ERROR_UNRECOGNIZED_SYMBOL,
};

typedef struct ErrInfo {
  TokenLoc pos;
  uint32_t code;
  int32_t  state;
  uint32_t token;
} ErrInfo;

#endif  // REGEX_GRAMMAR_ERROR_H
