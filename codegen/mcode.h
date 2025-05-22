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
 * Module Name: codegen/x64
 * Filename: mcode.h
 * Creator: Yaokai Liu
 * Create Date: 2024-07-27
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_CODEGEN_MCODE_H
#define REGEX_CODEGEN_MCODE_H

#include "array.h"
#include "char_t.h"

uint32_t mcode_ranges(uint32_t lower_bounds, uint32_t upper_bounds, uint32_t n_ranges);
Array *mcode_char(char_t the_char);
Array *mcode_plains(const char_t *plains, uint32_t n_plains);
Array *mcode_sequence(const char_t *plains, uint32_t n_plains);

#endif  // REGEX_CODEGEN_MCODE_H
