/**
 * Project Name: regex
 * Module Name: automaton
 * Filename: nfa.h
 * Creator: Yaokai Liu
 * Create Date: 24-7-1
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_NFA_H
#define REGEX_NFA_H

#include <stdint.h>

struct FinityMaton {
  uint32_t *plains;
  uint32_t *states;
};

struct Action {
  void *operation;
  uint32_t failed;
  uint32_t success;
};

void FinityMaton_combineCharset(struct FinityMaton *maton, uint32_t *plains, uint32_t length);

#endif  // REGEX_NFA_H
