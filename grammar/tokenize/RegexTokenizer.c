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
 * Filename: RegexTokenizer.c
 * Creator: Yaokai Liu
 * Create Date: 2024-6-25
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "RegexTokenizer.h"
#include "allocator.h"
#include "array.h"
#include "regex/target.h"
#include "string_t.h"
#include "token.h"
#include "enum.h"
#include <stdint.h>

#define str_lit_len(str_literal) ((sizeof str_literal) - 1)
#define max(a, b)                ((a) > (b) ? (a) : (b))
#define min(a, b)                ((a) < (b) ? (a) : (b))

#define startswithDigital(pText) ('0' <= (pText)[0] && (pText)[0] <= '9')
#define startswithLetter(pText) \
  (('a' <= (pText)[0] && (pText)[0] <= 'z') || ('A' <= (pText)[0] && (pText)[0] <= 'Z'))

uint32_t regex_t_NUMBER_adic10(const char_t *input, Terminal *result, const Allocator *);
uint32_t regex_try_tokenize_QUANTIFIER_EXPR(const char_t *input, Terminal *result, const Allocator *allocator);
uint32_t regex_t_ESCAPE(const char_t *input, Terminal *result, const Allocator *allocator);
uint32_t regex_single_tokenize(const char_t *input, Terminal *result, const Allocator *allocator);

uint32_t RegexTokenizer_next(RegexTokenizer *tokenizer, Token *token, ErrInfo *, const Allocator *allocator);

inline uint32_t regex_t_NUMBER_adic10(const char_t *const input, Terminal *const result,
                                      const Allocator *) {
  const char_t *pText = input;
  uint64_t value = 0;
  while (true) {
    if (startswithDigital(pText)) {
      value = (value * 10) + (*pText++ - '0');  // NOLINT(*-magic-numbers)
      continue;
    }
    if (startswithLetter(pText)) { return 0; }
    if (*pText == '\'') {
      pText++;
    } else {
      break;
    }
  }
  result->value = (void *) value;
  result->location.length = pText - input;
  return result->location.length;
}

uint32_t regex_try_tokenize_QUANTIFIER_EXPR(const char_t *input, Terminal *result, const Allocator *allocator) {
  const char_t *pText = input + 1;
  Quantifier quant = { .min = 0, .max = 0 };

  pText += pass_whitespace(pText);
  uint32_t length = regex_t_NUMBER_adic10(pText, result, allocator);
  if (length) { quant.min = (uint32_t) (uint64_t) result->value; pText += length; }

  pText += pass_whitespace(pText);
  if (*pText == ',') { pText++; }
  else if (*pText == '}') { quant.max = quant.min; pText ++; goto __compose_and_return; }
  else { goto __failed_fall_through; }

  pText += pass_whitespace(pText);
  if (*pText == '}') { pText ++; goto __compose_and_return; }
  length = regex_t_NUMBER_adic10(pText, result, allocator);
  quant.max = length == 0 ? 0 : (uint64_t) result->value;
  pText += length;

  pText += pass_whitespace(pText);
  if (*pText != '}') { goto __failed_fall_through; }
  pText++;

__compose_and_return:
  result->type = enum_QUANTIFIER;
  result->value = (void *) Quantifier_toUint64(quant);
  result->location.length = pText - input;
  return result->location.length;

__failed_fall_through:
  result->type = enum_SYMBOL;
  result->value = (void *) (uint64_t) '{';
  result->location.length = 1;
  return 1;
}

const char_t ESCAPE_LITERALS[] = {
    [CHARSET_DEC_DIGITAL] = 'd',
    [CHARSET_HEX_DIGITAL] = 'D',
    [CHARSET_LETTER] = 'w',
    [CHARSET_IDENT] = 'W',
    [CHARSET_LOWER_LETTER] = 'a',
    [CHARSET_UPPER_LETTER] = 'A',
    0
};

inline uint32_t regex_t_ESCAPE(const char_t *input, Terminal *result, const Allocator *) {
  const char_t *pText = input + 1;
  if (!*pText) { return 0; }
  if (startswithLetter(pText)) {
    uint32_t idx = stridx_o(ESCAPE_LITERALS, *pText);
    if (idx >= str_lit_len(ESCAPE_LITERALS)) { return 0; }
    result->type = enum_CHARSET_ESCAPE;
    result->location.length = 2;
    result->mark[0] = false;
    result->value = (void *) (uint64_t) idx;
  } else {
    result->type = enum_SYMBOL;
    result->location.length = 2;
    result->value = (void *) (uint64_t) *pText;
  }
  return result->location.length;
}

