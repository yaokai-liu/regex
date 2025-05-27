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
 * Filename: quantifier.c
 * Creator: Yaokai Liu
 * Create Date: 2025-05-22
 * Copyright (c) 2025 Yaokai Liu. All rights reserved.
 **/

#include "allocator.h"
#include "regex/char_t.h"
#include "regex/enum.h"
#include "regex/tokens.h"
#include "regex/target.h"
#include "regex/token.h"
#include "regex/regex.h"
#include <check.h>
#include <stdint.h>

#define add_test_for(_name, _pattern, _min, _max)                                 \
  START_TEST(test_QUANTIFIER_##_name) {                                           \
    char_t *string = _pattern;                                                    \
    uint32_t cost, n_tokens;                                                      \
    const Terminal *terminals = regex_tokenize(string, &cost, &n_tokens,          \
                                               nullptr, nullptr, &STDAllocator);  \
    ck_assert_uint_eq(cost, (sizeof _pattern) - 1);                               \
    ck_assert_uint_eq(n_tokens, 2);                                               \
    ck_assert_ptr_ne(terminals, nullptr);                                         \
    ck_assert_uint_eq(terminals[0].type, enum_QUANTIFIER);                        \
    ck_assert_str_eq(get_name(terminals[0].type), string_t("QUANTIFIER"));        \
    Quantifier quant = {.min = _min, .max = _max};                                \
    ck_assert_uint_eq((uint64_t) terminals[0].value, Quantifier_toUint64(quant)); \
    Quantifier quant2 = Quantifier_fromUint64((uint64_t) terminals[0].value);     \
    ck_assert_uint_eq(quant2.max, quant.max);                                     \
    ck_assert_uint_eq(quant2.min, quant.min);                                     \
    ck_assert_uint_eq(terminals[1].type, enum_TERMINATOR);                        \
    ck_assert_uint_eq((uint64_t) terminals[1].value, 0);                          \
    ck_assert_str_eq(get_name(terminals[1].type), string_t("TERMINATOR"));        \
    STDAllocator.free((void *) terminals);                                        \
  }                                                                               \
  END_TEST

add_test_for(MIN_AND_MAX, "{12, 34}", 12, 34)
add_test_for(MIN_BUT_NO_MAX, "{12,}", 12, 0)
add_test_for(NO_MIN_BUT_MAX, "{, 34}", 0, 34)
add_test_for(NO_MIN_AND_NO_MAX, "{ , }", 0, 0)
add_test_for(MIN_SAME_MAX, "{67}", 67, 67)

Suite *quantifier_suite() {
  Suite *suite = suite_create("Continuous Tokens");
  TCase *tc_quantifier = tcase_create("number");
  tcase_add_test(tc_quantifier, test_QUANTIFIER_MIN_AND_MAX);
  tcase_add_test(tc_quantifier, test_QUANTIFIER_MIN_BUT_NO_MAX);
  tcase_add_test(tc_quantifier, test_QUANTIFIER_NO_MIN_BUT_MAX);
  tcase_add_test(tc_quantifier, test_QUANTIFIER_NO_MIN_AND_NO_MAX);
  tcase_add_test(tc_quantifier, test_QUANTIFIER_MIN_SAME_MAX);
  suite_add_tcase(suite, tc_quantifier);
  return suite;
}
