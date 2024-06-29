/**
 * Project Name: regex
 * Module Name:
 * Filename: action-table.c
 * Creator: Yaokai Liu
 * Create Date: 24-6-27
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "tokens.gen.h"
#include "reduces.gen.h"
#include "action-table.h"

struct state {
  const uint32_t ndx_base;
  const uint32_t goto_base;
  const uint32_t token_base;
  const uint32_t n_tokens;
};
struct unit {
  uint8_t type;
  uint8_t offset;
};

const struct action ACTIONS[];
const struct state *JUMPS[];
const struct unit UNITS[];
const struct state STATES[];

const struct action ACTIONS[] = {
  ${actions}
};

const struct state * JUMPS[] = {
  ${jumps}
};

const struct unit UNITS[] = {
  ${units}
};

const struct state STATES[] = {
  ${states}
};
