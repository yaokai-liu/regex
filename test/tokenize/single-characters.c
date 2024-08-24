/**
 * Project Name: regex
 * Module Name: test/produce
 * Filename: single-characters.c
 * Creator: Yaokai Liu
 * Create Date: 2024-7-5
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "allocator.h"
#include "char_t.h"
#include "terminal.h"
#include "token.h"
#include "tokens.gen.h"
#include <check.h>
#include <stdint.h>

START_TEST(test_TERMINATOR) {
  char_t *string = "";
  uint32_t cost, n_tokens;
  Terminal *terminals = tokenize(string, &cost, &n_tokens, &STDAllocator);
  ck_assert_uint_eq(cost, 0);
  ck_assert_uint_eq(n_tokens, 1);
  ck_assert_ptr_ne(terminals, nullptr);
  ck_assert_uint_eq(terminals[0].type, enum_TERMINATOR);
  ck_assert_uint_eq(terminals[0].value, 0);
  ck_assert_str_eq(get_name(terminals[0].type), string_t("TERMINATOR"));
  STDAllocator.free(terminals);
}
END_TEST

#define add_test_for(_name, _value)                                          \
  START_TEST(test_##_name) {                                                 \
    char_t *string = _value;                                                 \
    uint32_t cost, n_tokens;                                                 \
    Terminal *terminals = tokenize(string, &cost, &n_tokens, &STDAllocator); \
    ck_assert_uint_eq(cost, 1);                                              \
    ck_assert_uint_eq(n_tokens, 2);                                          \
    ck_assert_ptr_ne(terminals, nullptr);                                    \
    ck_assert_uint_eq(terminals[0].type, enum_##_name);                      \
    ck_assert_uint_eq(terminals[0].value, 0);                                \
    ck_assert_str_eq(get_name(terminals[0].type), string_t(#_name));         \
    ck_assert_uint_eq(terminals[1].type, enum_TERMINATOR);                   \
    ck_assert_uint_eq(terminals[1].value, 0);                                \
    ck_assert_str_eq(get_name(terminals[1].type), string_t("TERMINATOR"));   \
    STDAllocator.free(terminals);                                            \
  }                                                                          \
  END_TEST

add_test_for(BEGIN_CHARSET, "[") add_test_for(BEGIN_GROUP, "(") add_test_for(BEGIN_QUANTIFIER, "{")
  add_test_for(COMMA, ",") add_test_for(END_CHARSET, "]") add_test_for(END_GROUP, ")")
    add_test_for(END_QUANTIFIER, "}") add_test_for(MINUS, "-") add_test_for(NOT, "^")
      add_test_for(SPLIT, "|") add_test_for(PLUS, "+") add_test_for(QUEST, "?")
        add_test_for(TIMES, "*")

          Suite *single_token_suite() {
  Suite *suite = suite_create("Single Token");
  TCase *tc_single_char = tcase_create("single-character");
  tcase_add_test(tc_single_char, test_TERMINATOR);
  tcase_add_test(tc_single_char, test_BEGIN_CHARSET);
  tcase_add_test(tc_single_char, test_BEGIN_GROUP);
  tcase_add_test(tc_single_char, test_BEGIN_QUANTIFIER);
  tcase_add_test(tc_single_char, test_COMMA);
  tcase_add_test(tc_single_char, test_END_CHARSET);
  tcase_add_test(tc_single_char, test_END_GROUP);
  tcase_add_test(tc_single_char, test_END_QUANTIFIER);
  tcase_add_test(tc_single_char, test_MINUS);
  tcase_add_test(tc_single_char, test_NOT);
  tcase_add_test(tc_single_char, test_SPLIT);
  tcase_add_test(tc_single_char, test_PLUS);
  tcase_add_test(tc_single_char, test_QUEST);
  tcase_add_test(tc_single_char, test_TIMES);
  suite_add_tcase(suite, tc_single_char);
  return suite;
}

