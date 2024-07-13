/**
 * Project Name: regex
 * Module Name:
 * Filename: _grammar_action.c
 * Creator: Yaokai Liu
 * Create Date: 2024-6-26
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "action.h"
#include "action-table.h"
#include "reduce.gen.h"
#include "stack.h"
#include "target.h"

#define ALLOC_LEN      32
#define _sizeof(_type) ((int32_t) sizeof(_type))

Regexp *produce(const Terminal *tokens, const Allocator * const allocator) {
  void *result;
  const Terminal *tp = tokens;
  uint64_t argv[MAX_ARGC] = {};
  Stack *state_stack = Stack_new();
  Stack *token_stack = Stack_new();
  int32_t state = 0;
  Stack_push(state_stack, &state, sizeof(int32_t));
  while (true) {
    const struct grammar_action *act = getAction(state, tp->type);
    if (!act) { goto __failed_to_product; }
    if (act->action == stack) {
      state = act->offset;
      Stack_push(token_stack, &tp, sizeof(void *));
      Stack_push(state_stack, &state, sizeof(int32_t));
      tp++;
    } else if (act->action == reduce) {
      Stack_pop(token_stack, argv, act->count * _sizeof(void *));
      Stack_pop(state_stack, nullptr, act->count * _sizeof(int32_t));
      Stack_top(state_stack, (int32_t *) &state, _sizeof(int32_t));
      fn_product *func = PRODUCTS[act->offset];
      result = func((void **) argv, allocator);
      if (!result) { goto __failed_to_product; }
      state = jump(state, act->type);
      if (state < 0) { goto __failed_to_product; }
      Stack_push(token_stack, &result, sizeof(void *));
      Stack_push(state_stack, &state, _sizeof(int32_t));
      if (act->offset == __EXTEND_RULE__) { break; }
    } else {
      // never be touched
    }
  }
  Stack_clear(token_stack);
  Stack_clear(state_stack);
  allocator->free(token_stack);
  allocator->free(state_stack);
  return result;

__failed_to_product:
  // TODO: release elements.
  Stack_clear(token_stack);
  Stack_clear(state_stack);
  allocator->free(token_stack);
  allocator->free(state_stack);
  return nullptr;
}
