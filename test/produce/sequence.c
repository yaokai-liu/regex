/**
 * Project Name: regex
 * Module Name: test/parse
 * Filename: sequence.c
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

#define string_to_test         \
  "0123456789"                 \
  "abcdefghijklmnopqrstuvwxyz" \
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

START_TEST(test_SEQUENCE_NORMAL) {
  char_t *string = string_to_test;
  ErrInfo errInfo = {};
  Regexp *regexp = parse(string, nullptr, nullptr, &errInfo, &STDAllocator);
  ck_assert_ptr_ne(regexp, nullptr);
  ck_assert_uint_eq(Array_length(regexp), 1);
  Branch *branch = (Branch *) Array_real_addr(regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(branch), sizeof(string_to_test) - 1);
  Object *objects = (Object *) Array_real_addr(branch, 0);
  ck_assert_ptr_ne(objects, nullptr);
  for (uint32_t i = 0; i < Array_length(branch); i++) {
    ck_assert_uint_eq(objects[i].type, enum_CHAR);
    ck_assert_uint_eq((uint64_t) objects[i].target, string_to_test[i]);
  }

  Array_destroy(regexp);
}
END_TEST

Suite *sequence_suite() {
  Suite *suite = suite_create("Sequence");
  TCase *t_case = tcase_create("sequence");
  tcase_add_test(t_case, test_SEQUENCE_NORMAL);
  suite_add_tcase(suite, t_case);
  return suite;
}

