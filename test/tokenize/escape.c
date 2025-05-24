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
 * Filename: escape.c
 * Creator: Yaokai Liu
 * Create Date: 2025-05-22
 * Copyright (c) 2025 Yaokai Liu. All rights reserved.
 **/

#include "allocator.h"
#include "char_t.h"
#include "enum.h"
#include "generated/tokens.gen.h"
#include "token.h"
#include "tokenize/RegexTokenizer.h"
#include <check.h>
#include <stdint.h>

#define add_test_for(_name, _pattern, _value)                                     \
  START_TEST(test_ESCAPE_##_name) {                                               \
    char_t *string = _pattern;                                                    \
    uint32_t cost = 0, n_tokens = 0;                                              \
    const Terminal *terminals = regex_tokenize(string, &cost, &n_tokens,          \
                                               nullptr, nullptr, &STDAllocator);  \
    ck_assert_uint_eq(cost, (sizeof _pattern) - 1);                               \
    ck_assert_uint_eq(n_tokens, 2);                                               \
    ck_assert_ptr_ne(terminals, nullptr);                                         \
    ck_assert_uint_eq(terminals[0].type, enum_CHARSET_ESCAPE);                    \
    ck_assert_str_eq(get_name(terminals[0].type), string_t("CHARSET_ESCAPE"));    \
    ck_assert_uint_eq((uint64_t) terminals[0].value, _value);                     \
    ck_assert_uint_eq(terminals[1].type, enum_TERMINATOR);                        \
    ck_assert_uint_eq((uint64_t) terminals[1].value, 0);                          \
    ck_assert_str_eq(get_name(terminals[1].type), string_t("TERMINATOR"));        \
    STDAllocator.free((void *) terminals);                                        \
  }                                                                               \
  END_TEST

add_test_for(CHARSET_DEC_DIGITAL, "\\d", CHARSET_DEC_DIGITAL);
add_test_for(CHARSET_HEX_DIGITAL, "\\D", CHARSET_HEX_DIGITAL);
add_test_for(CHARSET_LETTER, "\\w", CHARSET_LETTER);
add_test_for(CHARSET_IDENT, "\\W", CHARSET_IDENT);
add_test_for(CHARSET_LOWER_LETTER, "\\a", CHARSET_LOWER_LETTER);
add_test_for(CHARSET_UPPER_LETTER, "\\A", CHARSET_UPPER_LETTER);

START_TEST(test_ESCAPE_FALL_THROUGH) {
  char_t *string = "\\[";
  uint32_t cost, n_tokens;
  const Terminal *terminals = regex_tokenize(string, &cost, &n_tokens, nullptr, nullptr, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof "\\[") - 1);
  ck_assert_uint_eq(n_tokens, 2);
  ck_assert_ptr_ne(terminals, nullptr);
  ck_assert_uint_eq(terminals[0].type, enum_SYMBOL);
  ck_assert_str_eq(get_name(terminals[0].type), string_t("SYMBOL"));
  ck_assert_uint_eq((uint64_t) terminals[0].value, '[');
  ck_assert_uint_eq(terminals[1].type, enum_TERMINATOR);
  ck_assert_uint_eq((uint64_t) terminals[1].value, 0);
  ck_assert_str_eq(get_name(terminals[1].type), string_t("TERMINATOR"));
  STDAllocator.free((void *) terminals);
}
END_TEST

Suite *escape_suite() {
  Suite *suite = suite_create("Continuous Tokens");
  TCase *tc_escape = tcase_create("escape");
  tcase_add_test(tc_escape, test_ESCAPE_CHARSET_DEC_DIGITAL);
  tcase_add_test(tc_escape, test_ESCAPE_CHARSET_HEX_DIGITAL);
  tcase_add_test(tc_escape, test_ESCAPE_CHARSET_LETTER);
  tcase_add_test(tc_escape, test_ESCAPE_CHARSET_IDENT);
  tcase_add_test(tc_escape, test_ESCAPE_CHARSET_LOWER_LETTER);
  tcase_add_test(tc_escape, test_ESCAPE_CHARSET_UPPER_LETTER);
  tcase_add_test(tc_escape, test_ESCAPE_FALL_THROUGH);
  suite_add_tcase(suite, tc_escape);
  return suite;
}
