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
 * Module Name: grammar/tokenize
 * Filename: XLRTokenizer.h
 * Creator: Yaokai Liu
 * Create Date: 2025-05-24
 * Copyright (c) 2025 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_GRAMMAR_XLR_TOKENIZER_H
#define REGEX_GRAMMAR_XLR_TOKENIZER_H


#include "char_t.h"
#include "token.h"
#include "Tokenizer.h"
#include "trie.h"
#include <stdint.h>

typedef struct XLRTokenizer {
  Tokenizer SUPER;
  Array *   ident_array;  // Array<Identifier>
  Trie *    ident_trie;   // Trie<char_t, Identifier>
} XLRTokenizer;

const Terminal *
xlr_tokenize(const char_t *input, uint32_t *cost, Array *ident_array, uint32_t *n_tokens, uint32_t *lineno,
             uint32_t *column, const Allocator *allocator);

XLRTokenizer *XLRTokenizer_new(const char_t *src, Array *ident_array, const Allocator *allocator);
void XLRTokenizer_destroy(XLRTokenizer *tokenizer);

#endif //REGEX_GRAMMAR_XLR_TOKENIZER_H
