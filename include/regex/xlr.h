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
 * Filename: xLR.h
 * Creator: Yaokai Liu
 * Create Date: 2025-05-26
 * Copyright (c) 2025 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_XLR_H
#define REGEX_XLR_H

#include "token.h"
#include "tokenizer.h"
#include "trie.h"
#include "types.h"

typedef struct XLRTokenizer {
  Tokenizer SUPER;
  bool end_of_rule;
  Array *ident_array;  // Array<Identifier>
  Trie *ident_trie;  // Trie<char_t, Identifier>
} XLRTokenizer;

const Terminal *xlr_tokenize(const char_t *input, uint32_t *cost, Array *ident_array, uint32_t *n_tokens,
                             uint32_t *lineno, uint32_t *column, const Allocator *allocator);

XLRTokenizer *XLRTokenizer_new(const char_t *src, Array *ident_array, Trie *ident_trie, const Allocator *allocator);
void XLRTokenizer_destroy(XLRTokenizer *tokenizer);

#endif  // REGEX_XLR_H
