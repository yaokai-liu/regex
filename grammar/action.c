/**
 * Project Name: regex
 * Module Name:
 * Filename: action.c
 * Creator: Yaokai Liu
 * Create Date: 24-6-26
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "stack.h"
#include "action.h"
#include "target.h"
#include "action-table.h"
#include "reduce.gen.h"
#include "tokens.gen.h"

#define ALLOC_LEN 32

struct Regexp *produce(const Terminal *tokens) {
  void *result;
  const Terminal *tp = tokens;
  uint64_t EOS = TERMINATOR;
  uint64_t argv[10] = {};
  Stack *status_stack = Stack_new();
  Stack *token_stack = Stack_new();
  const state *state = 0;
  Stack_push(status_stack, (uint64_t *) &state, 1);
  Stack_push(token_stack, &EOS, 1);
  while (true) {
    const action *act = getAction(state, tp->type);
    if (act->action == stack) {
      state = getState(act->offset);
      Stack_push(status_stack, (uint64_t *) &state, 1);
      Stack_push(token_stack, (uint64_t *) &tp, 1);
      tp++;
    } else if (act->action == reduce) {
      Stack_pop(token_stack, argv, act->count);
      Stack_pop(status_stack, nullptr, act->count);
      Stack_top(status_stack, (uint64_t *) &state);
      fn_product *func = PRODUCTS[act->offset];
      result = func((void **) argv, &STDAllocator);
      state = jump(state, act->type);
      Stack_push(token_stack, result, 1);
      Stack_push(status_stack, (uint64_t *) &state, 1);
      if (act->offset == __EXTEND_RULE__) { break; }
    } else {
      // TODO: release elements.
      Stack_release(token_stack);
      Stack_release(status_stack);
      return nullptr;
    }
  }
  return result;
}
