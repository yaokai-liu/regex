/* License
 *
 * xRegex - a Kind of Regular Expression
 * Copyright (C) 2025 Yaokai Liu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *
 * Project Name: regex
 * Module Name:
 * Filename: _grammar_action.c
 * Creator: Yaokai Liu
 * Create Date: 2024-6-26
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "action.h"
#include "regex/error.h"
#include "stack.h"
#include "target.h"
#include "regex/token.h"
#include "generated/regex/action-table.gen.h"
#include "generated/regex/rules.gen.h"
#include "regex/tokens.h"
#include "regex/tokenizer.h"

#define MAX_ARGC       16
#define _sizeof(_type) ((int32_t) sizeof(_type))

Regex *failed_to_get_next_state(Stack *state_stack, Stack *token_stack, void *result,
                                 uint32_t result_type, const Allocator *allocator);
Regex *failed_to_parse(Stack *state_stack, Stack *token_stack, Token *, uint32_t,
                        const Allocator *allocator);
Regex *failed_to_get_action(Stack *state_stack, Stack *token_stack, const Allocator *allocator);

Regex *parse(Tokenizer *tokenizer, ErrInfo *errInfo, const Allocator *allocator) {
  Terminal token = {}, result = {};
  Token args[MAX_ARGC] = {};
  RegexContext context = {};
  Stack *state_stack = Stack_new(allocator);
  Stack *token_stack = Stack_new(allocator);
  int32_t state = 0;
  Stack_push(state_stack, &state, sizeof(int32_t));
  uint32_t status = tokenizer->next(tokenizer, &token, errInfo, allocator);
  if (status != REGEX_SUCCESS) { return nullptr; }
  while (true) {
    const struct grammar_action *act = getParseAction(state, token.type);
    if (!act) {
      return failed_to_get_action(state_stack, token_stack, allocator);
    }
    if (act->action == Regex_action_stack) {
      state = act->offset;
      Stack_push(token_stack, &token, sizeof(Token));
      Stack_push(state_stack, &state, sizeof(int32_t));
      status = tokenizer->next(tokenizer, &token, errInfo, allocator);
      if (status != REGEX_SUCCESS) { return failed_to_get_action(state_stack, token_stack, allocator); }
      fn_ctx_act *ctxAct = getRegexContextAction(state);
      if (ctxAct) { ctxAct(&context, &token); }
    } else if (act->action == Regex_action_reduce) {
      Stack_pop(token_stack, args, act->count * _sizeof(Token));
      Stack_pop(state_stack, nullptr, act->count * _sizeof(int32_t));
      Stack_top(state_stack, (int32_t *) &state, _sizeof(int32_t));
      fn_regex_reduce *func = REGEX_PRODUCTS[act->offset];
      result.type = act->type;
      result.location.offset = args[0].location.offset;
      result.location.lineno = args[0].location.lineno;
      result.location.column = args[0].location.column;
      result.location.length = args[act->count - 1].location.offset - args[0].location.offset
                               + args[act->count - 1].location.length;
      result.value = func(args, &context, errInfo, allocator);
      if (!result.value) {
        return failed_to_parse(state_stack, token_stack, args, act->count, allocator);
      }
      state = parseJumpState(state, act->type);
      if (state < 0) {
        return failed_to_get_next_state(state_stack, token_stack, &result, act->type, allocator);
      }
      Stack_push(token_stack, &result, sizeof(Token));
      Stack_push(state_stack, &state, _sizeof(int32_t));
      fn_ctx_act *ctxAct = getRegexContextAction(state);
      if (ctxAct) { ctxAct(&context, &token); }
      if (act->offset == enum_Regex_Regex_EXT) { break; }
    } else {
      // never be touched
    }
  }
  Stack_clear(token_stack);
  Stack_clear(state_stack);
  allocator->free(token_stack);
  allocator->free(state_stack);
  return (enum_Regex == (uint64_t) result.value) ? nullptr : result.value;
}
