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
 * Filename: char.c
 * Creator: Yaokai Liu
 * Create Date: 2024-7-6
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "allocator.h"
#include "char_t.h"
#include "tokens.h"
#include "token.h"
#include "regex.h"
#include "xlr.h"
#include <check.h>
#include <stdint.h>

START_TEST(test_CHAR_DIGITAL) {
  char_t *string = "0123456789";
  uint32_t cost, n_tokens;
  const Terminal *terminals = regex_tokenize(string, &cost, &n_tokens, nullptr, nullptr, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof "0123456789") - 1);
  ck_assert_uint_eq(n_tokens, (sizeof "0123456789"));
  ck_assert_ptr_ne(terminals, nullptr);
  for (uint32_t i = 0; i < n_tokens - 1; i++) {
    ck_assert_uint_eq(terminals[i].type, enum_SYMBOL);
    ck_assert_uint_eq((uint64_t) terminals[i].value, string[i]);
    ck_assert_str_eq(get_name(terminals[i].type), string_t("SYMBOL"));
  }
  ck_assert_uint_eq(terminals[n_tokens - 1].type, enum_TERMINATOR);
  ck_assert_uint_eq((uint64_t) terminals[n_tokens - 1].value, 0);
  ck_assert_str_eq(get_name(terminals[n_tokens - 1].type), string_t("TERMINATOR"));
  STDAllocator.free((void *) terminals);
}
END_TEST

START_TEST(test_CHAR_LOWER) {
  char_t *string = "abcdefghijklmnopqrstuvwxyz";
  uint32_t cost, n_tokens;
  const Terminal *terminals = regex_tokenize(string, &cost, &n_tokens, nullptr, nullptr, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof "abcdefghijklmnopqrstuvwxyz") - 1);
  ck_assert_uint_eq(n_tokens, (sizeof "abcdefghijklmnopqrstuvwxyz"));
  ck_assert_ptr_ne(terminals, nullptr);
  for (uint32_t i = 0; i < n_tokens - 1; i++) {
    ck_assert_uint_eq(terminals[i].type, enum_SYMBOL);
    ck_assert_uint_eq((uint64_t) terminals[i].value, string[i]);
    ck_assert_str_eq(get_name(terminals[i].type), string_t("SYMBOL"));
  }
  ck_assert_uint_eq(terminals[n_tokens - 1].type, enum_TERMINATOR);
  ck_assert_uint_eq((uint64_t) terminals[n_tokens - 1].value, 0);
  ck_assert_str_eq(get_name(terminals[n_tokens - 1].type), string_t("TERMINATOR"));
  STDAllocator.free((void *) terminals);
}
END_TEST

START_TEST(test_CHAR_UPPER) {
  char_t *string = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  uint32_t cost, n_tokens;
  const Terminal *terminals = regex_tokenize(string, &cost, &n_tokens, nullptr, nullptr, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof "ABCDEFGHIJKLMNOPQRSTUVWXYZ") - 1);
  ck_assert_uint_eq(n_tokens, (sizeof "ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
  ck_assert_ptr_ne(terminals, nullptr);
  for (uint32_t i = 0; i < n_tokens - 1; i++) {
    ck_assert_uint_eq(terminals[i].type, enum_SYMBOL);
    ck_assert_uint_eq((uint64_t) terminals[i].value, string[i]);
    ck_assert_str_eq(get_name(terminals[i].type), string_t("SYMBOL"));
  }
  ck_assert_uint_eq(terminals[n_tokens - 1].type, enum_TERMINATOR);
  ck_assert_uint_eq((uint64_t) terminals[n_tokens - 1].value, 0);
  ck_assert_str_eq(get_name(terminals[n_tokens - 1].type), string_t("TERMINATOR"));
  STDAllocator.free((void *) terminals);
}
END_TEST

START_TEST(test_CHAR_SYMBOL) {
  char_t *string = "~@#$%&:;\"'<>./{";
  uint32_t cost, n_tokens;
  const Terminal *terminals = regex_tokenize(string, &cost, &n_tokens, nullptr, nullptr, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof "~@#$%&:;\"'<>./{") - 1);
  ck_assert_uint_eq(n_tokens, (sizeof "~@#$%&:;\"'<>./{"));
  ck_assert_ptr_ne(terminals, nullptr);
  for (uint32_t i = 0; i < n_tokens - 1; i++) {
    ck_assert_uint_eq(terminals[i].type, enum_SYMBOL);
    ck_assert_uint_eq((uint64_t) terminals[i].value, string[i]);
    ck_assert_str_eq(get_name(terminals[i].type), string_t("SYMBOL"));
  }
  ck_assert_uint_eq(terminals[n_tokens - 1].type, enum_TERMINATOR);
  ck_assert_uint_eq((uint64_t) terminals[n_tokens - 1].value, 0);
  ck_assert_str_eq(get_name(terminals[n_tokens - 1].type), string_t("TERMINATOR"));
  STDAllocator.free((void *) terminals);
}
END_TEST

