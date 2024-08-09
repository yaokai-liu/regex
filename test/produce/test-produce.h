/**
 * Project Name: regex
 * Module Name: test/produce
 * Filename: test-produce.h
 * Creator: Yaokai Liu
 * Create Date: 24-7-13
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_TEST_PRODUCE_H
#define REGEX_TEST_PRODUCE_H

#include <check.h>

Suite *sequence_suite();
Suite *charset_suite();
Suite *quantified_suite();
Suite *group_suite();
Suite *branch_suite();

Suite *illegal_suite();

#endif  // REGEX_TEST_PRODUCE_H
