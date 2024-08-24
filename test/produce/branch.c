/**
 * Project Name: regex
 * Module Name: test/produce
 * Filename: branch.c
 * Creator: Yaokai Liu
 * Create Date: 2024-07-13
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "action.h"
#include "allocator.h"
#include "char_t.h"
#include "terminal.h"
#include "token.h"
#include "tokens.gen.h"
#include <check.h>

#define string_to_test "^(abcd)|efg|()"

START_TEST(test_BRANCH_NORMAL) {
  char_t *string = string_to_test;
  uint32_t cost, n_tokens;
  Terminal *terminals = tokenize(string, &cost, &n_tokens, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof string_to_test) - 1);
  ck_assert_uint_eq(n_tokens, (sizeof string_to_test));
  ck_assert_ptr_ne(terminals, nullptr);
  ck_assert_uint_eq(terminals[n_tokens - 1].type, enum_TERMINATOR);
  ck_assert_uint_eq(terminals[n_tokens - 1].value, 0);
  ck_assert_str_eq(get_name(terminals[n_tokens - 1].type), string_t("TERMINATOR"));
  Regexp *regexp = produce(terminals, &STDAllocator);
  ck_assert_ptr_ne(regexp, nullptr);
  ck_assert_uint_eq(Array_length(regexp), 3);

  Branch *branch1 = (Branch *) Array_get(regexp, 0);
  ck_assert_ptr_ne(branch1, nullptr);
  ck_assert_uint_eq(Array_length(branch1), 1);
  Object *object1 = (Object *) Array_get(branch1, 0);
  ck_assert_ptr_ne(object1, nullptr);
  ck_assert_uint_eq(object1->type, enum_Group);
  ck_assert_uint_eq(object1->inv, true);
  Group *group1 = object1->target;
  ck_assert_ptr_ne(group1, nullptr);
  Regexp *sub_regexp1 = group1->regexp;
  ck_assert_uint_eq(Array_length(sub_regexp1), 1);
  Branch *branch2 = (Branch *) Array_get(regexp, 1);
  ck_assert_ptr_ne(branch2, nullptr);
  ck_assert_uint_eq(Array_length(branch1), 1);
  Object *object2 = (Object *) Array_get(branch2, 0);
  ck_assert_ptr_ne(object2, nullptr);
  ck_assert_uint_eq(object2->type, enum_Sequence);
  ck_assert_uint_eq(object2->inv, false);
  Sequence *sequence = object2->target;
  ck_assert_ptr_ne(sequence, nullptr);
  Branch *branch3 = (Branch *) Array_get(regexp, 2);
  ck_assert_ptr_ne(branch3, nullptr);
  ck_assert_uint_eq(Array_length(branch1), 1);
  Object *object3 = (Object *) Array_get(branch3, 0);
  ck_assert_ptr_ne(object3, nullptr);
  ck_assert_uint_eq(object3->type, enum_Group);
  ck_assert_uint_eq(object3->inv, false);
  Group *group2 = object3->target;
  ck_assert_ptr_ne(group2, nullptr);
  Regexp *sub_regexp = group2->regexp;
  ck_assert_ptr_ne(sub_regexp, nullptr);
  ck_assert_uint_eq(Array_length(sub_regexp), 0);

  releaseRegexp(regexp, &STDAllocator);
  Array_destroy(regexp);
  STDAllocator.free(terminals);
}

END_TEST

Suite *branch_suite() {
  Suite *suite = suite_create("Branch");
  TCase *t_case = tcase_create("branch");
  tcase_add_test(t_case, test_BRANCH_NORMAL);
  suite_add_tcase(suite, t_case);
  return suite;
}
