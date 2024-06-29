/**
 * Project Name: regex
 * Module Name: test
 * Filename: test-produce.c
 * Creator: Yaokai Liu
 * Create Date: 24-6-27
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "grammar/action.h"

#define len(a) ((sizeof a) / sizeof(a[0]))

int main() {
  "1+2*3?45{123,45}";
  const char *string = "([<a-z>stc])";
  uint32_t cost = 0, n_tokens = 0;
  Terminal *tokens = tokenize(string, &cost, &n_tokens);
  struct Regexp * regexp = produce(tokens);
  if (!regexp) { return -1; }
  return 0;
}

