/* License
 *
 * x-regex - A light regular expression and its compiler
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
#include "generated/regex/action-table.gen.h"
#include "generated/regex/rules.gen.h"
#include "regex/error.h"
#include "regex/token.h"
#include "regex/tokenizer.h"
#include "regex/tokens.h"
#include "stack.h"
#include "target.h"

#define MAX_ARGC       16
#define _sizeof(_type) ((int32_t) sizeof(_type))

void terminal2Token(Terminal *terminal, Token *token);

Regex *failed_to_get_next_state(Stack *state_stack, Stack *token_stack, void *result, uint32_t result_type,
                                const Allocator *allocator);
Regex *failed_to_parse(Stack *state_stack, Stack *token_stack, Token *, uint32_t, const Allocator *allocator);
Regex *failed_to_get_action(Stack *state_stack, Stack *token_stack, const Allocator *allocator);

void terminal2Token(Terminal *terminal, Token *token) {
  token->type = terminal->type;
  token->start.lineno = terminal->location.lineno;
  token->start.offset = terminal->location.offset;
  token->start.column = terminal->location.column;
  token->end.lineno = terminal->location.lineno;
  token->end.offset = terminal->location.offset + terminal->length;
  token->end.column = terminal->location.column + terminal->length;
  token->length = terminal->length;
  token->value = terminal->value;
}

Regex *parse(Tokenizer *tokenizer, ErrInfo *errInfo, const Allocator *allocator) {
  Token token = {};
  Terminal terminal = {};
  Token args[MAX_ARGC] = {};
  RegexContext context = {};
  Stack *state_stack = Stack_new(allocator);
  Stack *token_stack = Stack_new(allocator);
  uint32_t state = Regex_state_;
  Stack_push(state_stack, &state, sizeof(int32_t));
  uint32_t status = tokenizer->next(tokenizer, &terminal, errInfo, allocator);
  if (status != REGEX_SUCCESS) { return nullptr; }
  terminal2Token(&terminal, &token);
  while (true) {
    const struct grammar_action *act = getParseAction(state, token.type);
    if (!act) { return failed_to_get_action(state_stack, token_stack, allocator); }
    if (act->action == Regex_action_stack) {
      state = act->offset;
      Stack_push(token_stack, &token, sizeof(Token));
      Stack_push(state_stack, &state, sizeof(uint32_t));
      status = tokenizer->next(tokenizer, &terminal, errInfo, allocator);
      if (status != REGEX_SUCCESS) { return failed_to_get_action(state_stack, token_stack, allocator); }
      terminal2Token(&terminal, &token);
      fn_ctx_act *ctxAct = getRegexContextAction(state);
      if (ctxAct) { ctxAct(&context, &token); }
    } else if (act->action == Regex_action_reduce) {
      Stack_pop(token_stack, args, act->count * sizeof(Token));
      Stack_pop(state_stack, nullptr, act->count * sizeof(uint32_t));
      Stack_top(state_stack, (uint32_t *) &state, sizeof(uint32_t));
      fn_regex_reduce *func = REGEX_PRODUCTS[act->offset];
      token.type = act->type;
      token.start.offset = args[0].start.offset;
      token.start.lineno = args[0].start.lineno;
      token.start.column = args[0].start.column;
      token.end.offset = args[act->count - 1].end.offset;
      token.end.lineno = args[act->count - 1].end.lineno;
      token.end.column = args[act->count - 1].end.column;
      token.length = token.end.offset - token.start.offset;
      token.value = func(args, &context, errInfo, allocator);
      if (!token.value) { return failed_to_parse(state_stack, token_stack, args, act->count, allocator); }
      state = parseJumpState(state, act->type);
      if (state == Regex_BAD_STATE) {
        return failed_to_get_next_state(state_stack, token_stack, &token, act->type, allocator);
      }
      Stack_push(token_stack, &token, sizeof(Token));
      Stack_push(state_stack, &state, sizeof(uint32_t));
      fn_ctx_act *ctxAct = getRegexContextAction(state);
      if (ctxAct) { ctxAct(&context, &token); }
      if (act->offset == Regex_RULE_Regex_EXT) { break; }
      terminal2Token(&terminal, &token);
    } else {
      // never be touched
    }
  }
  Stack_clear(token_stack);
  Stack_clear(state_stack);
  allocator->free(token_stack);
  allocator->free(state_stack);
  return (Regex_TOKEN_Regex == (uint64_t) token.value) ? nullptr : token.value;
}
