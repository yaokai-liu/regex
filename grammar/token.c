/**
 * Project Name: regex
 * Module Name:
 * Filename: token.c
 * Creator: Yaokai Liu
 * Create Date: 24-6-25
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "token.h"
#include "allocator.h"
#include "terminal.h"
#include "tokens.gen.h"
#include <malloc.h>
#include <stdint.h>
#define len(a) ((sizeof a) / sizeof(a[0]))

int32_t stridx_i(const char_t *string, char_t ch, int32_t len);

int32_t lex_number(const char_t *input, Terminal *token, bool is_number) {
  if (!is_number) { return 0; }
  const char_t *sp = input;
  while ('0' <= *sp && *sp < '9') {
    token->value = (token->value * 10) + *sp - '0';
    sp++;
  }
  token->type = enum_NUMBER;
  return (int32_t) (sp - input);
}

Terminal *tokenize(const char_t *input, uint32_t *cost, uint32_t *n_tokens, const Allocator * allocator) {
  uint32_t alloc_len = 32;
  uint32_t used_len = 0;
  Terminal *tokens = malloc(alloc_len * sizeof(Terminal));

  const char_t *sp = input;
  bool is_quant = false;
  while (*sp) {
    while (used_len >= alloc_len) {
      alloc_len += 32;
      Terminal *p = realloc(tokens, alloc_len * sizeof(Terminal));
      if (!p) { goto __failed_tokenize; }
      tokens = p;
    }
    int32_t idx = stridx_i(TERMINAL_STRING, *sp, N_TERMINAL);
    if (idx >= 0) {
      tokens[used_len].type = TERMINALS[idx];
      tokens[used_len].value = 0;
      if (tokens[used_len].type == enum_BEGIN_QUANTIFIER) { is_quant = true; }
      if (tokens[used_len].type == enum_END_QUANTIFIER) { is_quant = false; }
      sp++;
      used_len++;
      continue;
    }
    idx = lex_number(sp, &tokens[used_len], is_quant);
    if (idx == 0) {
      tokens[used_len].type = enum_CHAR;
      tokens[used_len].value = *sp & 0xff;
      sp++;
    } else {
      sp += idx;
    }
    used_len++;
  }
  *cost = sp - input;
  while (used_len >= alloc_len) {
    alloc_len += 32;
    Terminal *p = realloc(tokens, alloc_len * sizeof(Terminal));
    if (!p) { goto __failed_tokenize; }
    tokens = p;
  }
  tokens[used_len].type = enum_TERMINATOR;
  tokens[used_len].value = 0;
  used_len++;
  *n_tokens = used_len;
  return tokens;

__failed_tokenize:
  free(tokens);
  return nullptr;
}

int32_t stridx_i(const char_t *string, char_t ch, int32_t len) {
  for (int32_t i = 0; i < len; i++) {
    if (ch == string[i]) { return i; }
  }
  return -1;
}

const char_t *get_name(uint16_t type) {
  return REGEX_TOKEN_NAMES[type];
}
