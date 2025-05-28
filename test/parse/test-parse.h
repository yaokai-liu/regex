/* License
 *
 * x-regex - A light regular expression and its compiler
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
 * Module Name: test/parse
 * Filename: test-parse.h
 * Creator: Yaokai Liu
 * Create Date: 24-7-13
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_TEST_PARSE_H
#define REGEX_TEST_PARSE_H

#include <check.h>

Suite *sequence_suite();
Suite *charset_suite();
Suite *quantified_suite();
Suite *group_suite();
Suite *branch_suite();

Suite *illegal_suite();

#endif  // REGEX_TEST_PARSE_H
