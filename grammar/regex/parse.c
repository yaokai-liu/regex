/**
 * Project Name: regex
 * Module Name:
 * Filename: _grammar_action.c
 * Creator: Yaokai Liu
 * Create Date: 2024-6-26
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "action.h"
#include "generated/regex/action-table.gen.h"
#include "generated/regex/reduce.gen.h"
#include "generated/tokens.gen.h"
#include "reduce.h"
#include "stack.h"
#include "target.h"
#include "terminal.h"
#include "tokenize.h"

#define MAX_ARGC       16
#define ALLOC_LEN      32
#define _sizeof(_type) ((int32_t) sizeof(_type))

Regexp *failed_to_get_next_state(Stack *state_stack, Stack *token_stack, void *result,
                                 uint32_t result_type, const Allocator *allocator);
Regexp *failed_to_produce(Stack *state_stack, Stack *token_stack, Token *, uint32_t,
                          const Allocator *allocator);
Regexp *failed_to_get_action(Stack *state_stack, Stack *token_stack, const Allocator *allocator);

Regexp *produce(const char_t *input, uint32_t *lineno, uint32_t *column, const Allocator * const allocator) {
  Terminal token = {}, result = {};
  Token args[MAX_ARGC] = {};
  RegexContext context = { .env = enum_Regexp };
  uint32_t l = lineno ? *lineno : 0;
  uint32_t c = column ? *column : 0;
  Stack *state_stack = Stack_new(allocator);
  Stack *token_stack = Stack_new(allocator);
  int32_t state = 0;
  Stack_push(state_stack, &state, sizeof(int32_t));
  input += pass_space(input, &l, &c);
  input += single_tokenize(input, &token, context.env, allocator);
  while (true) {
    const struct grammar_action *act = getParseAction(state, token.type);
    if (!act) {
      lineno ? *lineno = l : 0;
      column ? *column = c : 0;
      return failed_to_get_action(state_stack, token_stack, allocator);
    }
    if (act->action == stack) {
      state = act->offset;
      Stack_push(token_stack, &token, sizeof(Token));
      Stack_push(state_stack, &state, sizeof(int32_t));
      input += pass_space(input, &l, &c);
      input += single_tokenize(input, &token, context.env, allocator);
      c += token.location.length;
      fn_ctx_act *ctxAct = getRegexContextAction(state);
      if (ctxAct) { ctxAct(&context, &token); }
    } else if (act->action == reduce) {
      Stack_pop(token_stack, args, act->count * _sizeof(Token));
      Stack_pop(state_stack, nullptr, act->count * _sizeof(int32_t));
      Stack_top(state_stack, (int32_t *) &state, _sizeof(int32_t));
      fn_reduce *func = REGEX_PRODUCTS[act->offset];
      result.type = act->type;
      result.location.offset = args[0].location.offset;
      result.location.lineno = args[0].location.lineno;
      result.location.column = args[0].location.column;
      result.location.length = args[act->count - 1].location.offset - args[0].location.offset + args[act->count - 1].location.length;
      result.value = func(args, &context, allocator);
      if (!result.value) {
        lineno ? *lineno = l : 0;
        column ? *column = c : 0;
        return failed_to_produce(state_stack, token_stack, args, act->count, allocator);
      }
      state = parseJumpState(state, act->type);
      if (state < 0) {
        lineno ? *lineno = l : 0;
        column ? *column = c : 0;
        return failed_to_get_next_state(state_stack, token_stack, &result, act->type, allocator);
      }
      Stack_push(token_stack, &result, sizeof(Token));
      Stack_push(state_stack, &state, _sizeof(int32_t));
      fn_ctx_act *ctxAct = getRegexContextAction(state);
      if (ctxAct) { ctxAct(&context, &token); }
      if (act->offset == __EXTEND_RULE__) { break; }
    } else {
      // never be touched
    }
  }
  Stack_clear(token_stack);
  Stack_clear(state_stack);
  allocator->free(token_stack);
  allocator->free(state_stack);
  return result.value;
}
