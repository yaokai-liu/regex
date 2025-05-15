/**
 * Project Name: regex
 * Module Name: test/parse
 * Filename: failed.c
 * Creator: Yaokai Liu
 * Create Date: 2024-07-13
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "action.h"
#include "allocator.h"
#include "char_t.h"
#include "generated/tokens.gen.h"
#include "regex/parse.h"
#include "regex/target.h"
#include "terminal.h"
#include "tokenize.h"
#include <check.h>

#define string_to_test "(abcd[(sdcc)])"

START_TEST(test_ILLEGAL) {
  char_t *string = string_to_test;
  ErrInfo errInfo = {};
  Regex *regexp = parse(string, nullptr, nullptr, &errInfo, &STDAllocator);
  ck_assert_ptr_eq(regexp, nullptr);
}

END_TEST

Suite *illegal_suite() {
  Suite *suite = suite_create("_Illegal");
  TCase *t_case = tcase_create("illegal");
  tcase_add_test(t_case, test_ILLEGAL);
  suite_add_tcase(suite, t_case);
  return suite;
}
