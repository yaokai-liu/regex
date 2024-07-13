/**
 * Project Name: regex
 * Module Name: test/produce
 * Filename: charset.c
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

#define string_to_test "[0123456789^3^[21a-z][^123ghcA-Z]]"

START_TEST(test_CHARSET_NORMAL) {
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
  ck_assert_uint_eq(object->type, enum_Charset);
  ck_assert_uint_eq(object->inv, false);

  Charset *charset = (Charset *) object->target;
  ck_assert_ptr_ne(charset, nullptr);
  struct charset_tap *tap0 = &charset->taps[CT_NORMAL];
  struct charset_tap *tap1 = &charset->taps[CT_INVERSE];
  ck_assert_ptr_ne(tap0->plains, nullptr);
  ck_assert_ptr_ne(tap0->ranges, nullptr);
  ck_assert_ptr_ne(tap1->plains, nullptr);
  ck_assert_ptr_ne(tap1->ranges, nullptr);
  ck_assert_uint_eq(Array_length(tap0->plains), (sizeof "0123456789ghc") - 1);
  ck_assert_uint_eq(Array_length(tap0->ranges), 1);
  ck_assert_uint_eq(Array_length(tap1->plains), (sizeof "321") - 1);
  ck_assert_uint_eq(Array_length(tap1->ranges), 1);
  for (uint32_t i = 0; i < Array_length(tap0->plains); i++) {
    char *p_char = Array_get(tap0->plains, i);
    ck_assert_uint_eq(*p_char, "0123456789ghc"[i]);
  }
  Range *range0 = (Range *) Array_get(tap0->ranges, 0);
  ck_assert_uint_eq(range0->min, 'A');
  ck_assert_uint_eq(range0->max, 'Z');
  for (uint32_t i = 0; i < Array_length(tap1->plains); i++) {
    char *p_char = Array_get(tap1->plains, i);
    ck_assert_uint_eq(*p_char, "321"[i]);
  }
  Range *range1 = (Range *) Array_get(tap1->ranges, 0);
  ck_assert_uint_eq(range1->min, 'a');
  ck_assert_uint_eq(range1->max, 'z');

  releaseRegexp(regexp, &STDAllocator);
  Array_destroy(regexp);
  STDAllocator.free(terminals);
}

END_TEST

Suite *charset_suite() {
  Suite *suite = suite_create("Charset");
  TCase *t_case = tcase_create("charset");
  tcase_add_test(t_case, test_CHARSET_NORMAL);
  suite_add_tcase(suite, t_case);
  return suite;
}

