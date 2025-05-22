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
 * Module Name: test
 * Filename: debug.c
 * Creator: Yaokai Liu
 * Create Date: 2024-7-13
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "regex/parse.h"
#include "regex/target.h"
#include "terminal.h"
#include <stdio.h>

int main() {
  const char *string = "^0123456789\\w";
  Regex *regexp = parse(string, nullptr, nullptr, nullptr, &STDAllocator);
  if (!regexp) { return -1; }
  printf("%u\n", Array_length(regexp));
  Branch *branch = Array_first_real(regexp);
  printf("%u\n", Array_length(branch));
  Object *object = Array_real_addr(branch, 10);
  Charset *charset = object->target;
  printf("%u\n", Array_length(charset->parts[CT_NORMAL].ranges));
  return 0;
}
