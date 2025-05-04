/* License
 *
 * ${PROJ_DESCRIPTION}
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
 * Filename: string_t.c
 * Creator: Yaokai Liu
 * Create Date: 2025-05-04
 * Copyright (c) 2025 Yaokai Liu. All rights reserved.
 **/

#include "string_t.h"

inline uint32_t stridx_o(const char_t *string, char_t ch) {
  if (!string) { return -1; }
  int len = 0;
  while (ch != string[len] && string[len]) { len++; }
  return len;
}

inline uint32_t stridx_i(const char_t *string, int ch, uint32_t len) {
  for (uint32_t i = 0; i < len; i++) {
    if (ch == string[i]) { return i; }
  }
  return UINT32_MAX;
}