const char_t TERMINALS[] = "[]()|-!^";
enum TOKEN_TYPE_ENUM TERMINAL_TYPES[] = {
    enum_LEFT_SQUARE_BRACKET, enum_RIGHT_SQUARE_BRACKET,
    enum_LEFT_PARENTHESIS, enum_RIGHT_PARENTHESIS,
    enum_SPLIT, enum_MINUS, enum_EXCLAIMA, enum_INVERSE,
};

inline uint32_t regex_single_tokenize(const char_t *input, Terminal *result, const Allocator *allocator) {
  if (!*input) {
    result->type = enum_TERMINATOR;
    result->location.length = 0;
    result->value = nullptr;
    return 0;
  }
  uint32_t idx = stridx_o(TERMINALS, *input);
  if (idx < str_lit_len(TERMINALS)) {
    result->type = TERMINAL_TYPES[idx];
    result->value = nullptr;
    return 1;
  }
  if (*input == '\\') {
    return regex_t_ESCAPE(input, result, allocator);
  }
  switch (*input) {
    case '*': {
      Quantifier quant = { .min = 0, .max = 0 };
      result->type = enum_QUANTIFIER;
      result->value = (void *) Quantifier_toUint64(quant);
      result->location.length = 1;
      return result->location.length;
    }
    case '+': {
      Quantifier quant = { .min = 1, .max = 0 };
      result->type = enum_QUANTIFIER;
      result->value = (void *) Quantifier_toUint64(quant);
      result->location.length = 1;
      return result->location.length;
    }
    case '?': {
      Quantifier quant = { .min = 0, .max = 1 };
      result->type = enum_QUANTIFIER;
      result->value = (void *) Quantifier_toUint64(quant);
      result->location.length = 1;
      return result->location.length;
    }
    case '{': {
      return regex_try_tokenize_QUANTIFIER_EXPR(input, result, allocator);
    }
    default: {}
  }
  result->type = enum_SYMBOL;
  result->value = (void *) (uint64_t) *input;
  result->location.length = 1;
  return 1;
}

const Terminal *
  regex_tokenize(const char_t *input, uint32_t *cost, uint32_t *n_tokens, uint32_t *lineno,
                 uint32_t *column, const Allocator *allocator) {  // NOLINT(*-easily-swappable-parameters)
  const char_t *pText = input;
  const uint32_t max_cost = (*cost) > 0 ? *cost : UINT32_MAX;
  *cost = 0;
  uint32_t l = lineno ? *lineno : 0;
  uint32_t c = column ? *column : 0;
  Array *terminals = Array_new(sizeof(Terminal), enum_TERMINATOR, allocator);
  Terminal terminal = {};
  pText += pass_space(pText, &l, &c);
  while (*pText && pText - input < max_cost) {
    terminal.location.lineno = l;
    terminal.location.column = c;
    *cost = regex_single_tokenize(pText, &terminal, allocator);
    c += terminal.location.length;
    if (0 == *cost) { break; }
    pText += *cost;
    pText += pass_space(pText, &l, &c);
    Array_append(terminals, &terminal, 1);
  }
  if ('\0' == *pText) {
    terminal.type = enum_TERMINATOR;
    terminal.value = nullptr;
    terminal.location.lineno = l;
    terminal.location.column = c;
    terminal.location.length = 0;
    Array_append(terminals, &terminal, 1);
  }
  *cost = (uint32_t) (pText - input);
  *n_tokens = Array_length(terminals);
  const Terminal *pTerminals = (*n_tokens == 0) ? nullptr : Array_real_addr(terminals, 0);
  Array_destroy(terminals);
  lineno ? *lineno = l : 0;
  column ? *column = c : 0;
  return pTerminals;
}

inline void RegexTokenizer_init(RegexTokenizer *tokenizer, const char_t *src, const Allocator *allocator) {
  tokenizer->allocator = allocator;
  tokenizer->src = src;
  tokenizer->lineno = 1;
  tokenizer->column = 1;
  tokenizer->offset = 0;
  tokenizer->next = RegexTokenizer_next;
}


uint32_t RegexTokenizer_next(RegexTokenizer *tokenizer, Token *token, ErrInfo *, const Allocator *allocator) {
  tokenizer->offset += pass_space(tokenizer->src + tokenizer->offset, &tokenizer->lineno, &tokenizer->column);
  token->location.lineno = tokenizer->lineno;
  token->location.column = tokenizer->column;
  token->location.offset = tokenizer->offset;
  uint32_t length = regex_single_tokenize(tokenizer->src, token, allocator);
  tokenizer->column += length;
  tokenizer->offset += length;
  return SUCCESS;
}
