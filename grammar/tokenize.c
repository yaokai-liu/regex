/**
 * Project Name: regex
 * Module Name:
 * Filename: token.c
 * Creator: Yaokai Liu
 * Create Date: 2024-6-25
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "tokenize.h"
#include "allocator.h"
#include "array.h"
#include "generated/tokens.gen.h"
#include "regex/target.h"
#include "string_t.h"
#include "terminal.h"
#include <stdint.h>

#define lenof(a)                 ((sizeof a) / sizeof(a[0]))
#define str_lit_len(str_literal) ((sizeof str_literal) - 1)
#define max(a, b)                ((a) > (b) ? (a) : (b))
#define min(a, b)                ((a) < (b) ? (a) : (b))

#define startswithDigital(pText) ('0' <= (pText)[0] && (pText)[0] <= '9')
#define startswithLetter(pText) \
  (('a' <= (pText)[0] && (pText)[0] <= 'z') || ('A' <= (pText)[0] && (pText)[0] <= 'Z'))

uint32_t t_NUMBER_adic10(const char_t *input, Terminal *result, const Allocator *allocator);
uint32_t try_tokenize_QUANTIFIER_EXPR(const char_t *input, Terminal *result, const Allocator *allocator);
uint32_t t_ESCAPE(const char_t *input, Terminal *result, const Allocator *allocator);
uint32_t pass_whitespace(const char_t * input);

inline uint32_t t_NUMBER_adic10(const char_t * const input, Terminal * const result,
                                const Allocator * const) {
  const char_t *pText = input;
  uint64_t value = 0;
  while (true) {
    if (startswithDigital(pText)) {
      value = (value * 10) + (*pText++ - '0');  // NOLINT(*-magic-numbers)
      continue;
    }
    if (startswithLetter(pText)) {
      result->location.length = pText - input;
      return 0;
    }
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

uint32_t try_tokenize_QUANTIFIER_EXPR(const char_t *input, Terminal *result, const Allocator *allocator) {
  const char_t *pText = input + 1;
  Quantifier quant = { .min = 0, .max = 0 };

  pText += pass_whitespace(pText);
  uint32_t length = t_NUMBER_adic10(pText, result, allocator);
  if (length) { quant.min = (uint32_t) (uint64_t) result->value; pText += length; }

  pText += pass_whitespace(pText);
  if (*pText == ',') { pText++; }
  else if (*pText == '}') { quant.max = quant.min; pText ++; goto __compose_and_return; }
  else { goto __failed_fall_through; }

  pText += pass_whitespace(pText);
  if (*pText == '}') { pText ++; goto __compose_and_return; }
  length = t_NUMBER_adic10(pText, result, allocator);
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
  result->type = enum_CHAR;
  result->value = (void *) (uint64_t) '{';
  result->location.length = 1;
  return 1;
}

#define ESCAPE_LITERALS "aAdw"

inline uint32_t t_ESCAPE(const char_t * const input, Terminal * const result,
                         const Allocator * const) {
  const char_t *sp = input + 1;
  if (!*sp) { return 0; }
  if (startswithLetter(sp)) {
    uint32_t idx = stridx_o(ESCAPE_LITERALS, *sp);
    if (idx >= str_lit_len(ESCAPE_LITERALS)) { return 0; }
    result->type = enum_SET_ESCAPE;
    result->location.length = 2;
    result->mark[0] = false;
    result->value = (void *) (uint64_t) idx;
  } else {
    result->type = enum_CHAR;
    result->location.length = 2;
    result->value = (void *) (uint64_t) *sp;
  }
  return result->location.length;
}

const char_t TERMINALS[] = "[]()|-!^";
enum TOKEN_TYPE_ENUM TERMINAL_TYPES[] = {
    enum_LEFT_SQUARE_BRACKET, enum_RIGHT_SQUARE_BRACKET,
    enum_LEFT_PARENTHESIS, enum_RIGHT_PARENTHESIS,
    enum_SPLIT, enum_MINUS, enum_EXCLAIMA, enum_INVERSE,
};

inline uint32_t single_tokenize(const char_t * const input, Terminal * const result, const Allocator * const allocator) {
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
    return t_ESCAPE(input, result, allocator);
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
      return try_tokenize_QUANTIFIER_EXPR(input, result, allocator);
    }
    default: {}
  }
  result->type = enum_CHAR;
  result->value = (void *) (uint64_t) *input;
  result->location.length = 1;
  return 1;
}

const Terminal *
  tokenize(const char_t * const input, uint32_t *cost, uint32_t *n_tokens, uint32_t * const lineno,
           uint32_t * const column,
           const Allocator * const allocator) {  // NOLINT(*-easily-swappable-parameters)
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
    *cost = single_tokenize(pText, &terminal, allocator);
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

#define WHITESPACES " \t\n\f\v\r"
uint32_t pass_whitespace(const char_t * const input) {
  const char_t *pText = input;
  while (*pText && stridx_o(WHITESPACES, *pText) < str_lit_len(WHITESPACES)) { pText++; }
  return pText - input;
}

uint32_t pass_space(const char * const input, uint32_t * const lineno, uint32_t * const column) {
  uint32_t l = lineno ? *lineno : 0;
  uint32_t c = column ? *column : 0;
  const char *pText = input;
  while (*pText) {
    switch (*pText) {
      case '\n': {
        l++;
        c = 1;
        break;
      }
      case '\f':
      case '\r':
      case ' ':
      case '\t': {
        c++;
        break;
      }
      default: {
        goto __return;
      }
    }
    pText++;
  }
__return:
  lineno ? *lineno = l : 0;
  column ? *column = c : 0;
  return pText - input;
}

const char_t *get_name(uint16_t type) {
  return TOKEN_NAMES[type];
}
