/**
 * Project Name: regex
 * Module Name: test/tokenize
 * Filename: number.c
 * Creator: Yaokai Liu
 * Create Date: 2024-7-6
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "allocator.h"
#include "char_t.h"
#include "terminal.h"
#include "token.h"
#include "tokens.gen.h"
#include <check.h>
#include <stdint.h>

START_TEST(test_NUMBER) {
  char_t *string = "{255}";
  uint32_t cost, n_tokens;
  Terminal *terminals = tokenize(string, &cost, &n_tokens, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof "{256}") - 1);
  ck_assert_uint_eq(n_tokens, 4);
  ck_assert_ptr_ne(terminals, nullptr);
  ck_assert_uint_eq(terminals[0].type, enum_BEGIN_QUANTIFIER);
  ck_assert_uint_eq(terminals[0].value, 0);
  ck_assert_str_eq(get_name(terminals[0].type), string_t("BEGIN_QUANTIFIER"));
  ck_assert_uint_eq(terminals[1].type, enum_NUMBER);
  ck_assert_uint_eq(terminals[1].value, 255);
  ck_assert_str_eq(get_name(terminals[1].type), string_t("NUMBER"));
  ck_assert_uint_eq(terminals[2].type, enum_END_QUANTIFIER);
  ck_assert_uint_eq(terminals[2].value, 0);
  ck_assert_str_eq(get_name(terminals[2].type), string_t("END_QUANTIFIER"));
  ck_assert_uint_eq(terminals[3].type, enum_TERMINATOR);
  ck_assert_uint_eq(terminals[3].value, 0);
  ck_assert_str_eq(get_name(terminals[3].type), string_t("TERMINATOR"));
  STDAllocator.free(terminals);
}
END_TEST

Suite *number_suite() {
  Suite *suite = suite_create("Continuous Tokens");
  TCase *tc_number = tcase_create("number");
  tcase_add_test(tc_number, test_NUMBER);
  suite_add_tcase(suite, tc_number);
  return suite;
}
