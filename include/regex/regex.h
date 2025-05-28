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
 * Filename: regex.h
 * Creator: Yaokai Liu
 * Create Date: 2025-05-26
 * Copyright (c) 2025 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_REGEX_H
#define REGEX_REGEX_H

#include "tokenizer.h"
#include "char_t.h"
#include "token.h"
#include "types.h"

typedef Tokenizer RegexTokenizer;

const Terminal *regex_tokenize(const char_t *input, uint32_t *cost, uint32_t *n_tokens, uint32_t *lineno,
                               uint32_t *column, const Allocator *allocator);

void RegexTokenizer_init(RegexTokenizer *tokenizer, const char_t *src, const Allocator *allocator);


#endif //REGEX_REGEX_H
