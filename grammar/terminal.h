/**
 * Project Name: regex
 * Module Name: grammar
 * Filename: terminal.h
 * Creator: Yaokai Liu
 * Create Date: 24-6-29
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_GRAMMAR_TERMINAL_H
#define REGEX_GRAMMAR_TERMINAL_H

#include "allocator.h"
#include "char_t.h"
#include <stdint.h>

/// location of a Token in a file
typedef struct TokenLoc {
  /// Offset in src string
  uint32_t offset;
  /// line number in src file
  uint32_t lineno;
  /// column offset in the line in src file
  uint32_t column;
  /// length of the token (size in bytes)
  uint32_t length;
} TokenLoc;

typedef struct Terminal {
  TokenLoc location;
  /// Token Type
  uint32_t type;
  /// Version in standard: [0] enable; [1] deprecated.
  uint16_t mark[2];
  /// value of the token
  void *value;
} Terminal, Token;

#endif  // REGEX_GRAMMAR_TERMINAL_H
