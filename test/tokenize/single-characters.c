/**
 * Project Name: regex
 * Module Name: test/produce
 * Filename: single-characters.c
 * Creator: Yaokai Liu
 * Create Date: 24-7-5
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "allocator.h"
#include "terminal.h"
#include "char_t.h"
#include "token.h"
#include "tokens.gen.h"
#include <check.h>
#include <stdint.h>

START_TEST(test_PLUS) {
    char_t * string = "+";
    uint32_t cost, n_tokens;
    Terminal * terminals = tokenize(string, &cost, &n_tokens, &STDAllocator);
    ck_assert_uint_eq(cost, 1);
    ck_assert_uint_eq(n_tokens, 1);
    ck_assert_ptr_ne(terminals, nullptr);
    ck_assert_uint_eq(terminals[0].type, enum_PLUS);
    ck_assert_uint_eq(terminals[0].value, 0);
    ck_assert_str_eq(get_name(terminals[0].type), string_t("PLUS"));
    STDAllocator.free(terminals);
}
END_TEST


Suite * single_character_suite() {

  Suite *suite = suite_create("Single-Character");

  TCase *tc_case = tcase_create("single-character");

  tcase_add_test(tc_case, test_PLUS);
  suite_add_tcase(suite, tc_case);
}

