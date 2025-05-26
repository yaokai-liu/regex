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
 * Module Name: test/tokenize
 * Filename: number.c
 * Creator: Yaokai Liu
 * Create Date: 2024-7-6
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "allocator.h"
#include "char_t.h"
#include "tokens.h"
#include "regex/target.h"
#include "token.h"
#include "regex.h"
#include <check.h>
#include <stdint.h>

START_TEST(test_NUMBER) {
  char_t *string = "{255}";
  uint32_t cost, n_tokens;
  const Terminal *terminals = regex_tokenize(string, &cost, &n_tokens, nullptr, nullptr, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof "{255}") - 1);
  ck_assert_uint_eq(n_tokens, 2);
  ck_assert_ptr_ne(terminals, nullptr);
  ck_assert_uint_eq(terminals[0].type, enum_QUANTIFIER);
  ck_assert_str_eq(get_name(terminals[0].type), string_t("QUANTIFIER"));
  Quantifier quant = {255, 255};
  ck_assert_uint_eq((uint64_t) terminals[0].value, Quantifier_toUint64(quant));
  Quantifier quant2 = Quantifier_fromUint64((uint64_t) terminals[0].value);
  ck_assert_uint_eq(quant2.max, quant.max);
  ck_assert_uint_eq(quant2.min, quant.min);
  ck_assert_uint_eq(terminals[1].type, enum_TERMINATOR);
  ck_assert_uint_eq((uint64_t) terminals[1].value, 0);
  ck_assert_str_eq(get_name(terminals[1].type), string_t("TERMINATOR"));
  STDAllocator.free((void *) terminals);
}
END_TEST

START_TEST(test_NUMBER2) {
  char_t *string = "{256}";
  uint32_t cost, n_tokens;
  const Terminal *terminals = regex_tokenize(string, &cost, &n_tokens, nullptr, nullptr, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof "{256}") - 1);
  ck_assert_uint_eq(n_tokens, 2);
  ck_assert_ptr_ne(terminals, nullptr);
  ck_assert_uint_eq(terminals[0].type, enum_QUANTIFIER);
  ck_assert_str_eq(get_name(terminals[0].type), string_t("QUANTIFIER"));
  Quantifier quant = {256, 256};
  ck_assert_uint_eq((uint64_t) terminals[0].value, Quantifier_toUint64(quant));
  Quantifier quant2 = Quantifier_fromUint64((uint64_t) terminals[0].value);
  ck_assert_uint_eq(quant2.max, quant.max);
  ck_assert_uint_eq(quant2.min, quant.min);
  ck_assert_uint_eq(terminals[1].type, enum_TERMINATOR);
  ck_assert_uint_eq((uint64_t) terminals[1].value, 0);
  ck_assert_str_eq(get_name(terminals[1].type), string_t("TERMINATOR"));
  STDAllocator.free((void *) terminals);
}
END_TEST

START_TEST(test_NUMBER3) {
  char_t *string = "{65536}";
  uint32_t cost, n_tokens;
  const Terminal *terminals = regex_tokenize(string, &cost, &n_tokens, nullptr, nullptr, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof "{65536}") - 1);
  ck_assert_uint_eq(n_tokens, 2);
  ck_assert_ptr_ne(terminals, nullptr);
  ck_assert_uint_eq(terminals[0].type, enum_QUANTIFIER);
  ck_assert_str_eq(get_name(terminals[0].type), string_t("QUANTIFIER"));
  Quantifier quant = {65536, 65536};
  ck_assert_uint_eq((uint64_t) terminals[0].value, Quantifier_toUint64(quant));
  Quantifier quant2 = Quantifier_fromUint64((uint64_t) terminals[0].value);
  ck_assert_uint_eq(quant2.max, quant.max);
  ck_assert_uint_eq(quant2.min, quant.min);
  ck_assert_uint_eq(terminals[1].type, enum_TERMINATOR);
  ck_assert_uint_eq((uint64_t) terminals[1].value, 0);
  ck_assert_str_eq(get_name(terminals[1].type), string_t("TERMINATOR"));
  STDAllocator.free((void *) terminals);
}
END_TEST

START_TEST(test_NUMBER4) {
  char_t *string = "{4294967295}";
  uint32_t cost, n_tokens;
  const Terminal *terminals = regex_tokenize(string, &cost, &n_tokens, nullptr, nullptr, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof "{4294967295}") - 1);
  ck_assert_uint_eq(n_tokens, 2);
  ck_assert_ptr_ne(terminals, nullptr);
  ck_assert_uint_eq(terminals[0].type, enum_QUANTIFIER);
  ck_assert_str_eq(get_name(terminals[0].type), string_t("QUANTIFIER"));
  Quantifier quant = {4294967295, 4294967295};
  ck_assert_uint_eq((uint64_t) terminals[0].value, Quantifier_toUint64(quant));
  Quantifier quant2 = Quantifier_fromUint64((uint64_t) terminals[0].value);
  ck_assert_uint_eq(quant2.max, quant.max);
  ck_assert_uint_eq(quant2.min, quant.min);
  ck_assert_uint_eq(terminals[1].type, enum_TERMINATOR);
  ck_assert_uint_eq((uint64_t) terminals[1].value, 0);
  ck_assert_str_eq(get_name(terminals[1].type), string_t("TERMINATOR"));
  STDAllocator.free((void *) terminals);
}
END_TEST

START_TEST(test_NUMBER_overflow) {
  char_t *string = "{4294967296}";
  uint32_t cost, n_tokens;
  const Terminal *terminals = regex_tokenize(string, &cost, &n_tokens, nullptr, nullptr, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof "{4294967296}") - 1);
  ck_assert_uint_eq(n_tokens, 2);
  ck_assert_ptr_ne(terminals, nullptr);
  ck_assert_uint_eq(terminals[0].type, enum_QUANTIFIER);
  ck_assert_str_eq(get_name(terminals[0].type), string_t("QUANTIFIER"));
  Quantifier quant = {0, 0};
  ck_assert_uint_eq((uint64_t) terminals[0].value, Quantifier_toUint64(quant));
  Quantifier quant2 = Quantifier_fromUint64((uint64_t) terminals[0].value);
  ck_assert_uint_eq(quant2.max, quant.max);
  ck_assert_uint_eq(quant2.min, quant.min);
  ck_assert_uint_eq(terminals[1].type, enum_TERMINATOR);
  ck_assert_uint_eq((uint64_t) terminals[1].value, 0);
  ck_assert_str_eq(get_name(terminals[1].type), string_t("TERMINATOR"));
  STDAllocator.free((void *) terminals);
}
END_TEST

Suite *number_suite() {
  Suite *suite = suite_create("Continuous Tokens");
  TCase *tc_number = tcase_create("number");
  tcase_add_test(tc_number, test_NUMBER);
  tcase_add_test(tc_number, test_NUMBER2);
  tcase_add_test(tc_number, test_NUMBER3);
  tcase_add_test(tc_number, test_NUMBER4);
  tcase_add_test(tc_number, test_NUMBER_overflow);
  suite_add_tcase(suite, tc_number);
  return suite;
}
