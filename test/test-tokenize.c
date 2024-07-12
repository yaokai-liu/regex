/**
 * Project Name: regex
 * Module Name: test/tokenize
 * Filename: test-tokenize.c
 * Creator: Yaokai Liu
 * Create Date: 2024-6-29
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "tokenize/test-tokenize.h"
#include <check.h>

int main() {
  SRunner *srunner = srunner_create(nullptr);
  srunner_add_suite(srunner, single_token_suite());
  srunner_add_suite(srunner, number_suite());
  srunner_add_suite(srunner, char_suite());
  srunner_add_suite(srunner, over_len_suite());
  srunner_set_fork_status(srunner, CK_NOFORK);
  srunner_run_all(srunner, CK_NORMAL);
  int n = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return n ? -1 : 0;
}
