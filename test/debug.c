/**
 * Project Name: regex
 * Module Name: test
 * Filename: debug.c
 * Creator: Yaokai Liu
 * Create Date: 2024-7-13
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "regex/parse.h"
#include "regex/target.h"
#include "terminal.h"
#include <stdio.h>

int main() {
  const char *string = "^0123456789\\w";
  Regexp *regexp = parse(string, nullptr, nullptr, nullptr, &STDAllocator);
  if (!regexp) { return -1; }
  printf("%u\n", Array_length(regexp));
  Branch *branch = Array_first_real(regexp);
  printf("%u\n", Array_length(branch));
  Object *object = Array_real_addr(branch, 10);
  Charset *charset = object->target;
  printf("%u\n", Set_count(charset->parts[CT_NORMAL].ranges));
  return 0;
}
