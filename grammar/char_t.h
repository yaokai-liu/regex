/**
 * Project Name: regex
 * Module Name: grammar
 * Filename: char_t.h
 * Creator: Yaokai Liu
 * Create Date: 24-7-4
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_CHAR_T_H
#define REGEX_CHAR_T_H

#include <stdint.h>

// Promise sizeof(char_t) < sizeof(uint64_t).
typedef uint8_t char_t;

#endif // REGEX_CHAR_T_H