START_TEST(test_IDENTIFIER) {
  char_t *string = "abcd_efg";
  uint32_t cost, n_tokens;
  Array *ident_array = Array_new(sizeof(char_t), enum_SYMBOL, &STDAllocator);
  Array_append(ident_array, "", 1);
  const Terminal *terminals = xlr_tokenize(string, &cost, ident_array, &n_tokens, nullptr, nullptr, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof "abcd_efg") - 1);
  ck_assert_uint_eq(n_tokens, 2);
  ck_assert_ptr_ne(terminals, nullptr);
  ck_assert_uint_eq(terminals[0].type, enum_SYMBOL);
  char_t *ident = Array_virt2real(ident_array, terminals[0].value);
  ck_assert_str_eq(ident, string);
  ck_assert_str_eq(get_name(terminals[0].type), string_t("SYMBOL"));
  ck_assert_uint_eq(terminals[1].type, enum_TERMINATOR);
  ck_assert_uint_eq((uint64_t) terminals[1].value, 0);
  ck_assert_str_eq(get_name(terminals[1].type), string_t("TERMINATOR"));
  STDAllocator.free((void *) terminals);
}
END_TEST

START_TEST(test_IDENTIFIER_2) {
  char_t *string = "_ABCde f012";
  uint32_t cost, n_tokens;
  Array *ident_array = Array_new(sizeof(char_t), enum_SYMBOL, &STDAllocator);
  Array_append(ident_array, "", 1);
  const Terminal *terminals = xlr_tokenize(string, &cost, ident_array, &n_tokens, nullptr, nullptr, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof "_ABCde f012") - 1);
  ck_assert_uint_eq(n_tokens, 3);
  ck_assert_ptr_ne(terminals, nullptr);
  ck_assert_uint_eq(terminals[0].type, enum_SYMBOL);
  char_t *ident1 = Array_virt2real(ident_array, terminals[0].value);
  ck_assert_str_eq(ident1, "_ABCde");
  ck_assert_str_eq(get_name(terminals[0].type), string_t("SYMBOL"));
  ck_assert_uint_eq(terminals[1].type, enum_SYMBOL);
  char_t *ident2 = Array_virt2real(ident_array, terminals[1].value);
  ck_assert_str_eq(ident2, "f012");
  ck_assert_str_eq(get_name(terminals[1].type), string_t("SYMBOL"));
  ck_assert_uint_eq(terminals[2].type, enum_TERMINATOR);
  ck_assert_uint_eq((uint64_t) terminals[2].value, 0);
  ck_assert_str_eq(get_name(terminals[2].type), string_t("TERMINATOR"));
  STDAllocator.free((void *) terminals);
}
END_TEST

START_TEST(test_IDENTIFIER_3) {
  const char_t * const string = "~@#$%&:;\"'<>./{}";
  uint32_t cost = 0, n_tokens = 0;
  Array *ident_array = Array_new(sizeof(char_t), enum_SYMBOL, &STDAllocator);
  Array_append(ident_array, "", 1);
  for (uint32_t i = 0; i < strlen(string); i++) {
    const Terminal *terminals = xlr_tokenize(&string[i], &cost, ident_array, &n_tokens, nullptr, nullptr, &STDAllocator);
    ck_assert_uint_eq(cost, 0);
    ck_assert_uint_eq(n_tokens, 0);
    ck_assert_ptr_eq(terminals, nullptr);
  }
}
END_TEST

Suite *char_suite() {
  Suite *suite = suite_create("Single Token");
  TCase *tc_number = tcase_create("char");
  tcase_add_test(tc_number, test_CHAR_DIGITAL);
  tcase_add_test(tc_number, test_CHAR_LOWER);
  tcase_add_test(tc_number, test_CHAR_UPPER);
  tcase_add_test(tc_number, test_CHAR_SYMBOL);
  tcase_add_test(tc_number, test_IDENTIFIER);
  tcase_add_test(tc_number, test_IDENTIFIER_2);
  tcase_add_test(tc_number, test_IDENTIFIER_3);
  suite_add_tcase(suite, tc_number);
  return suite;
}
