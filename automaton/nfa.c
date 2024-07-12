/**
 * Project Name: regex
 * Module Name: automaton
 * Filename: nfa.c
 * Creator: Yaokai Liu
 * Create Date: 2024-7-1
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "nfa.h"

uint32_t FinityMaton_addChar(struct FinityMaton *maton, uint32_t plain);

void FinityMaton_combineCharset(struct FinityMaton *maton, uint32_t *plains, uint32_t length) {
  for (uint32_t i = 0; i < length; i++) { FinityMaton_addChar(maton, plains[i]); }
}

uint32_t FinityMaton_addChar(struct FinityMaton *maton, uint32_t plain) {
  if (!maton || !plain) { return 0; }
  return plain;
}