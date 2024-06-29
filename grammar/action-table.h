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

#include <stdint.h>
#include "target.h"

typedef struct state state;
typedef struct action {
  enum : uint16_t {
    reject = 0,
    stack = 1,
    reduce = 2
  } action;
  uint16_t type;
  int32_t count;
  union {
    const state * state;
    fn_product * product;
  } target;
} action;

action * getAction(const state * state, uint32_t ahead);
state * jump(const state * state, uint32_t current);

#endif  // REGEX_ACTION_TABLE_H
