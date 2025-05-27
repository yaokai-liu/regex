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
 * Filename: group.c
 * Creator: Yaokai Liu
 * Create Date: 2024-07-13
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "action.h"
#include "allocator.h"
#include "regex/char_t.h"
#include "regex/regex.h"
#include "regex/tokens.h"
#include "regex/target.h"
#include "regex/parse.h"
#include <check.h>

#define string_to_test "(1234[5678]^[4321]^abcd{4})"

START_TEST(test_GROUP_NORMAL) {
  char_t *string = string_to_test;
  ErrInfo errInfo = {};
  Tokenizer tokenizer = {};
  RegexTokenizer_init(&tokenizer, string, &STDAllocator);
  Regex *regexp = parse(&tokenizer, &errInfo, &STDAllocator);
  ck_assert_ptr_ne(regexp, nullptr);
  ck_assert_uint_eq(Array_length(regexp), 1);
  Branch *branch = (Branch *) Array_real_addr(regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(branch), 1);
  Object *object = (Object *) Array_real_addr(branch, 0);
  ck_assert_ptr_ne(object, nullptr);
  ck_assert_uint_eq(object->type, enum_Group);
  ck_assert_uint_eq(object->inverse, false);

  Group *group = (Group *) object->target;
  ck_assert_ptr_ne(group, nullptr);
  Regex *sub_regexp = group->regexp;
  ck_assert_ptr_ne(sub_regexp, nullptr);
  ck_assert_uint_eq(Array_length(sub_regexp), 1);
  Branch *sub_branch = (Branch *) Array_real_addr(sub_regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(sub_branch), 10);

  Array_destroy(regexp);
}

END_TEST

Suite *group_suite() {
  Suite *suite = suite_create("Group");
  TCase *t_case = tcase_create("group");
  tcase_add_test(t_case, test_GROUP_NORMAL);
  suite_add_tcase(suite, t_case);
  return suite;
}
