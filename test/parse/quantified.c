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
 * Filename: quantified.c
 * Creator: Yaokai Liu
 * Create Date: 2024-7-13
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "action.h"
#include "allocator.h"
#include "char_t.h"
#include "enum.h"
#include "generated/tokens.gen.h"
#include "regex/parse.h"
#include "regex/target.h"
#include "terminal.h"
#include "tokenize.h"
#include <check.h>

#define string_to_test0 "123?"

START_TEST(test_QUANTIFIED_NURMAL0) {
  char_t *string = string_to_test0;
  ErrInfo errInfo = {};
  Regex *regexp = parse(string, nullptr, nullptr, &errInfo, &STDAllocator);
  ck_assert_ptr_ne(regexp, nullptr);
  ck_assert_uint_eq(Array_length(regexp), 1);
  Branch *branch = (Branch *) Array_real_addr(regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(branch), 3);
  Object *objects = (Object *) Array_real_addr(branch, 0);
  ck_assert_ptr_ne(objects, nullptr);
  ck_assert_uint_eq(objects[0].type, enum_CHAR);
  ck_assert_uint_eq(objects[0].inverse, false);
  ck_assert_uint_eq(objects[0].assertion, false);
  ck_assert_uint_eq(objects[1].type, enum_CHAR);
  ck_assert_uint_eq(objects[1].inverse, false);
  ck_assert_uint_eq(objects[1].assertion, false);
  ck_assert_uint_eq(objects[2].type, enum_CHAR);
  ck_assert_uint_eq(objects[2].inverse, false);
  ck_assert_uint_eq(objects[2].assertion, false);
  char_t chr = (uint64_t) objects[2].target;
  ck_assert_uint_eq(chr, '3');
  ck_assert_uint_eq(objects[2].min_times, 0);
  ck_assert_uint_eq(objects[2].max_times, 1);

  Array_destroy(regexp);
}

END_TEST

#define string_to_test1 "123+"

START_TEST(test_QUANTIFIED_NURMAL1) {
  char_t *string = string_to_test1;
  ErrInfo errInfo = {};
  Regex *regexp = parse(string, nullptr, nullptr, &errInfo, &STDAllocator);
  ck_assert_ptr_ne(regexp, nullptr);
  ck_assert_uint_eq(Array_length(regexp), 1);
  Branch *branch = (Branch *) Array_real_addr(regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(branch), 3);
  Object *objects = (Object *) Array_real_addr(branch, 0);
  ck_assert_ptr_ne(objects, nullptr);
  ck_assert_uint_eq(objects[0].type, enum_CHAR);
  ck_assert_uint_eq(objects[0].inverse, false);
  ck_assert_uint_eq(objects[0].assertion, false);
  ck_assert_uint_eq(objects[1].type, enum_CHAR);
  ck_assert_uint_eq(objects[1].inverse, false);
  ck_assert_uint_eq(objects[1].assertion, false);
  ck_assert_uint_eq(objects[2].type, enum_CHAR);
  ck_assert_uint_eq(objects[2].inverse, false);
  ck_assert_uint_eq(objects[2].assertion, false);
  char_t chr = (uint64_t) objects[2].target;
  ck_assert_uint_eq(chr, '3');
  ck_assert_uint_eq(objects[2].min_times, 1);
  ck_assert_uint_eq(objects[2].max_times, 0);

  Array_destroy(regexp);
}

END_TEST

#define string_to_test2 "123*"

