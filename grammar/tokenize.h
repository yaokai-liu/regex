/**
 * Project Name: regex
 * Module Name:
 * Filename: token.h
 * Creator: Yaokai Liu
 * Create Date: 24-6-25
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_TOKENIZE_H
#define REGEX_TOKENIZE_H

#include "char_t.h"
#include "terminal.h"
#include <stdint.h>

uint32_t pass_space(const char *input, uint32_t *lineno, uint32_t *column);

uint32_t single_tokenize(const char_t *input, Terminal *result,
                         uint32_t env, const Allocator *allocator);

const Terminal *tokenize(
  const char_t *input, uint32_t *cost, uint32_t *n_tokens, uint32_t *lineno,
  uint32_t *column, const Allocator * allocator
);

const char_t *get_name(uint16_t type);

#endif  // REGEX_TOKENIZE_H
