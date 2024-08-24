/**
 * Project Name: regex
 * Module Name: test/produce
 * Filename: group.c
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

#define string_to_test "(1234[5678]^[4321]^abcd{4})"

START_TEST(test_GROUP_NORMAL) {
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
  ck_assert_uint_eq(Array_length(regexp), 1);
  Branch *branch = (Branch *) Array_get(regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(branch), 1);
  Object *object = (Object *) Array_get(branch, 0);
  ck_assert_ptr_ne(object, nullptr);
  ck_assert_uint_eq(object->type, enum_Group);
  ck_assert_uint_eq(object->inv, false);

  Group *group = (Group *) object->target;
  ck_assert_ptr_ne(group, nullptr);
  Regexp *sub_regexp = group->regexp;
  ck_assert_ptr_ne(sub_regexp, nullptr);
  ck_assert_uint_eq(Array_length(sub_regexp), 1);
  Branch *sub_branch = (Branch *) Array_get(sub_regexp, 0);
  ck_assert_ptr_ne(branch, nullptr);
  ck_assert_uint_eq(Array_length(sub_branch), 5);
  Object *sub_object1 = (Object *) Array_get(sub_branch, 0);
  ck_assert_ptr_ne(sub_object1, nullptr);
  ck_assert_uint_eq(sub_object1->type, enum_Sequence);
  ck_assert_uint_eq(sub_object1->inv, false);
  Object *sub_object2 = (Object *) Array_get(sub_branch, 1);
  ck_assert_ptr_ne(sub_object2, nullptr);
  ck_assert_uint_eq(sub_object2->type, enum_Charset);
  ck_assert_uint_eq(sub_object2->inv, false);
  Object *sub_object3 = (Object *) Array_get(sub_branch, 2);
  ck_assert_ptr_ne(sub_object3, nullptr);
  ck_assert_uint_eq(sub_object3->type, enum_Charset);
  ck_assert_uint_eq(sub_object3->inv, true);
  Object *sub_object4 = (Object *) Array_get(sub_branch, 3);
  ck_assert_ptr_ne(sub_object4, nullptr);
  ck_assert_uint_eq(sub_object4->type, enum_CHAR);
  ck_assert_uint_eq(sub_object4->inv, true);
  Object *sub_object5 = (Object *) Array_get(sub_branch, 4);
  ck_assert_ptr_ne(sub_object5, nullptr);
  ck_assert_uint_eq(sub_object5->type, enum_Quantified);
  ck_assert_uint_eq(sub_object5->inv, false);

  releaseRegexp(regexp, &STDAllocator);
  Array_destroy(regexp);
  STDAllocator.free(terminals);
}

END_TEST

Suite *group_suite() {
  Suite *suite = suite_create("Group");
  TCase *t_case = tcase_create("group");
  tcase_add_test(t_case, test_GROUP_NORMAL);
  suite_add_tcase(suite, t_case);
  return suite;
}