START_TEST(test_QUANTIFIED_NURMAL2) {
  char_t *string = string_to_test2;
  ErrInfo errInfo = {};
  Regex *regexp = parse(string, nullptr, nullptr, &errInfo, &STDAllocator);
  ck_assert_ptr_ne(regexp, nullptr);
  ck_assert_uint_eq(Array_length(regexp), 1);
  Branch *branch = (Branch *) Array_real_addr(regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(branch), 3);
  Object *objects = (Object *) Array_real_addr(branch, 0);
  ck_assert_ptr_ne(objects, nullptr);
  ck_assert_uint_eq(objects[0].type, enum_CHAR);
  ck_assert_uint_eq(objects[0].inverse, false);
  ck_assert_uint_eq(objects[0].assertion, false);
  ck_assert_uint_eq(objects[1].type, enum_CHAR);
  ck_assert_uint_eq(objects[1].inverse, false);
  ck_assert_uint_eq(objects[1].assertion, false);
  ck_assert_uint_eq(objects[2].type, enum_CHAR);
  ck_assert_uint_eq(objects[2].inverse, false);
  ck_assert_uint_eq(objects[2].assertion, false);
  char_t chr = (uint64_t) objects[2].target;
  ck_assert_uint_eq(chr, '3');
  ck_assert_uint_eq(objects[2].min_times, 0);
  ck_assert_uint_eq(objects[2].max_times, 0);

  Array_destroy(regexp);
}

END_TEST

#define string_to_test3 "123{3}"

START_TEST(test_QUANTIFIED_NURMAL3) {
  char_t *string = string_to_test3;
  ErrInfo errInfo = {};
  Regex *regexp = parse(string, nullptr, nullptr, &errInfo, &STDAllocator);
  ck_assert_ptr_ne(regexp, nullptr);
  ck_assert_uint_eq(Array_length(regexp), 1);
  Branch *branch = (Branch *) Array_real_addr(regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(branch), 3);
  Object *objects = (Object *) Array_real_addr(branch, 0);
  ck_assert_ptr_ne(objects, nullptr);
  ck_assert_uint_eq(objects[0].type, enum_CHAR);
  ck_assert_uint_eq(objects[0].inverse, false);
  ck_assert_uint_eq(objects[0].assertion, false);
  ck_assert_uint_eq(objects[1].type, enum_CHAR);
  ck_assert_uint_eq(objects[1].inverse, false);
  ck_assert_uint_eq(objects[1].assertion, false);
  ck_assert_uint_eq(objects[2].type, enum_CHAR);
  ck_assert_uint_eq(objects[2].inverse, false);
  ck_assert_uint_eq(objects[2].assertion, false);
  char_t chr = (uint64_t) objects[2].target;
  ck_assert_uint_eq(chr, '3');
  ck_assert_uint_eq(objects[2].min_times, 3);
  ck_assert_uint_eq(objects[2].max_times, 3);

  Array_destroy(regexp);
}

END_TEST

#define string_to_test4 "123{3,7}"

START_TEST(test_QUANTIFIED_NURMAL4) {
  char_t *string = string_to_test4;
  ErrInfo errInfo = {};
  Regex *regexp = parse(string, nullptr, nullptr, &errInfo, &STDAllocator);
  ck_assert_ptr_ne(regexp, nullptr);
  ck_assert_uint_eq(Array_length(regexp), 1);
  Branch *branch = (Branch *) Array_real_addr(regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(branch), 3);
  Object *objects = (Object *) Array_real_addr(branch, 0);
  ck_assert_ptr_ne(objects, nullptr);
  ck_assert_uint_eq(objects[0].type, enum_CHAR);
  ck_assert_uint_eq(objects[0].inverse, false);
  ck_assert_uint_eq(objects[0].assertion, false);
  ck_assert_uint_eq(objects[1].type, enum_CHAR);
  ck_assert_uint_eq(objects[1].inverse, false);
  ck_assert_uint_eq(objects[1].assertion, false);
  ck_assert_uint_eq(objects[2].type, enum_CHAR);
  ck_assert_uint_eq(objects[2].inverse, false);
  ck_assert_uint_eq(objects[2].assertion, false);
  char_t chr = (uint64_t) objects[2].target;
  ck_assert_uint_eq(chr, '3');
  ck_assert_uint_eq(objects[2].min_times, 3);
  ck_assert_uint_eq(objects[2].max_times, 7);

  Array_destroy(regexp);
}

END_TEST

#define string_to_test5 "123{6,}"

