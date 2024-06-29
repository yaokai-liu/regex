/**
 * Project Name: regex
 * Module Name:
 * Filename: action-table.gen.c
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "tokens.gen.h"
#include "reduce.gen.h"
#include "action-table.h"

struct state {
  const uint16_t ndx_base;
  const uint16_t goto_base;
  const uint16_t token_base;
  const uint16_t n_tokens;
};
struct unit {
  uint8_t type;
  uint8_t offset;
};

const struct action ACTIONS[];
const uint16_t JUMPS[];
const struct unit UNITS[];

const struct unit *getUnit(const state *state, uint32_t look);

const struct action ACTIONS[] = {
  ${actions}
};

const uint16_t JUMPS[] = {
  ${jumps}
};

const struct unit UNITS[] = {
  ${units}
};

const struct state STATES[] = {
  ${states}
};

inline const struct unit *getUnit(const state *state, uint32_t look) {
  const struct unit *unit = nullptr;
  uint32_t pad = state->n_tokens / 2;
  uint32_t u_idx = pad + state->token_base;
  unit = &UNITS[u_idx];
  while (unit->type != look || pad == 0) {
    pad /= 2;
    if (unit->type < look) {
      u_idx += pad;
    } else {
      u_idx -= pad;
    }
    unit = &UNITS[u_idx];
  }
  if (unit->type != look) { return nullptr; }
  return unit;
}

inline const action *getAction(const state *state, uint32_t ahead) {
  const struct unit *unit = getUnit(state, ahead);
  if (!unit) return nullptr;
  const action *act = &ACTIONS[state->ndx_base + unit->offset];
  return act;
}
inline const state *jump(const state *state, uint32_t current) {
  const struct unit *unit = getUnit(state, current);
  if (!unit) return nullptr;
  return &STATES[JUMPS[unit->offset]];
}

inline const state *getState(uint16_t offset) {
  return &STATES[offset];
}