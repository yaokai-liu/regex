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
 * Filename: XLRTokenizer.c
 * Creator: Yaokai Liu
 * Create Date: 2025-05-24
 * Copyright (c) 2025 Yaokai Liu. All rights reserved.
 **/

#include "xlr.h"
#include "enum.h"
#include "string_t.h"
#include "regex/target.h"

#define str_lit_len(str_literal) ((sizeof str_literal) - 1)
#define startswithDigital(pText) ('0' <= (pText)[0] && (pText)[0] <= '9')
#define startswithLetter(pText) \
  (('a' <= (pText)[0] && (pText)[0] <= 'z') || ('A' <= (pText)[0] && (pText)[0] <= 'Z'))

uint32_t t_IDENTIFIER(XLRTokenizer *tokenizer, Terminal *result, const Allocator *allocator);
uint32_t xlr_single_tokenize(XLRTokenizer *tokenizer, Terminal *result, const Allocator *allocator);
uint32_t XLRTokenizer_next(Tokenizer *tokenizer, Token *token, ErrInfo *, const Allocator *allocator);
uint64_t get_char(const void *key);

inline uint32_t t_IDENTIFIER(XLRTokenizer *tokenizer, Terminal *const result, const Allocator *allocator) {
  const char_t *input = tokenizer->SUPER.src + tokenizer->SUPER.offset;
  const char_t *pText = input;
  if (startswithLetter(pText) || (*pText == '_')) { pText++; } else { return 0; }
  while (true) {
    if (startswithLetter(pText) || startswithDigital(pText) || (*pText == '_')) { pText++; }
    else { break; }
  }
  const uint32_t length = pText - input;
  result->type = enum_SYMBOL;
  result->value = allocator->calloc(length + 1, sizeof(char_t));
  allocator->memcpy(result->value, input, length);
  ((char_t *) result->value)[length] = '\0';
  REFER(char_t) v_ident = Trie_get(tokenizer->ident_trie, result->value);
  if (!v_ident) {
    v_ident = Array_last_virt(tokenizer->ident_array) + 1;
    Array_append(tokenizer->ident_array, result->value, length + 1);
    Trie_set(tokenizer->ident_trie, result->value, v_ident);
  }
  allocator->free(result->value);
  result->value = v_ident;
  result->location.length = pText - input;
  return result->location.length;
}

const char_t XLR_TERMINALS[] = "()|^=;";
enum TOKEN_TYPE_ENUM XLR_TERMINAL_TYPES[] = {
    enum_LEFT_PARENTHESIS, enum_RIGHT_PARENTHESIS,
    enum_SPLIT, enum_INVERSE, enum_ASSIGNER, enum_SEMICOLON
};

inline uint32_t
xlr_single_tokenize(XLRTokenizer *tokenizer, Terminal *result, const Allocator *allocator) {
  const char_t *input = tokenizer->SUPER.src + tokenizer->SUPER.offset;
  const char_t *pText = input;
  if (!*pText) {
    result->type = enum_TERMINATOR;
    result->location.length = 0;
    result->value = nullptr;
    return REGEX_SUCCESS;
  }
  uint32_t idx = stridx_o(XLR_TERMINALS, *pText);
  if (idx < str_lit_len(XLR_TERMINALS)) {
    result->type = XLR_TERMINAL_TYPES[idx];
    result->value = nullptr;
    result->location.length  = 1;
    tokenizer->SUPER.column += 1;
    tokenizer->SUPER.offset += 1;
    return REGEX_SUCCESS;
  }
  switch (*pText) {
    case '*': {
      Quantifier quant = { .min = 0, .max = 0 };
      result->type = enum_QUANTIFIER;
      result->value = (void *) Quantifier_toUint64(quant);
      result->location.length  = 1;
      tokenizer->SUPER.column += 1;
      tokenizer->SUPER.offset += 1;
      return REGEX_SUCCESS;
    }
    case '+': {
      Quantifier quant = { .min = 1, .max = 0 };
      result->type = enum_QUANTIFIER;
      result->value = (void *) Quantifier_toUint64(quant);
      result->location.length  = 1;
      tokenizer->SUPER.column += 1;
      tokenizer->SUPER.offset += 1;
      return REGEX_SUCCESS;
    }
    case '?': {
      Quantifier quant = { .min = 0, .max = 1 };
      result->type = enum_QUANTIFIER;
      result->value = (void *) Quantifier_toUint64(quant);
      result->location.length  = 1;
      tokenizer->SUPER.column += 1;
      tokenizer->SUPER.offset += 1;
      return REGEX_SUCCESS;
    }
    default: {}
  }
  uint32_t length = t_IDENTIFIER(tokenizer, result, allocator);
  if (!length) { return REGEX_ERROR_UNRECOGNIZED_SYMBOL; }
  tokenizer->SUPER.column += length;
  tokenizer->SUPER.offset += length;
  return REGEX_SUCCESS;
}

