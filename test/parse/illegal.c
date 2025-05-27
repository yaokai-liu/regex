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
 * Module Name: test/parse
 * Filename: failed.c
 * Creator: Yaokai Liu
 * Create Date: 2024-07-13
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "allocator.h"
#include "regex/char_t.h"
#include "regex/regex.h"
#include "regex/target.h"
#include "regex/parse.h"
#include <check.h>

#define string_to_test "(abcd[(sdcc)])"

START_TEST(test_ILLEGAL) {
  char_t *string = string_to_test;
  ErrInfo errInfo = {};
  Tokenizer tokenizer = {};
  RegexTokenizer_init(&tokenizer, string, &STDAllocator);
  Regex *regexp = parse(&tokenizer, &errInfo, &STDAllocator);
  ck_assert_ptr_eq(regexp, nullptr);
}

END_TEST

Suite *illegal_suite() {
  Suite *suite = suite_create("_Illegal");
  TCase *t_case = tcase_create("illegal");
  tcase_add_test(t_case, test_ILLEGAL);
  suite_add_tcase(suite, t_case);
  return suite;
}
