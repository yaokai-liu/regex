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
 * Module Name: test/parse
 * Filename: sequence.c
 * Creator: Yaokai Liu
 * Create Date: 2024-7-13
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

#define string_to_test         \
  "0123456789"                 \
  "abcdefghijklmnopqrstuvwxyz" \
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

START_TEST(test_SEQUENCE_NORMAL) {
  char_t *string = string_to_test;
  ErrInfo errInfo = {};
  Tokenizer tokenizer = {};
  RegexTokenizer_init(&tokenizer, string, &STDAllocator);
  Regex *regexp = parse(&tokenizer, &errInfo, &STDAllocator);
  ck_assert_ptr_ne(regexp, nullptr);
  ck_assert_uint_eq(Array_length(regexp), 1);
  Branch *branch = (Branch *) Array_real_addr(regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(branch), sizeof(string_to_test) - 1);
  Object *objects = (Object *) Array_real_addr(branch, 0);
  ck_assert_ptr_ne(objects, nullptr);
  for (uint32_t i = 0; i < Array_length(branch); i++) {
    ck_assert_uint_eq(objects[i].type, enum_SYMBOL);
    ck_assert_uint_eq((uint64_t) objects[i].target, string_to_test[i]);
  }
  Array_reset(regexp, (destruct_t *) releaseBranch);
  Array_destroy(regexp);
}
END_TEST

#define string_to_test2 "{123ab}"

START_TEST(test_SEQUENCE_FALL_THROUGH) {
  char_t *string = string_to_test2;
  ErrInfo errInfo = {};
  Tokenizer tokenizer = {};
  RegexTokenizer_init(&tokenizer, string, &STDAllocator);
  Regex *regexp = parse(&tokenizer, &errInfo, &STDAllocator);
  ck_assert_ptr_ne(regexp, nullptr);
  ck_assert_uint_eq(Array_length(regexp), 1);
  Branch *branch = (Branch *) Array_real_addr(regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(branch), sizeof(string_to_test2) - 1);
  Object *objects = (Object *) Array_real_addr(branch, 0);
  ck_assert_ptr_ne(objects, nullptr);
  for (uint32_t i = 0; i < Array_length(branch); i++) {
    ck_assert_uint_eq(objects[i].type, enum_SYMBOL);
    ck_assert_uint_eq((uint64_t) objects[i].target, string_to_test2[i]);
  }
  Array_reset(regexp, (destruct_t *) releaseBranch);
  Array_destroy(regexp);
}
END_TEST

#define string_to_test3 "{123\nab}"

START_TEST(test_SEQUENCE_FALL_THROUGH_2) {
  char_t *string = string_to_test3;
  ErrInfo errInfo = {};
  Tokenizer tokenizer = {};
  RegexTokenizer_init(&tokenizer, string, &STDAllocator);
  Regex *regexp = parse(&tokenizer, &errInfo, &STDAllocator);
  ck_assert_ptr_ne(regexp, nullptr);
  ck_assert_uint_eq(Array_length(regexp), 1);
  Branch *branch = (Branch *) Array_real_addr(regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(branch), sizeof(string_to_test2) - 1);
  Object *objects = (Object *) Array_real_addr(branch, 0);
  ck_assert_ptr_ne(objects, nullptr);
  for (uint32_t i = 0; i < Array_length(branch); i++) {
    ck_assert_uint_eq(objects[i].type, enum_SYMBOL);
    ck_assert_uint_eq((uint64_t) objects[i].target, string_to_test2[i]);
  }
  Array_reset(regexp, (destruct_t *) releaseBranch);
  Array_destroy(regexp);
}
END_TEST

Suite *sequence_suite() {
  Suite *suite = suite_create("Sequence");
  TCase *t_case = tcase_create("sequence");
  tcase_add_test(t_case, test_SEQUENCE_NORMAL);
  tcase_add_test(t_case, test_SEQUENCE_FALL_THROUGH);
  tcase_add_test(t_case, test_SEQUENCE_FALL_THROUGH_2);
  suite_add_tcase(suite, t_case);
  return suite;
}

