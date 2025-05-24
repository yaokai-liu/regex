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
 * Filename: Tokenizer.h
 * Creator: Yaokai Liu
 * Create Date: 2025-05-24
 * Copyright (c) 2025 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_GRAMMAR_TOKENIZER_H
#define REGEX_GRAMMAR_TOKENIZER_H

#include "array.h"
#include "char_t.h"
#include "error.h"
#include "token.h"

typedef struct Tokenizer Tokenizer;
typedef uint32_t tokenizer_next_t(Tokenizer *tokenizer, Token *token, ErrInfo *err_info, const Allocator *allocator);

typedef struct Tokenizer {
  const Allocator *allocator;
  const char_t *src;
  uint32_t cost;
  uint32_t lineno;
  uint32_t column;
  tokenizer_next_t *next;
} Tokenizer;

uint32_t pass_whitespace(const char_t * input);
uint32_t pass_space(const char *input, uint32_t *lineno, uint32_t *column);


#endif //REGEX_GRAMMAR_TOKENIZER_H
