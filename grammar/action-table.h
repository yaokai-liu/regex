/**
 * Project Name: regex
 * Module Name: grammar
 * Filename: action-table.h
 * Creator: Yaokai Liu
 * Create Date: 24-6-29
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_ACTION_TABLE_H
#define REGEX_ACTION_TABLE_H

#include "target.h"
#include <stdint.h>

typedef struct state state;
typedef struct action {
  enum : uint8_t {
    reject = 0,
    stack = 1,
    reduce = 2
  } action     : 4;
  uint8_t count: 4;
  uint8_t type;
  const uint16_t offset;
} action;

const action *getAction(uint32_t index, uint32_t ahead);
int32_t jump(uint32_t index, uint32_t current);
const state *getState(uint16_t index);

#endif  // REGEX_ACTION_TABLE_H
