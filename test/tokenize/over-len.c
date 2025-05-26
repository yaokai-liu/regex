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
 * Filename: over-len.c
 * Creator: Yaokai Liu
 * Create Date: 2024-7-12
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "allocator.h"
#include "char_t.h"
#include "tokens.h"
#include "token.h"
#include "regex.h"
#include <check.h>
#include <stdint.h>
#include <string.h>

#define string_for_test              \
  "12345678123456781234567812345678" \
  "1234567812345678123456781234567"

START_TEST(test_REALLOC) {
  char_t *string = string_for_test;
  uint32_t cost, n_tokens;
  const Terminal *terminals = regex_tokenize(string, &cost, &n_tokens, nullptr, nullptr, &STDAllocator);
  ck_assert_uint_eq(cost, 63);
  ck_assert_uint_eq(n_tokens, 64);
  ck_assert_ptr_ne(terminals, nullptr);
  ck_assert_str_eq(get_name(terminals[n_tokens - 1].type), string_t("TERMINATOR"));
  STDAllocator.free((void *) terminals);
}

END_TEST

#define BUFFER_SIZE (64 * sizeof(Terminal))
thread_local static uint32_t allocated = 0;
thread_local static char buffer[BUFFER_SIZE] = {};

void *moc_malloc(size_t size) {
  if (allocated + size > BUFFER_SIZE) { return nullptr; }
  void *ptr = &buffer[allocated];
  allocated += size;
  return ptr;
}

void *moc_calloc(size_t count, size_t size) {
  size = count * size;
  if (allocated + size > BUFFER_SIZE) { return nullptr; }
  void *ptr = &buffer[allocated];
  for (uint32_t i = 0; i < size; i++, allocated++) { buffer[allocated] = '\0'; }
  return ptr;
}

void *moc_realloc(void *ptr, size_t size) {
  void *new_buffer = moc_malloc(size);
  if (!new_buffer) { return nullptr; }
  if (ptr) { memcpy(new_buffer, ptr, size); }
  return new_buffer;
}

void moc_free(void *ptr) {
  // nothing to do.
  *(char *) ptr = 'h';
}

void *moc_memcpy(void * restrict dest, const void * restrict src, size_t size) {
  return memcpy(dest, src, size);
}

void *moc_memset(void *dest, int value, size_t size) {
  return memset(dest, value, size);
}

static const Allocator MocAllocator = {.malloc = moc_malloc,
                                       .realloc = moc_realloc,
                                       .calloc = moc_calloc,
                                       .free = moc_free,
                                       .memcpy = moc_memcpy,
                                       .memset = moc_memset};

#define string_for_test2 "123456781234567812345678123456"

START_TEST(test_REALLOC_LAST) {
  char_t *string = string_for_test2;
  uint32_t cost, n_tokens;
  const Terminal *terminals = regex_tokenize(string, &cost, &n_tokens, nullptr, nullptr, &MocAllocator);
  ck_assert_uint_eq(cost, 30);
  ck_assert_uint_eq(n_tokens, 31);
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
  const Terminal *terminals = regex_tokenize(string, &cost, &n_tokens, nullptr, nullptr, &MocAllocator);
  ck_assert_uint_eq(cost, sizeof(string_for_test3) - 1);
  ck_assert_uint_lt(n_tokens, sizeof(string_for_test3) - 1);
  ck_assert_uint_ne(terminals[n_tokens - 1].type, enum_TERMINATOR);
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
