/**
 * Project Name: regex
 * Module Name: test
 * Filename: test-produce.c
 * Creator: Yaokai Liu
 * Create Date: 24-6-27
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "action.h"
#include "array.h"
#include "target.h"
#include <stdio.h>

#define len(a) ((sizeof a) / sizeof(a[0]))

int main() {
  const char *string = "1+2*3?45{123,45}|([<a-z>stc])";
  uint32_t cost = 0, n_tokens = 0;
  Terminal *tokens = tokenize(string, &cost, &n_tokens);
  Regexp * regexp = produce(tokens);
  if (!regexp) { return -1; }
  printf("%u\n", Array_length(regexp));
  return 0;
}

