/**
 * Project Name: regex
 * Module Name: test/produce
 * Filename: failed.c
 * Creator: Yaokai Liu
 * Create Date: 2024-07-13
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "action.h"
#include "allocator.h"
#include "char_t.h"
#include "terminal.h"
#include "token.h"
#include "tokens.gen.h"
#include <check.h>

#define string_to_test "(abcd[(sdcc)])"

START_TEST(test_ILLEGAL) {
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
  ck_assert_ptr_eq(regexp, nullptr);

  STDAllocator.free(terminals);
}

END_TEST

Suite *illegal_suite() {
  Suite *suite = suite_create("_Illegal");
  TCase *t_case = tcase_create("illegal");
  tcase_add_test(t_case, test_ILLEGAL);
  suite_add_tcase(suite, t_case);
  return suite;
}
