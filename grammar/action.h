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
 * Filename: actions.h
 * Creator: Yaokai Liu
 * Create Date: 24-6-26
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_GRAMMAR_ACTION_H
#define REGEX_GRAMMAR_ACTION_H

#include <stdint.h>

typedef struct state state;
struct grammar_action {
  enum : uint8_t {
    Regex_action_reject = 0,
    Regex_action_stack = 1,
    Regex_action_reduce = 2
  } action      : 4;
  uint8_t count : 4;
  uint8_t type;
  const uint16_t offset;
};

#endif  // REGEX_GRAMMAR_ACTION_H
