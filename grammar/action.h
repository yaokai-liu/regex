/**
 * Project Name: regex
 * Module Name:
 * Filename: actions.h
 * Creator: Yaokai Liu
 * Create Date: 24-6-26
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_ACTION_H
#define REGEX_ACTION_H

#include <stdint.h>

typedef struct state state;
struct grammar_action {
  enum : uint8_t {
    reject = 0,
    stack = 1,
    reduce = 2
  } action      : 4;
  uint8_t count : 4;
  uint8_t type;
  const uint16_t offset;
};

#endif  // REGEX_ACTION_H
