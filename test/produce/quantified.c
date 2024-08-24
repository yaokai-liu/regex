/**
 * Project Name: regex
 * Module Name: test/produce
 * Filename: quantified.c
 * Creator: Yaokai Liu
 * Create Date: 2024-7-13
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "action.h"
#include "allocator.h"
#include "char_t.h"
#include "terminal.h"
#include "token.h"
#include "tokens.gen.h"
#include <check.h>

#define string_to_test0 "123?"

START_TEST(test_QUANTIFIED_NURMAL0) {
  char_t *string = string_to_test0;
  uint32_t cost, n_tokens;
  Terminal *terminals = tokenize(string, &cost, &n_tokens, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof string_to_test0) - 1);
  ck_assert_uint_eq(n_tokens, (sizeof string_to_test0));
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
  ck_assert_uint_eq(object->type, enum_Quantified);
  ck_assert_uint_eq(object->inv, false);

  Quantified *quantified = (Quantified *) object->target;
  ck_assert_uint_eq(quantified->object.type, enum_Sequence);
  ck_assert_uint_eq(quantified->object.inv, false);
  Sequence *sequence = (Sequence *) quantified->object.target;
  ck_assert_ptr_ne(sequence, nullptr);
  ck_assert_uint_eq(Array_length(sequence), (sizeof "123") - 1);
  for (uint32_t i = 0; i < Array_length(sequence); i++) {
    ck_assert_uint_eq(*(char *) Array_get(sequence, i), "123"[i]);
  }
  ck_assert_uint_eq(quantified->quant.min, 0);
  ck_assert_uint_eq(quantified->quant.max, 1);

  releaseRegexp(regexp, &STDAllocator);
  Array_destroy(regexp);
  STDAllocator.free(terminals);
}

END_TEST

#define string_to_test1 "123+"

START_TEST(test_QUANTIFIED_NURMAL1) {
  char_t *string = string_to_test1;
  uint32_t cost, n_tokens;
  Terminal *terminals = tokenize(string, &cost, &n_tokens, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof string_to_test1) - 1);
  ck_assert_uint_eq(n_tokens, (sizeof string_to_test1));
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
  ck_assert_uint_eq(object->type, enum_Quantified);
  ck_assert_uint_eq(object->inv, false);

  Quantified *quantified = (Quantified *) object->target;
  ck_assert_uint_eq(quantified->object.type, enum_Sequence);
  ck_assert_uint_eq(quantified->object.inv, false);
  Sequence *sequence = (Sequence *) quantified->object.target;
  ck_assert_ptr_ne(sequence, nullptr);
  ck_assert_uint_eq(Array_length(sequence), (sizeof "123") - 1);
  for (uint32_t i = 0; i < Array_length(sequence); i++) {
    ck_assert_uint_eq(*(char *) Array_get(sequence, i), "123"[i]);
  }
  ck_assert_uint_eq(quantified->quant.min, 1);
  ck_assert_uint_eq(quantified->quant.max, 0);

  releaseRegexp(regexp, &STDAllocator);
  Array_destroy(regexp);
  STDAllocator.free(terminals);
}

END_TEST

#define string_to_test2 "123*"

START_TEST(test_QUANTIFIED_NURMAL2) {
  char_t *string = string_to_test2;
  uint32_t cost, n_tokens;
  Terminal *terminals = tokenize(string, &cost, &n_tokens, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof string_to_test2) - 1);
  ck_assert_uint_eq(n_tokens, (sizeof string_to_test2));
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
  ck_assert_uint_eq(object->type, enum_Quantified);
  ck_assert_uint_eq(object->inv, false);

  Quantified *quantified = (Quantified *) object->target;
  ck_assert_uint_eq(quantified->object.type, enum_Sequence);
  ck_assert_uint_eq(quantified->object.inv, false);
  Sequence *sequence = (Sequence *) quantified->object.target;
  ck_assert_ptr_ne(sequence, nullptr);
  ck_assert_uint_eq(Array_length(sequence), (sizeof "123") - 1);
  for (uint32_t i = 0; i < Array_length(sequence); i++) {
    ck_assert_uint_eq(*(char *) Array_get(sequence, i), "123"[i]);
  }
  ck_assert_uint_eq(quantified->quant.min, 0);
  ck_assert_uint_eq(quantified->quant.max, 0);

  releaseRegexp(regexp, &STDAllocator);
  Array_destroy(regexp);
  STDAllocator.free(terminals);
}

END_TEST

#define string_to_test3 "123{3}"

START_TEST(test_QUANTIFIED_NURMAL3) {
  char_t *string = string_to_test3;
  uint32_t cost, n_tokens;
  Terminal *terminals = tokenize(string, &cost, &n_tokens, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof string_to_test3) - 1);
  ck_assert_uint_eq(n_tokens, (sizeof string_to_test3));
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
  ck_assert_uint_eq(object->type, enum_Quantified);
  ck_assert_uint_eq(object->inv, false);

  Quantified *quantified = (Quantified *) object->target;
  ck_assert_uint_eq(quantified->object.type, enum_Sequence);
  ck_assert_uint_eq(quantified->object.inv, false);
  Sequence *sequence = (Sequence *) quantified->object.target;
  ck_assert_ptr_ne(sequence, nullptr);
  ck_assert_uint_eq(Array_length(sequence), (sizeof "123") - 1);
  for (uint32_t i = 0; i < Array_length(sequence); i++) {
    ck_assert_uint_eq(*(char *) Array_get(sequence, i), "123"[i]);
  }
  ck_assert_uint_eq(quantified->quant.min, 3);
  ck_assert_uint_eq(quantified->quant.max, 3);

  releaseRegexp(regexp, &STDAllocator);
  Array_destroy(regexp);
  STDAllocator.free(terminals);
}

END_TEST

#define string_to_test4 "123{3,7}"

START_TEST(test_QUANTIFIED_NURMAL4) {
  char_t *string = string_to_test4;
  uint32_t cost, n_tokens;
  Terminal *terminals = tokenize(string, &cost, &n_tokens, &STDAllocator);
  ck_assert_uint_eq(cost, (sizeof string_to_test4) - 1);
  ck_assert_uint_eq(n_tokens, (sizeof string_to_test4));
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
  ck_assert_uint_eq(object->type, enum_Quantified);
  ck_assert_uint_eq(object->inv, false);

  Quantified *quantified = (Quantified *) object->target;
  ck_assert_uint_eq(quantified->object.type, enum_Sequence);
  ck_assert_uint_eq(quantified->object.inv, false);
  Sequence *sequence = (Sequence *) quantified->object.target;
  ck_assert_ptr_ne(sequence, nullptr);
  ck_assert_uint_eq(Array_length(sequence), (sizeof "123") - 1);
  for (uint32_t i = 0; i < Array_length(sequence); i++) {
    ck_assert_uint_eq(*(char *) Array_get(sequence, i), "123"[i]);
  }
  ck_assert_uint_eq(quantified->quant.min, 3);
  ck_assert_uint_eq(quantified->quant.max, 7);

  releaseRegexp(regexp, &STDAllocator);
  Array_destroy(regexp);
  STDAllocator.free(terminals);
}

END_TEST

Suite *quantified_suite() {
  Suite *suite = suite_create("Quantified");
  TCase *t_case = tcase_create("quantified");
  tcase_add_test(t_case, test_QUANTIFIED_NURMAL0);
  tcase_add_test(t_case, test_QUANTIFIED_NURMAL1);
  tcase_add_test(t_case, test_QUANTIFIED_NURMAL2);
  tcase_add_test(t_case, test_QUANTIFIED_NURMAL3);
  tcase_add_test(t_case, test_QUANTIFIED_NURMAL4);
  suite_add_tcase(suite, t_case);
  return suite;
}

