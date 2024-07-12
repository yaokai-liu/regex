/**
 * Project Name: regex
 * Module Name: test
 * Filename: debug.c
 * Creator: Yaokai Liu
 * Create Date: 2024-7-13
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "action.h"
#include "terminal.h"
#include <stdio.h>

#define len(a) ((sizeof a) / sizeof(a[0]))

int main() {
  const char *string = "0123456789";
  uint32_t cost = 0, n_tokens = 0;
  Terminal *tokens = tokenize(string, &cost, &n_tokens, &STDAllocator);
  Regexp *regexp = produce(tokens, &STDAllocator);
  if (!regexp) { return -1; }
  printf("%u\n", Array_length(regexp));
  return 0;
}
