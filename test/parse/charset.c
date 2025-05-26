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
 * Filename: charset.c
 * Creator: Yaokai Liu
 * Create Date: 2024-7-13
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "action.h"
#include "allocator.h"
#include "char_t.h"
#include "regex.h"
#include "tokens.h"
#include "regex/target.h"
#include "regex/parse.h"
#include <check.h>

#define string_to_test "[0123456789^3^[21a-z][^4123ghcA-Z]]"

START_TEST(test_CHARSET_NORMAL) {
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
  ck_assert_uint_eq(object->type, enum_Charset);
  ck_assert_uint_eq(object->inverse, false);

  Charset *charset = (Charset *) object->target;
  ck_assert_ptr_ne(charset, nullptr);
  struct CharsetPart *tap0 = &charset->parts[CT_NORMAL];
  struct CharsetPart *tap1 = &charset->parts[CT_INVERSE];
  ck_assert_ptr_ne(tap0->plains, nullptr);
  ck_assert_ptr_ne(tap0->ranges, nullptr);
  ck_assert_ptr_ne(tap1->plains, nullptr);
  ck_assert_ptr_ne(tap1->ranges, nullptr);
  ck_assert_uint_eq(Array_length(tap0->plains), (sizeof "0123456789ghc") - 1);
  ck_assert_uint_eq(Array_length(tap0->ranges), 1);
  ck_assert_uint_eq(Array_length(tap1->plains), (sizeof "3214") - 1);
  ck_assert_uint_eq(Array_length(tap1->ranges), 1);
  uint32_t *plains = (uint32_t *) Array_first_real(tap0->plains);
  for (uint32_t i = 0; i < Array_length(tap0->plains); i++) { ck_assert_uint_eq(plains[i], "0123456789ghc"[i]); }
  ck_assert_uint_eq(Array_length(tap0->ranges), 1);
  Range *range0 = (Range *) Array_first_real(tap0->ranges);
  for (uint32_t i = 0; i < Array_length(tap0->ranges); i++) {
    ck_assert_uint_eq(range0->min, 'A');
    ck_assert_uint_eq(range0->max, 'Z');
  }
  plains = (uint32_t *) Array_first_real(tap1->plains);
  for (uint32_t i = 0; i < Array_length(tap1->plains); i++) { ck_assert_uint_eq(plains[i], "3214"[i]); }
  ck_assert_uint_eq(Array_length(tap1->ranges), 1);
  Range *range1 = (Range *) Array_first_real(tap1->ranges);
  for (uint32_t i = 0; i < Array_length(tap1->ranges); i++) {
    ck_assert_uint_eq(range1->min, 'a');
    ck_assert_uint_eq(range1->max, 'z');
  }

  Array_destroy(regexp);
}

END_TEST

#define string_to_test1 "[01234234341g-ma-kl-sA-Z]"
START_TEST(test_CHARSET_DUPLICATED) {
  char_t *string = string_to_test1;
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
  ck_assert_uint_eq(object->type, enum_Charset);
  ck_assert_uint_eq(object->inverse, false);

  Charset *charset = (Charset *) object->target;
  ck_assert_ptr_ne(charset, nullptr);
  struct CharsetPart *tap0 = &charset->parts[CT_NORMAL];
  struct CharsetPart *tap1 = &charset->parts[CT_INVERSE];
  ck_assert_ptr_ne(tap0->plains, nullptr);
  ck_assert_ptr_ne(tap0->ranges, nullptr);
  ck_assert_ptr_ne(tap1->plains, nullptr);
  ck_assert_ptr_ne(tap1->ranges, nullptr);
  ck_assert_uint_eq(Array_length(tap0->plains), (sizeof "01234") - 1);
  ck_assert_uint_eq(Array_length(tap0->ranges), 2);
  ck_assert_uint_eq(Array_length(tap1->plains), 0);
  ck_assert_uint_eq(Array_length(tap1->ranges), 0);
  Range *ranges = (Range *) Array_first_real(tap0->ranges);
  ck_assert_uint_eq(ranges[0].min, 'a');
  ck_assert_uint_eq(ranges[0].max, 's');
  ck_assert_uint_eq(ranges[1].min, 'A');
  ck_assert_uint_eq(ranges[1].max, 'Z');

  Array_destroy(regexp);
}

END_TEST

#define string_to_test2 "[a-fi-ld-k]"
START_TEST(test_CHARSET_RANGES_INTERSECT) {
  char_t *string = string_to_test2;
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
  ck_assert_uint_eq(object->type, enum_Charset);
  ck_assert_uint_eq(object->inverse, false);

  Charset *charset = (Charset *) object->target;
  ck_assert_ptr_ne(charset, nullptr);
  struct CharsetPart *tap0 = &charset->parts[CT_NORMAL];
  struct CharsetPart *tap1 = &charset->parts[CT_INVERSE];
  ck_assert_ptr_ne(tap0->plains, nullptr);
  ck_assert_ptr_ne(tap0->ranges, nullptr);
  ck_assert_ptr_ne(tap1->plains, nullptr);
  ck_assert_ptr_ne(tap1->ranges, nullptr);
  ck_assert_uint_eq(Array_length(tap0->plains), 0);
  ck_assert_uint_eq(Array_length(tap0->ranges), 1);
  ck_assert_uint_eq(Array_length(tap1->plains), 0);
  ck_assert_uint_eq(Array_length(tap1->ranges), 0);
  Range *range0 = (Range *) Array_first_real(tap0->ranges);
  ck_assert_uint_eq(range0->min, 'a');
  ck_assert_uint_eq(range0->max, 'l');

  Array_destroy(regexp);
}

END_TEST

#define string_to_test3 "\\d"
START_TEST(test_CHARSET_ESCAPE) {
  char_t *string = string_to_test3;
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
  ck_assert_uint_eq(object->type, enum_Charset);
  ck_assert_uint_eq(object->inverse, false);

  Charset *charset = (Charset *) object->target;
  ck_assert_ptr_ne(charset, nullptr);
  struct CharsetPart *tap0 = &charset->parts[CT_NORMAL];
  struct CharsetPart *tap1 = &charset->parts[CT_INVERSE];
  ck_assert_ptr_ne(tap0->plains, nullptr);
  ck_assert_ptr_ne(tap0->ranges, nullptr);
  ck_assert_ptr_ne(tap1->plains, nullptr);
  ck_assert_ptr_ne(tap1->ranges, nullptr);
  ck_assert_uint_eq(Array_length(tap0->plains), 0);
  ck_assert_uint_eq(Array_length(tap0->ranges), 1);
  ck_assert_uint_eq(Array_length(tap1->plains), 0);
  ck_assert_uint_eq(Array_length(tap1->ranges), 0);
  Range *range0 = (Range *) Array_first_real(tap0->ranges);
  ck_assert_uint_eq(range0->min, '0');
  ck_assert_uint_eq(range0->max, '9');

  Array_destroy(regexp);
}

END_TEST

Suite *charset_suite() {
  Suite *suite = suite_create("Charset");
  TCase *t_case = tcase_create("charset");
  tcase_add_test(t_case, test_CHARSET_NORMAL);
  tcase_add_test(t_case, test_CHARSET_DUPLICATED);
  tcase_add_test(t_case, test_CHARSET_RANGES_INTERSECT);
  tcase_add_test(t_case, test_CHARSET_ESCAPE);
  suite_add_tcase(suite, t_case);
  return suite;
}