const Terminal *
xlr_tokenize(const char_t *input, uint32_t *cost, Array *ident_array, uint32_t *n_tokens, uint32_t *lineno,
             uint32_t *column, const Allocator *allocator) {  // NOLINT(*-easily-swappable-parameters)
  XLRTokenizer *tokenizer = XLRTokenizer_new(input, ident_array, allocator);
  Array *terminals = Array_new(sizeof(Terminal), enum_TOKEN, allocator);
  const uint32_t max_cost = (*cost) > 0 ? *cost : UINT32_MAX;
  tokenizer->SUPER.lineno = lineno ? *lineno : 0;
  tokenizer->SUPER.column = column ? *column : 0;
  Terminal terminal = {};
  ErrInfo errInfo = {};

  do {
    *cost = XLRTokenizer_next((Tokenizer *) tokenizer, &terminal, &errInfo, allocator);
    if (*cost == REGEX_SUCCESS) { Array_append(terminals, &terminal, 1); } else { break; }
  } while (terminal.type != enum_TERMINATOR && tokenizer->SUPER.offset < max_cost);

  *cost = tokenizer->SUPER.offset;
  lineno ? *lineno = tokenizer->SUPER.lineno : 0;
  column ? *column = tokenizer->SUPER.column : 0;
  *n_tokens = Array_length(terminals);
  XLRTokenizer_destroy(tokenizer);
  const Terminal *pTerminals = (*n_tokens == 0) ? nullptr : Array_real_addr(terminals, 0);
  if (*n_tokens == 0) { releasePrimeArray(terminals); } else { Array_destroy(terminals); }
  return pTerminals;
}


XLRTokenizer *XLRTokenizer_new(const char_t *src, Array *ident_array, const Allocator *allocator) {
  XLRTokenizer *tokenizer = allocator->calloc(1, sizeof(XLRTokenizer));
  tokenizer->ident_trie = Trie_new(sizeof(char_t), get_char, allocator);
  tokenizer->SUPER.next = XLRTokenizer_next;
  tokenizer->SUPER.allocator = allocator;
  tokenizer->ident_array = ident_array;
  tokenizer->SUPER.lineno = 1;
  tokenizer->SUPER.column = 1;
  tokenizer->SUPER.src = src;
  tokenizer->SUPER.offset = 0;
  return tokenizer;
}

void XLRTokenizer_destroy(XLRTokenizer *tokenizer) {
  Trie_destroy(tokenizer->ident_trie);
  tokenizer->SUPER.allocator->free(tokenizer);
}

uint32_t XLRTokenizer_next(Tokenizer *tokenizer, Token *token, ErrInfo *errInfo, const Allocator *allocator) {
  tokenizer->offset += pass_space(tokenizer->src + tokenizer->offset, &tokenizer->lineno, &tokenizer->column);
  token->location.lineno = tokenizer->lineno;
  token->location.column = tokenizer->column;
  token->location.offset = tokenizer->offset;
  uint32_t result = xlr_single_tokenize((XLRTokenizer *) tokenizer, token, allocator);
  if (result != REGEX_SUCCESS) {
    errInfo->pos.lineno = tokenizer->lineno;
    errInfo->pos.column = tokenizer->column;
    errInfo->pos.offset = tokenizer->offset;
    errInfo->code = result;
    return result;
  }
  return REGEX_SUCCESS;
}

uint64_t get_char(const void *key) {
  return *(const char_t *) key;
}
