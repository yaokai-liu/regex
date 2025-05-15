/**
 * Project Name: regex
 * Module Name: test/parse
 * Filename: group.c
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

#define string_to_test "(1234[5678]^[4321]^abcd{4})"

START_TEST(test_GROUP_NORMAL) {
  char_t *string = string_to_test;
  ErrInfo errInfo = {};
  Regex *regexp = parse(string, nullptr, nullptr, &errInfo, &STDAllocator);
  ck_assert_ptr_ne(regexp, nullptr);
  ck_assert_uint_eq(Array_length(regexp), 1);
  Branch *branch = (Branch *) Array_real_addr(regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(branch), 1);
  Object *object = (Object *) Array_real_addr(branch, 0);
  ck_assert_ptr_ne(object, nullptr);
  ck_assert_uint_eq(object->type, enum_Group);
  ck_assert_uint_eq(object->inverse, false);

  Group *group = (Group *) object->target;
  ck_assert_ptr_ne(group, nullptr);
  Regex *sub_regexp = group->regexp;
  ck_assert_ptr_ne(sub_regexp, nullptr);
  ck_assert_uint_eq(Array_length(sub_regexp), 1);
  Branch *sub_branch = (Branch *) Array_real_addr(sub_regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(sub_branch), 10);

  Array_destroy(regexp);
}

END_TEST

Suite *group_suite() {
  Suite *suite = suite_create("Group");
  TCase *t_case = tcase_create("group");
  tcase_add_test(t_case, test_GROUP_NORMAL);
  suite_add_tcase(suite, t_case);
  return suite;
}
