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
 * Filename: single-characters.c
 * Creator: Yaokai Liu
 * Create Date: 2024-7-5
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "allocator.h"
#include "char_t.h"
#include "generated/tokens.gen.h"
#include "regex/target.h"
#include "token.h"
#include "tokenize/RegexTokenizer.h"
#include <check.h>
#include <stdint.h>

START_TEST(test_TERMINATOR) {
  char_t *string = "";
  uint32_t cost, n_tokens;
  const Terminal *terminals = regex_tokenize(string, &cost, &n_tokens, nullptr, nullptr, &STDAllocator);
  ck_assert_uint_eq(cost, 0);
  ck_assert_uint_eq(n_tokens, 1);
  ck_assert_ptr_ne(terminals, nullptr);
  ck_assert_uint_eq(terminals[0].type, enum_TERMINATOR);
  ck_assert_uint_eq((uint64_t) terminals[0].value, 0);
  ck_assert_str_eq(get_name(terminals[0].type), string_t("TERMINATOR"));
  STDAllocator.free((void *) terminals);
}
END_TEST

#define add_test_for(_name, _value)                                                                  \
  START_TEST(test_##_name) {                                                                         \
    char_t *string = _value;                                                                         \
    uint32_t cost, n_tokens;                                                                         \
    const Terminal *terminals = regex_tokenize(string, &cost, &n_tokens, nullptr, nullptr, &STDAllocator); \
    ck_assert_uint_eq(cost, 1);                                                                      \
    ck_assert_uint_eq(n_tokens, 2);                                                                  \
    ck_assert_ptr_ne(terminals, nullptr);                                                            \
    ck_assert_uint_eq(terminals[0].type, enum_##_name);                                              \
    ck_assert_uint_eq((uint64_t) terminals[0].value, 0);                                             \
    ck_assert_str_eq(get_name(terminals[0].type), string_t(#_name));                                 \
    ck_assert_uint_eq(terminals[1].type, enum_TERMINATOR);                                           \
    ck_assert_uint_eq((uint64_t) terminals[1].value, 0);                                             \
    ck_assert_str_eq(get_name(terminals[1].type), string_t("TERMINATOR"));                           \
    STDAllocator.free((void *) terminals);                                                           \
  }                                                                                                  \
  END_TEST

#define add_test_for_QUANTIFIER(_name, _pattern, _min, _max)                                         \
  START_TEST(test_QUANTIFIER_##_name) {                                                              \
    char_t *string = _pattern;                                                                       \
    uint32_t cost, n_tokens;                                                                         \
    const Terminal *terminals = regex_tokenize(string, &cost, &n_tokens, nullptr, nullptr, &STDAllocator); \
    ck_assert_uint_eq(cost, 1);                                                                      \
    ck_assert_uint_eq(n_tokens, 2);                                                                  \
    ck_assert_ptr_ne(terminals, nullptr);                                                            \
    ck_assert_str_eq(get_name(terminals[0].type), string_t("QUANTIFIER"));                           \
    Quantifier quant = {_min, _max};                                                                 \
    ck_assert_uint_eq((uint64_t) terminals[0].value, Quantifier_toUint64(quant));                    \
    Quantifier quant2 = Quantifier_fromUint64((uint64_t) terminals[0].value);                        \
    ck_assert_uint_eq(quant2.max, quant.max);                                                        \
    ck_assert_uint_eq(quant2.min, quant.min);                                                        \
    ck_assert_uint_eq(terminals[1].type, enum_TERMINATOR);                                           \
    ck_assert_uint_eq((uint64_t) terminals[1].value, 0);                                             \
    ck_assert_str_eq(get_name(terminals[1].type), string_t("TERMINATOR"));                           \
    STDAllocator.free((void *) terminals);                                                           \
  }                                                                                                  \
  END_TEST

add_test_for(LEFT_SQUARE_BRACKET, "[")
add_test_for(RIGHT_SQUARE_BRACKET, "]")
add_test_for(LEFT_PARENTHESIS, "(")
add_test_for(RIGHT_PARENTHESIS, ")")
add_test_for(MINUS, "-")
add_test_for(INVERSE, "^")
add_test_for(SPLIT, "|")
add_test_for_QUANTIFIER(Q1, "*", 0, 0)
add_test_for_QUANTIFIER(Q2, "+", 1, 0)
add_test_for_QUANTIFIER(Q3, "?", 0, 1)

START_TEST(test_EMPTY_STRING) {
  char_t *string = "";
  uint32_t cost, n_tokens;
  const Terminal *terminals = regex_tokenize(string, &cost, &n_tokens, nullptr, nullptr, &STDAllocator);
  ck_assert_uint_eq(cost, 0);
  ck_assert_uint_eq(n_tokens, 1);
  ck_assert_ptr_ne(terminals, nullptr);
  ck_assert_uint_eq(terminals[0].type, enum_TERMINATOR);
  ck_assert_uint_eq((uint64_t) terminals[0].value, 0);
  ck_assert_str_eq(get_name(terminals[0].type), string_t("TERMINATOR"));
  STDAllocator.free((void *) terminals);
}
END_TEST

Suite *single_token_suite() {
  Suite *suite = suite_create("Single Token");
  TCase *tc_single_char = tcase_create("single-character");
  tcase_add_test(tc_single_char, test_TERMINATOR);
  tcase_add_test(tc_single_char, test_LEFT_SQUARE_BRACKET);
  tcase_add_test(tc_single_char, test_RIGHT_SQUARE_BRACKET);
  tcase_add_test(tc_single_char, test_LEFT_PARENTHESIS);
  tcase_add_test(tc_single_char, test_RIGHT_PARENTHESIS);
  tcase_add_test(tc_single_char, test_MINUS);
  tcase_add_test(tc_single_char, test_INVERSE);
  tcase_add_test(tc_single_char, test_SPLIT);
  tcase_add_test(tc_single_char, test_QUANTIFIER_Q1);
  tcase_add_test(tc_single_char, test_QUANTIFIER_Q2);
  tcase_add_test(tc_single_char, test_QUANTIFIER_Q3);
  tcase_add_test(tc_single_char, test_EMPTY_STRING);
  suite_add_tcase(suite, tc_single_char);
  return suite;
}

