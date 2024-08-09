/**
 * Project Name: regex
 * Module Name: test
 * Filename: test-produce.c
 * Creator: Yaokai Liu
 * Create Date: 2024-6-27
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/
#include "produce/test-produce.h"
#include <check.h>

int main() {
  SRunner *srunner = srunner_create(nullptr);
  srunner_add_suite(srunner, sequence_suite());
  srunner_add_suite(srunner, charset_suite());
  srunner_add_suite(srunner, quantified_suite());
  srunner_add_suite(srunner, group_suite());
  srunner_add_suite(srunner, branch_suite());
  srunner_add_suite(srunner, illegal_suite());
  srunner_set_fork_status(srunner, CK_NOFORK);
  srunner_run_all(srunner, CK_NORMAL);
  int n = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return n ? -1 : 0;
}
