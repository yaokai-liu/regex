/**
 * Project Name: regex
 * Module Name: test/tokenize
 * Filename: over-len.c
 * Creator: Yaokai Liu
 * Create Date: 2024-7-12
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "allocator.h"
#include "char_t.h"
#include "terminal.h"
#include "token.h"
#include <check.h>
#include <stdint.h>
#include <string.h>

#define string_for_test              \
  "12345678123456781234567812345678" \
  "1234567812345678123456781234567"

START_TEST(test_REALLOC) {
  char_t *string = string_for_test;
  uint32_t cost, n_tokens;
  Terminal *terminals = tokenize(string, &cost, &n_tokens, &STDAllocator);
  ck_assert_uint_eq(cost, 63);
  ck_assert_uint_eq(n_tokens, 64);
  ck_assert_ptr_ne(terminals, nullptr);
  ck_assert_str_eq(get_name(terminals[n_tokens - 1].type), string_t("TERMINATOR"));
  STDAllocator.free(terminals);
}

END_TEST

#define BUFFER_SIZE (64 * sizeof(Terminal))
thread_local static uint32_t allocated = 0;
thread_local static char buffer[BUFFER_SIZE] = {};

void *moc_malloc(size_t size) {
  if (allocated + size > BUFFER_SIZE) { return nullptr; }
  return &buffer[allocated];
}

void *moc_realloc(void *ptr, size_t size) {
  void *new_buffer = moc_malloc(size);
  if (!new_buffer) { return nullptr; }
  memcpy(new_buffer, ptr, size);
  return new_buffer;
}

void moc_free(void *ptr) {
  // nothing to do.
  *(char *) ptr = 'h';
}

static const Allocator MocAllocator = {
  .malloc = moc_malloc, .realloc = moc_realloc, .calloc = nullptr, .free = moc_free};

#define string_for_test2 "12345678123456781234567812345678"

START_TEST(test_REALLOC_LAST) {
  char_t *string = string_for_test2;
  uint32_t cost, n_tokens;
  Terminal *terminals = tokenize(string, &cost, &n_tokens, &MocAllocator);
  ck_assert_uint_eq(cost, 32);
  ck_assert_uint_eq(n_tokens, 33);
  ck_assert_ptr_ne(terminals, nullptr);
  ck_assert_str_eq(get_name(terminals[n_tokens - 1].type), string_t("TERMINATOR"));
  for (uint32_t i = 0; i < BUFFER_SIZE; i++) { buffer[i] = '\0'; }
  allocated = 0;
}

END_TEST

#define string_for_test3             \
  "12345678123456781234567812345678" \
  "12345678123456781234567812345678"

START_TEST(test_REALLOC_FAILED) {
  char_t *string = string_for_test3;
  uint32_t cost, n_tokens;
  Terminal *terminals = tokenize(string, &cost, &n_tokens, &MocAllocator);
  ck_assert_uint_eq(cost, 64);
  ck_assert_uint_eq(n_tokens, 0);
  ck_assert_ptr_eq(terminals, nullptr);
  for (uint32_t i = 0; i < BUFFER_SIZE; i++) { buffer[i] = '\0'; }
  allocated = 0;
}

END_TEST

Suite *over_len_suite() {
  Suite *suite = suite_create("Continuous Tokens");
  TCase *tc_over_len = tcase_create("over-len");
  tcase_add_test(tc_over_len, test_REALLOC);
  tcase_add_test(tc_over_len, test_REALLOC_LAST);
  tcase_add_test(tc_over_len, test_REALLOC_FAILED);
  suite_add_tcase(suite, tc_over_len);
  return suite;
}
