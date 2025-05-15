/**
 * Project Name: regex
 * Module Name: test/parse
 * Filename: branch.c
 * Creator: Yaokai Liu
 * Create Date: 2024-07-13
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "action.h"
#include "allocator.h"
#include "char_t.h"
#include "enum.h"
#include "generated/tokens.gen.h"
#include "regex/parse.h"
#include "regex/target.h"
#include "terminal.h"
#include "tokenize.h"
#include <check.h>

#define string_to_test "^(abcd)|efg|()"

START_TEST(test_BRANCH_NORMAL) {
  char_t *string = string_to_test;
  ErrInfo errInfo = {};
  Regex *regexp = parse(string, nullptr, nullptr, &errInfo, &STDAllocator);
  ck_assert_ptr_ne(regexp, nullptr);
  ck_assert_uint_eq(Array_length(regexp), 3);

  Branch *branch1 = (Branch *) Array_real_addr(regexp, 0);
  ck_assert_ptr_ne(branch1, nullptr);
  ck_assert_uint_eq(Array_length(branch1), 1);
  Object *object1 = (Object *) Array_real_addr(branch1, 0);
  ck_assert_ptr_ne(object1, nullptr);
  ck_assert_uint_eq(object1->type, enum_Group);
  ck_assert_uint_eq(object1->inverse, true);
  Group *group1 = object1->target;
  ck_assert_ptr_ne(group1, nullptr);
  Regex *sub_regexp1 = group1->regexp;
  ck_assert_uint_eq(Array_length(sub_regexp1), 1);

  Branch *branch2 = (Branch *) Array_real_addr(regexp, 1);
  ck_assert_ptr_ne(branch2, nullptr);
  ck_assert_uint_eq(Array_length(branch2), 3);
  Object *objects2 = (Object *) Array_real_addr(branch2, 0);
  ck_assert_ptr_ne(objects2, nullptr);
  ck_assert_uint_eq(objects2[0].type, enum_CHAR);
  ck_assert_uint_eq(objects2[0].inverse, false);
  ck_assert_uint_eq(objects2[1].type, enum_CHAR);
  ck_assert_uint_eq(objects2[1].inverse, false);
  ck_assert_uint_eq(objects2[2].type, enum_CHAR);
  ck_assert_uint_eq(objects2[2].inverse, false);

  Branch *branch3 = (Branch *) Array_real_addr(regexp, 2);
  ck_assert_ptr_ne(branch3, nullptr);
  ck_assert_uint_eq(Array_length(branch1), 1);
  Object *object3 = (Object *) Array_real_addr(branch3, 0);
  ck_assert_ptr_ne(object3, nullptr);
  ck_assert_uint_eq(object3->type, enum_Group);
  ck_assert_uint_eq(object3->inverse, false);
  Group *group2 = object3->target;
  ck_assert_ptr_ne(group2, nullptr);
  Regex *sub_regexp = group2->regexp;
  ck_assert_ptr_eq(sub_regexp, nullptr);

  Array_destroy(regexp);
}

END_TEST

Suite *branch_suite() {
  Suite *suite = suite_create("Branch");
  TCase *t_case = tcase_create("branch");
  tcase_add_test(t_case, test_BRANCH_NORMAL);
  suite_add_tcase(suite, t_case);
  return suite;
}
