/**
 * Project Name: regex
 * Module Name: test/tokenize
 * Filename: char.c
 * Creator: Yaokai Liu
 * Create Date: 24-7-6
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "allocator.h"
#include "char_t.h"
#include "terminal.h"
#include "token.h"
#include "tokens.gen.h"
#include <check.h>
#include <stdint.h>

START_TEST(test_CHAR_1) {
  char_t *string = "1";
  uint32_t cost, n_tokens;
  Terminal *terminals = tokenize(string, &cost, &n_tokens, &STDAllocator);
  ck_assert_uint_eq(cost, 1);
  ck_assert_uint_eq(n_tokens, 2);
  ck_assert_ptr_ne(terminals, nullptr);
  for (uint32_t i = 0; i < n_tokens - 1; i++) {
    ck_assert_uint_eq(terminals[0].type, enum_CHAR);
    ck_assert_uint_eq(terminals[0].value, string[i]);
    ck_assert_str_eq(get_name(terminals[0].type), string_t("CHAR"));
  }
  ck_assert_uint_eq(terminals[1].type, enum_TERMINATOR);
  ck_assert_uint_eq(terminals[1].value, 0);
  ck_assert_str_eq(get_name(terminals[1].type), string_t("TERMINATOR"));
  STDAllocator.free(terminals);
}
END_TEST

Suite *char_suite() {
  Suite *suite = suite_create("Single Token");
  TCase *tc_number = tcase_create("char");
  tcase_add_test(tc_number, test_CHAR_1);
  suite_add_tcase(suite, tc_number);
  return suite;
}