START_TEST(test_QUANTIFIED_NURMAL5) {
  char_t *string = string_to_test5;
  ErrInfo errInfo = {};
  Regex *regexp = parse(string, nullptr, nullptr, &errInfo, &STDAllocator);
  ck_assert_ptr_ne(regexp, nullptr);
  ck_assert_uint_eq(Array_length(regexp), 1);
  Branch *branch = (Branch *) Array_real_addr(regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(branch), 3);
  Object *objects = (Object *) Array_real_addr(branch, 0);
  ck_assert_ptr_ne(objects, nullptr);
  ck_assert_uint_eq(objects[0].type, enum_CHAR);
  ck_assert_uint_eq(objects[0].inverse, false);
  ck_assert_uint_eq(objects[0].assertion, false);
  ck_assert_uint_eq(objects[1].type, enum_CHAR);
  ck_assert_uint_eq(objects[1].inverse, false);
  ck_assert_uint_eq(objects[1].assertion, false);
  ck_assert_uint_eq(objects[2].type, enum_CHAR);
  ck_assert_uint_eq(objects[2].inverse, false);
  ck_assert_uint_eq(objects[2].assertion, false);
  char_t chr = (uint64_t) objects[2].target;
  ck_assert_uint_eq(chr, '3');
  ck_assert_uint_eq(objects[2].min_times, 6);
  ck_assert_uint_eq(objects[2].max_times, 0);

  Array_destroy(regexp);
}

END_TEST

#define string_to_test6 "123{,7}"

START_TEST(test_QUANTIFIED_NURMAL6) {
  char_t *string = string_to_test6;
  ErrInfo errInfo = {};
  Regex *regexp = parse(string, nullptr, nullptr, &errInfo, &STDAllocator);
  ck_assert_ptr_ne(regexp, nullptr);
  ck_assert_uint_eq(Array_length(regexp), 1);
  Branch *branch = (Branch *) Array_real_addr(regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(branch), 3);
  Object *objects = (Object *) Array_real_addr(branch, 0);
  ck_assert_ptr_ne(objects, nullptr);
  ck_assert_uint_eq(objects[0].type, enum_CHAR);
  ck_assert_uint_eq(objects[0].inverse, false);
  ck_assert_uint_eq(objects[0].assertion, false);
  ck_assert_uint_eq(objects[1].type, enum_CHAR);
  ck_assert_uint_eq(objects[1].inverse, false);
  ck_assert_uint_eq(objects[1].assertion, false);
  ck_assert_uint_eq(objects[2].type, enum_CHAR);
  ck_assert_uint_eq(objects[2].inverse, false);
  ck_assert_uint_eq(objects[2].assertion, false);
  char_t chr = (uint64_t) objects[2].target;
  ck_assert_uint_eq(chr, '3');
  ck_assert_uint_eq(objects[2].min_times, 0);
  ck_assert_uint_eq(objects[2].max_times, 7);

  Array_destroy(regexp);
}

END_TEST

#define string_to_test7 "123{,}"

START_TEST(test_QUANTIFIED_NURMAL7) {
  char_t *string = string_to_test7;
  ErrInfo errInfo = {};
  Regex *regexp = parse(string, nullptr, nullptr, &errInfo, &STDAllocator);
  ck_assert_ptr_ne(regexp, nullptr);
  ck_assert_uint_eq(Array_length(regexp), 1);
  Branch *branch = (Branch *) Array_real_addr(regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(branch), 3);
  Object *objects = (Object *) Array_real_addr(branch, 0);
  ck_assert_ptr_ne(objects, nullptr);
  ck_assert_uint_eq(objects[0].type, enum_CHAR);
  ck_assert_uint_eq(objects[0].inverse, false);
  ck_assert_uint_eq(objects[0].assertion, false);
  ck_assert_uint_eq(objects[1].type, enum_CHAR);
  ck_assert_uint_eq(objects[1].inverse, false);
  ck_assert_uint_eq(objects[1].assertion, false);
  ck_assert_uint_eq(objects[2].type, enum_CHAR);
  ck_assert_uint_eq(objects[2].inverse, false);
  ck_assert_uint_eq(objects[2].assertion, false);
  char_t chr = (uint64_t) objects[2].target;
  ck_assert_uint_eq(chr, '3');
  ck_assert_uint_eq(objects[2].min_times, 0);
  ck_assert_uint_eq(objects[2].max_times, 0);

  Array_destroy(regexp);
}

