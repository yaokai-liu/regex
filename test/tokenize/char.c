/**
 * Project Name: regex
 * Module Name: test/tokenize
 * Filename: char.c
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

START_TEST(test_CHAR_DIGITAL) {
  char_t *string = "0123456789";
  uint32_t cost, n_tokens;
  Terminal *terminals = tokenize(string, &cost, &n_tokens, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof "0123456789") - 1);
  ck_assert_uint_eq(n_tokens, (sizeof "0123456789"));
  ck_assert_ptr_ne(terminals, nullptr);
  for (uint32_t i = 0; i < n_tokens - 1; i++) {
    ck_assert_uint_eq(terminals[i].type, enum_CHAR);
    ck_assert_uint_eq(terminals[i].value, string[i]);
    ck_assert_str_eq(get_name(terminals[i].type), string_t("CHAR"));
  }
  ck_assert_uint_eq(terminals[n_tokens - 1].type, enum_TERMINATOR);
  ck_assert_uint_eq(terminals[n_tokens - 1].value, 0);
  ck_assert_str_eq(get_name(terminals[n_tokens - 1].type), string_t("TERMINATOR"));
  STDAllocator.free(terminals);
}
END_TEST

START_TEST(test_CHAR_LOWER) {
  char_t *string = "abcdefghijklmnopqrstuvwxyz";
  uint32_t cost, n_tokens;
  Terminal *terminals = tokenize(string, &cost, &n_tokens, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof "abcdefghijklmnopqrstuvwxyz") - 1);
  ck_assert_uint_eq(n_tokens, (sizeof "abcdefghijklmnopqrstuvwxyz"));
  ck_assert_ptr_ne(terminals, nullptr);
  for (uint32_t i = 0; i < n_tokens - 1; i++) {
    ck_assert_uint_eq(terminals[i].type, enum_CHAR);
    ck_assert_uint_eq(terminals[i].value, string[i]);
    ck_assert_str_eq(get_name(terminals[i].type), string_t("CHAR"));
  }
  ck_assert_uint_eq(terminals[n_tokens - 1].type, enum_TERMINATOR);
  ck_assert_uint_eq(terminals[n_tokens - 1].value, 0);
  ck_assert_str_eq(get_name(terminals[n_tokens - 1].type), string_t("TERMINATOR"));
  STDAllocator.free(terminals);
}
END_TEST

START_TEST(test_CHAR_UPPER) {
  char_t *string = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  uint32_t cost, n_tokens;
  Terminal *terminals = tokenize(string, &cost, &n_tokens, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof "ABCDEFGHIJKLMNOPQRSTUVWXYZ") - 1);
  ck_assert_uint_eq(n_tokens, (sizeof "ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
  ck_assert_ptr_ne(terminals, nullptr);
  for (uint32_t i = 0; i < n_tokens - 1; i++) {
    ck_assert_uint_eq(terminals[i].type, enum_CHAR);
    ck_assert_uint_eq(terminals[i].value, string[i]);
    ck_assert_str_eq(get_name(terminals[i].type), string_t("CHAR"));
  }
  ck_assert_uint_eq(terminals[n_tokens - 1].type, enum_TERMINATOR);
  ck_assert_uint_eq(terminals[n_tokens - 1].value, 0);
  ck_assert_str_eq(get_name(terminals[n_tokens - 1].type), string_t("TERMINATOR"));
  STDAllocator.free(terminals);
}
END_TEST

START_TEST(test_CHAR_SYMBOL) {
  char_t *string = "~!@#$%&:;\"'<>.\\/";
  uint32_t cost, n_tokens;
  Terminal *terminals = tokenize(string, &cost, &n_tokens, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof "~!@#$%&:;\"'<>.\\/") - 1);
  ck_assert_uint_eq(n_tokens, (sizeof "~!@#$%&:;\"'<>.\\/"));
  ck_assert_ptr_ne(terminals, nullptr);
  for (uint32_t i = 0; i < n_tokens - 1; i++) {
    ck_assert_uint_eq(terminals[i].type, enum_CHAR);
    ck_assert_uint_eq(terminals[i].value, string[i]);
    ck_assert_str_eq(get_name(terminals[i].type), string_t("CHAR"));
  }
  ck_assert_uint_eq(terminals[n_tokens - 1].type, enum_TERMINATOR);
  ck_assert_uint_eq(terminals[n_tokens - 1].value, 0);
  ck_assert_str_eq(get_name(terminals[n_tokens - 1].type), string_t("TERMINATOR"));
  STDAllocator.free(terminals);
}
END_TEST

Suite *char_suite() {
  Suite *suite     = suite_create("Single Token");
  TCase *tc_number = tcase_create("char");
  tcase_add_test(tc_number, test_CHAR_DIGITAL);
  tcase_add_test(tc_number, test_CHAR_LOWER);
  tcase_add_test(tc_number, test_CHAR_UPPER);
  tcase_add_test(tc_number, test_CHAR_SYMBOL);
  suite_add_tcase(suite, tc_number);
  return suite;
}
