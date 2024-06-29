/**
 * Project Name: regex
 * Module Name: grammar
 * Filename: terminal.h
 * Creator: Yaokai Liu
 * Create Date: 24-6-29
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_TERMINAL_H
#define REGEX_TERMINAL_H

#include <stdint.h>

typedef struct {
  uint8_t type;
  uint8_t value;
} Terminal;
Terminal *tokenize(const char *input, uint32_t *cost, uint32_t *n_tokens);
extern const char TERMINALS[];
extern const int32_t N_TERMINAL;

#endif  // REGEX_TERMINAL_H