END_TEST

#define string_to_test8 "123{}"

START_TEST(test_QUANTIFIED_NURMAL8) {
  char_t *string = string_to_test8;
  ErrInfo errInfo = {};
  Regex *regexp = parse(string, nullptr, nullptr, &errInfo, &STDAllocator);
  ck_assert_ptr_ne(regexp, nullptr);
  ck_assert_uint_eq(Array_length(regexp), 1);
  Branch *branch = (Branch *) Array_real_addr(regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(branch), 3);
  Object *objects = (Object *) Array_real_addr(branch, 0);
  ck_assert_ptr_ne(objects, nullptr);
  ck_assert_uint_eq(objects[0].type, enum_CHAR);
  ck_assert_uint_eq(objects[0].inverse, false);
  ck_assert_uint_eq(objects[0].assertion, false);
  ck_assert_uint_eq(objects[1].type, enum_CHAR);
  ck_assert_uint_eq(objects[1].inverse, false);
  ck_assert_uint_eq(objects[1].assertion, false);
  ck_assert_uint_eq(objects[2].type, enum_CHAR);
  ck_assert_uint_eq(objects[2].inverse, false);
  ck_assert_uint_eq(objects[2].assertion, false);
  char_t chr = (uint64_t) objects[2].target;
  ck_assert_uint_eq(chr, '3');
  ck_assert_uint_eq(objects[2].min_times, 0);
  ck_assert_uint_eq(objects[2].max_times, 0);

  Array_destroy(regexp);
}

END_TEST

#define string_to_test9 "123+"

START_TEST(test_QUANTIFIED_NURMAL9) {
  char_t *string = string_to_test9;
  ErrInfo errInfo = {};
  Regex *regexp = parse(string, nullptr, nullptr, &errInfo, &STDAllocator);
  ck_assert_ptr_ne(regexp, nullptr);
  ck_assert_uint_eq(Array_length(regexp), 1);
  Branch *branch = (Branch *) Array_real_addr(regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(branch), 3);
  Object *objects = (Object *) Array_real_addr(branch, 0);
  ck_assert_ptr_ne(objects, nullptr);
  ck_assert_uint_eq(objects[0].type, enum_CHAR);
  ck_assert_uint_eq(objects[0].inverse, false);
  ck_assert_uint_eq(objects[0].assertion, false);
  ck_assert_uint_eq(objects[1].type, enum_CHAR);
  ck_assert_uint_eq(objects[1].inverse, false);
  ck_assert_uint_eq(objects[1].assertion, false);
  ck_assert_uint_eq(objects[2].type, enum_CHAR);
  ck_assert_uint_eq(objects[2].inverse, false);
  ck_assert_uint_eq(objects[2].assertion, false);
  char_t chr = (uint64_t) objects[2].target;
  ck_assert_uint_eq(chr, '3');
  ck_assert_uint_eq(objects[2].min_times, 1);
  ck_assert_uint_eq(objects[2].max_times, 0);

  Array_destroy(regexp);
}

END_TEST

Suite *quantified_suite() {
  Suite *suite = suite_create("Quantified");
  TCase *t_case = tcase_create("quantified");
  tcase_add_test(t_case, test_QUANTIFIED_NURMAL0);
  tcase_add_test(t_case, test_QUANTIFIED_NURMAL1);
  tcase_add_test(t_case, test_QUANTIFIED_NURMAL2);
  tcase_add_test(t_case, test_QUANTIFIED_NURMAL3);
  tcase_add_test(t_case, test_QUANTIFIED_NURMAL4);
  tcase_add_test(t_case, test_QUANTIFIED_NURMAL5);
  tcase_add_test(t_case, test_QUANTIFIED_NURMAL6);
  tcase_add_test(t_case, test_QUANTIFIED_NURMAL7);
  tcase_add_test(t_case, test_QUANTIFIED_NURMAL8);
  tcase_add_test(t_case, test_QUANTIFIED_NURMAL9);
  suite_add_tcase(suite, t_case);
  return suite;
}
