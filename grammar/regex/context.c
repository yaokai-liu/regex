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
 * Module Name: grammar/regex
 * Filename: context.c
 * Creator: Yaokai Liu
 * Create Date: 2025-05-04
 * Copyright (c) 2025 Yaokai Liu. All rights reserved.
 **/

#include "context.h"
#include "generated/regex/action-table.gen.h"
#include "generated/tokens.gen.h"

void set_env_quantifier(RegexContext *context, const Token *) {
  context->env = enum_Quantifier;
}

void set_env_regexp(RegexContext *context, const Token *) {
  context->env = enum_Regex;
}
void set_env_not(RegexContext *context, const Token *) {
  context->env = enum_NOT;
}

fn_ctx_act *getRegexContextAction(uint32_t state) {
  switch (state) {
    case Regex_state_NOT: {
      return set_env_not;
    }
    case Regex_state_Object: {
      return set_env_regexp;
    }
    case Regex_state_Object_BEGIN_QUANTIFIER: {
      return set_env_quantifier;
    }
    case Regex_state_Object_Quantifier: {
      return set_env_regexp;
    }
    default: {
    }
  }
  return nullptr;
}