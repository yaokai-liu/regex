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
 * Module Name: grammar
 * Filename: string_t.h
 * Creator: Yaokai Liu
 * Create Date: 2025-05-04
 * Copyright (c) 2025 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_GRAMMAR_STRING_T_H
#define REGEX_GRAMMAR_STRING_T_H

#include "regex/char_t.h"
#include <stdint.h>

uint32_t stridx_o(const char_t *string, char_t ch);

#endif  // REGEX_GRAMMAR_STRING_T_H
