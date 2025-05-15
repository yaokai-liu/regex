/**
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
#include "generated/tokens.gen.h"
#include "regex/parse.h"
#include "regex/target.h"
#include "terminal.h"
#include "tokenize.h"
#include <check.h>

#define string_to_test "[0123456789^3^[21a-z][^4123ghcA-Z]]"

START_TEST(test_CHARSET_NORMAL) {
  char_t *string = string_to_test;
  ErrInfo errInfo = {};
  Regexp *regexp = parse(string, nullptr, nullptr, &errInfo, &STDAllocator);
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
  ck_assert_uint_eq(Set_count(tap0->plains), (sizeof "0123456789ghc") - 1);
  ck_assert_uint_eq(Set_count(tap0->ranges), 1);
  ck_assert_uint_eq(Set_count(tap1->plains), (sizeof "3214") - 1);
  ck_assert_uint_eq(Set_count(tap1->ranges), 1);
  for (uint32_t i = 0; i < Set_count(tap0->plains); i++) {
    char p_char = ((uint64_t *) Set_data(tap0->plains))[i];
    ck_assert_uint_eq(p_char, "0123456789ghc"[i]);
  }
  ck_assert_uint_eq(Set_count(tap0->ranges), 1);
  uint64_t *range0 = (uint64_t *) Set_data(tap0->ranges);
  for (uint32_t i = 0; i < Set_count(tap0->ranges); i++) {
    Range range = Range_fromUint64(range0[i]);
    ck_assert_uint_eq(range.min, 'A');
    ck_assert_uint_eq(range.max, 'Z');
  }
  for (uint32_t i = 0; i < Set_count(tap1->plains); i++) {
    char p_char = ((uint64_t *) Set_data(tap1->plains))[i];
    ck_assert_uint_eq(p_char, "3214"[i]);
  }
  ck_assert_uint_eq(Set_count(tap1->ranges), 1);
  uint64_t *range1 = (uint64_t *) Set_data(tap1->ranges);
  for (uint32_t i = 0; i < Set_count(tap1->ranges); i++) {
    Range range = Range_fromUint64(range1[i]);
    ck_assert_uint_eq(range.min, 'a');
    ck_assert_uint_eq(range.max, 'z');
  }

  Array_destroy(regexp);
}

END_TEST

#define string_to_test1 "[01234234341g-ma-kl-sA-Z]"
START_TEST(test_CHARSET_DUPLICATED) {
  char_t *string = string_to_test1;
  ErrInfo errInfo = {};
  Regexp *regexp = parse(string, nullptr, nullptr, &errInfo, &STDAllocator);
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
  ck_assert_uint_eq(Set_count(tap0->plains), (sizeof "01234") - 1);
  ck_assert_uint_eq(Set_count(tap0->ranges), 2);
  ck_assert_uint_eq(Set_count(tap1->plains), 0);
  ck_assert_uint_eq(Set_count(tap1->ranges), 0);
  uint64_t *ranges = (uint64_t *) Set_data(tap0->ranges);
  Range range0 = Range_fromUint64(ranges[0]);
  Range range1 = Range_fromUint64(ranges[1]);
  ck_assert_uint_eq(range0.min, 'a');
  ck_assert_uint_eq(range0.max, 's');
  ck_assert_uint_eq(range1.min, 'A');
  ck_assert_uint_eq(range1.max, 'Z');

  Array_destroy(regexp);
}

END_TEST

Suite *charset_suite() {
  Suite *suite = suite_create("Charset");
  TCase *t_case = tcase_create("charset");
  tcase_add_test(t_case, test_CHARSET_NORMAL);
  tcase_add_test(t_case, test_CHARSET_DUPLICATED);
  suite_add_tcase(suite, t_case);
  return suite;
}

