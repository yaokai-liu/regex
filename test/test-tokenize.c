/**
 * Project Name: regex
 * Module Name: test
 * Filename: test-tokenize.c
 * Creator: Yaokai Liu
 * Create Date: 24-6-25
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "terminal.h"
#include "token.h"
#include "tokens.gen.h"
#include <malloc.h>
#include <stdio.h>

#define len(a) ((sizeof a) / sizeof(a[0]))

int main() {
  const char *string = "+-*^,12345{123,45}()[]";
  const uint8_t type_list[20] = {enum_PLUS,
                                 enum_MINUS,
                                 enum_TIMES,
                                 enum_NOT,
                                 enum_COMMA,
                                 enum_CHAR,
                                 enum_CHAR,
                                 enum_CHAR,
                                 enum_CHAR,
                                 enum_CHAR,
                                 enum_BEGIN_QUANTIFIER,
                                 enum_NUMBER,
                                 enum_COMMA,
                                 enum_NUMBER,
                                 enum_END_QUANTIFIER,
                                 enum_BEGIN_GROUP,
                                 enum_END_GROUP,
                                 enum_BEGIN_CHARSET,
                                 enum_END_CHARSET,
                                 enum_TERMINATOR};
  uint32_t cost = 0, n_tokens = 0;
  Terminal *tokens = tokenize(string, &cost, &n_tokens);
  if (n_tokens != len(type_list)) { return -1; }
  for (int i = 0; i < n_tokens; i++) {
    if (tokens[i].type != type_list[i]) { return -1; }
    printf("%s ", get_name(tokens[i].type));
  }
  free(tokens);
  return 0;
}

