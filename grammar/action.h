/**
 * Project Name: regex
 * Module Name:
 * Filename: actions.h
 * Creator: Yaokai Liu
 * Create Date: 24-6-26
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_ACTION_H
#define REGEX_ACTION_H

#include "target.h"
#include "terminal.h"

#define MAX_ARGC 0x10

Regexp *produce(const Terminal *tokens, const Allocator *allocator);

#endif  // REGEX_ACTION_H
