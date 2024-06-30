/**
 * Project Name: regex
 * Module Name: test
 * Filename: test-produce.c
 * Creator: Yaokai Liu
 * Create Date: 24-6-27
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include <stdio.h>
#include "grammar/target.h"
#include "grammar/action.h"
#include "grammar/token.h"

#define len(a) ((sizeof a) / sizeof(a[0]))

int main() {
  const char *string = "1+2*3?45{123,45}|([<a-z>stc])";
  uint32_t cost = 0, n_tokens = 0;
  Terminal *tokens = tokenize(string, &cost, &n_tokens);
  struct Regexp *regexp = produce(tokens);
  if (!regexp) { return -1; }
  printf("%u\n", regexp->branches->post_state);
  return 0;
}

