/**
 * Project Name: regex
 * Module Name: test/produce
 * Filename: sequence.c
 * Creator: Yaokai Liu
 * Create Date: 2024-7-13
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "action.h"
#include "allocator.h"
#include "char_t.h"
#include "terminal.h"
#include "token.h"
#include "tokens.gen.h"
#include <check.h>

#define string_to_test         \
  "0123456789"                 \
  "abcdefghijklmnopqrstuvwxyz" \
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

START_TEST(test_SEQUENCE_NORMAL) {
  char_t *string = string_to_test;
  uint32_t cost, n_tokens;
  Terminal *terminals = tokenize(string, &cost, &n_tokens, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof string_to_test) - 1);
  ck_assert_uint_eq(n_tokens, (sizeof string_to_test));
  ck_assert_ptr_ne(terminals, nullptr);
  ck_assert_uint_eq(terminals[n_tokens - 1].type, enum_TERMINATOR);
  ck_assert_uint_eq(terminals[n_tokens - 1].value, 0);
  ck_assert_str_eq(get_name(terminals[n_tokens - 1].type), string_t("TERMINATOR"));
  Regexp *regexp = produce(terminals, &STDAllocator);
  ck_assert_ptr_ne(regexp, nullptr);
  ck_assert_uint_eq(Array_length(regexp), 1);
  Branch *branch = (Branch *) Array_get(regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(branch), 1);
  Object *object = (Object *) Array_get(branch, 0);
  ck_assert_ptr_ne(object, nullptr);
  ck_assert_uint_eq(object->type, enum_Sequence);
  ck_assert_uint_eq(object->inv, false);

  Sequence *sequence = (Sequence *) object->target;
  ck_assert_ptr_ne(sequence, nullptr);
  ck_assert_uint_eq(Array_length(sequence), cost);
  for (uint32_t i = 0; i < cost; i++) {
    ck_assert_uint_eq(string[i], *(char *) Array_get(sequence, i));
  }

  releaseRegexp(regexp, &STDAllocator);
  Array_destroy(regexp);
  STDAllocator.free(terminals);
}
END_TEST

Suite *sequence_suite() {
  Suite *suite  = suite_create("Sequence");
  TCase *t_case = tcase_create("sequence");
  tcase_add_test(t_case, test_SEQUENCE_NORMAL);
  suite_add_tcase(suite, t_case);
  return suite;
}

